#ifndef ECS_H
#define ECS_H

#include "ecsComponent.h"
#include "ecsSystem.h"
#include "../dStr/map.h"
#include "../math/math.h"
#include <cstring>

class ECS
{
private:
    Vector<BaseECSSystem*> systems;
    Map<uint32, Vector<uint8>> components;
    Vector<std::pair<uint32, Vector<std::pair<uint32, uint32>>>*> entities;

    inline std::pair<uint32, Vector<std::pair<uint32, uint32>>>* handleToRawType(EntityHandle handle)
    {
        return (std::pair<uint32, Vector<std::pair<uint32, uint32>>>*)handle;
    }
    inline uint32 handleToEntityIndex(EntityHandle handle)
    {
        return handleToRawType(handle)->first;
    }
    inline Vector<std::pair<uint32, uint32>>& handleToEntity(EntityHandle handle)
    {
        return handleToRawType(handle)->second;
    }

    void deleteComponent(uint32 componentID, uint32 index);
    bool removeComponentInternal(EntityHandle handle, uint32 componentID);
    void addComponentInternal(EntityHandle handle, Vector<std::pair<uint32, uint32>>& entity, uint32 componentID, BaseECSComponent* component);
    BaseECSComponent* getComponentInternal(Vector<std::pair<uint32, uint32>>& entityComponents, uint32 componentID);

    void updateSystemWithMultipleComponents(uint32 index, const Vector<uint32>& componentTypes, Vector<BaseECSComponent*>& componentParam);

public:
    ECS() {}
    ~ECS();

    // Entity Methods
    EntityHandle makeEntity(BaseECSComponent* components, const uint32* componentIDs, size_t numComponents);
    void removeEntity(EntityHandle handle);

    // Component Methods
    template <typename Component>
    inline void addComponent(EntityHandle entity, Component* component)
    {
        addComponentInternal(entity, handleToEntity(entity), Component::ID, component);
    }

    template <typename Component>
    inline bool removeComponent(EntityHandle entity)
    {
        return removeComponentInternal(entity, Component::ID);
    }

    template <typename Component>
    Component* getComponent(EntityHandle entity)
    {
        return (Component*)getComponentInternal(handleToEntity(entity), Component::ID);
    }

    // System Methods
    inline void addSystem(BaseECSSystem& system)
    {
        systems.push_back(&system);
    }

    void updateSystems();
    bool removeSystems(BaseECSSystem& system);
};

#endif // ECS_H
