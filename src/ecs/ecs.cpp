#include "ecs.h"

ECS::~ECS()
{
    for(Map<uint32, Vector<uint8>>::iterator it = components.begin(); it != components.end(); it++)
    {
        size_t typeSize = BaseECSComponent::getTypeSize(it->first);
        ECSComponentFreeFunction freefn = BaseECSComponent::getTypeFreeFunction(it->first);
        for(uint32 i = 0; i < it->second.size(); i += typeSize)
        {
            freefn((BaseECSComponent*)&it->second[i]);
        }
    }

    for(uint32 i = 0; i < entities.size(); ++i)
    {
        delete entities[i];
    }
}

EntityHandle ECS::makeEntity(BaseECSComponent* entityComponents, const uint32* componentIDs, size_t numComponents)
{
    std::pair<uint32, Vector<std::pair<uint32, uint32>>>* newEntity = new std::pair<uint32, Vector<std::pair<uint32, uint32>>>();
    EntityHandle handle = (EntityHandle)newEntity;
    for(uint32 i = 0; i < numComponents; ++i)
    {
        // Check if ID is valid
        if(BaseECSComponent::isTypeValid(componentIDs[i]))
        {
            DEBUG_LOG("ECS", LOG_ERROR, "'%u' is not a valid component");
            delete newEntity;
            return NULL_ENTITY_HANDLE;
        }

        addComponentInternal(handle, newEntity->second, componentIDs[i], &entityComponents[i]);
    }

    newEntity->first = entities.size();
    entities.push_back(newEntity);
    return handle;
}

void ECS::removeEntity(EntityHandle handle)
{
    Vector<std::pair<uint32, uint32>>& entity = handleToEntity(handle);
    for(uint32 i = 0; i < entities.size(); ++i)
    {
        deleteComponent(entity[i].first, entity[i].second);
    }

    uint32 destIndex = handleToEntityIndex(handle);
    uint32 srcIndex = entities.size() - 1;
    delete entities[destIndex];
    entities[destIndex] = entities[srcIndex];
    entities.pop_back();
}

void ECS::addComponentInternal(EntityHandle handle, Vector<std::pair<uint32, uint32>>& entity, uint32 componentID, BaseECSComponent* component)
{
    ECSComponentCreateFunction createfn = BaseECSComponent::getTypeCreateFunction(componentID);
    std::pair<uint32, uint32> newPair;
    newPair.first = componentID;
    newPair.second = createfn(components[componentID], handle, component);
    entity.push_back(newPair);
}

void ECS::deleteComponent(uint32 componentID, uint32 index)
{
    Vector<uint8>& array = components[componentID];
    ECSComponentFreeFunction freefn = BaseECSComponent::getTypeFreeFunction(componentID);
    size_t typeSize = BaseECSComponent::getTypeSize(componentID);
    uint32 srcIndex = array.size() - typeSize;

    BaseECSComponent* srcComponent = (BaseECSComponent*)&array[srcIndex];
    BaseECSComponent* destComponent = (BaseECSComponent*)&array[index];
    freefn(destComponent);

    if(index == srcIndex)
    {
        array.resize(srcIndex);
        return;
    }

    std::memcpy(destComponent, srcComponent, typeSize);

    Vector<std::pair<uint32, uint32>>& srcComponents = handleToEntity(srcComponent->entity);
    for(uint32 i = 0; i < srcComponents.size(); ++i)
    {
        if(componentID == srcComponents[i].first && srcIndex == srcComponents[i].second)
        {
            srcComponents[i].second = index;
            break;
        }
    }

    array.resize(srcIndex);
}

bool ECS::removeComponentInternal(EntityHandle handle, uint32 componentID)
{
    Vector<std::pair<uint32, uint32>>& entityComponents = handleToEntity(handle);
    for(uint32 i = 0; i < entityComponents.size(); ++i)
    {
        if(componentID == entityComponents[i].first)
        {
            deleteComponent(entityComponents[i].first, entityComponents[i].second);
            uint32 srcIndex = entityComponents.size() - 1;
            uint32 destIndex = i;
            entityComponents[destIndex] = entityComponents[srcIndex];
            entityComponents.pop_back();
            return true;
        }
    }
    return false;
}

BaseECSComponent* ECS::getComponentInternal(Vector<std::pair<uint32, uint32>>& entityComponents, uint32 componentID)
{
    for(uint32 i = 0; i < entityComponents.size(); ++i)
    {
        if(componentID == entityComponents[i].first)
        {
            return (BaseECSComponent*)&components[componentID][entityComponents[i].second];
        }
    }
    return nullptr;
}

bool ECS::removeSystems(BaseECSSystem& system)
{
    for(uint32 i = 0; i < systems.size(); ++i)
    {
        if(&system == systems[i])
        {
            systems.erase(systems.begin() + i);
            return true;
        }
    }
    return false;
}

void ECS::updateSystems()
{
    Vector<BaseECSComponent*> componentParam;
    for(uint32 i = 0; i < systems.size(); ++i)
    {
        const Vector<uint32>& componentTypes = systems[i]->getComponentTypes();
        if(componentTypes.size() == 1)
        {
            size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[0]);
            Vector<uint8>& array = components[componentTypes[0]];
            for(uint32 j = 0; j < array.size(); j += typeSize)
            {
                BaseECSComponent* components = (BaseECSComponent*)&array[j];
                systems[i]->updateComponents(&components);
            }
        }
        else
        {
            updateSystemWithMultipleComponents(i, componentTypes, componentParam);
        }
    }
}

void ECS::updateSystemWithMultipleComponents(uint32 index, const Vector<uint32>& componentTypes, Vector<BaseECSComponent*>& componentParam)
{
    componentParam.resize(Math::max(componentParam.size(), componentTypes.size()));

    size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[0]);
    Vector<uint8>& array = components[componentTypes[0]];
    for(uint32 i = 0; i < array.size(); i += typeSize)
    {
        componentParam[0] = (BaseECSComponent*)&array[i];
        Vector<std::pair<uint32, uint32>>& entityComponents = handleToEntity(componentParam[0]->entity);

        bool isValid = true;
        for(uint32 j = 0; j < componentTypes.size(); ++j)
        {
            if(j == 0) continue;

            componentParam[j] = getComponentInternal(entityComponents, componentTypes[j]);
            if(componentParam[j] == nullptr) isValid = false;
        }

        if(isValid)
            systems[index]->updateComponents(&componentParam[0]);
    }
}
