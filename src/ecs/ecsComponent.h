#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include "../core/common.h"
#include "../dStr/vector.h"

#define NULL_ENTITY_HANDLE nullptr

struct BaseECSComponent;
typedef void* EntityHandle;
typedef uint32 (*ECSComponentCreateFunction)(Vector<uint8>& memory, EntityHandle entity, BaseECSComponent* comp);
typedef void (*ECSComponentFreeFunction)(BaseECSComponent* comp);

struct BaseECSComponent
{
    static uint32 nextID();
    EntityHandle entity = NULL_ENTITY_HANDLE;
};

template <typename T>
struct ECSComponent : public BaseECSComponent
{
    static const ECSComponentCreateFunction CREATE_FUNCTION;
    static const ECSComponentFreeFunction FREE_FUNCTION;
    static const uint32 ID;
    static const size_t SIZE;
};

template <typename Component>
uint32 ECSComponentCreate(Vector<uint8>& memory, EntityHandle entity, BaseECSComponent* comp)
{
    uint32 index = memory.size();
    memory.resize(index + Component::SIZE);
    Component* component = new(&memory[index]) Component(*(Component*)comp);
    component->entity = entity;
    return index;
}

template <typename Component>
void ECSComponentFree(BaseECSComponent* comp)
{
    Component* component = (Component*)comp;
    component->~Component();
}

template <typename T>
const uint32 ECSComponent<T>::ID(BaseECSComponent::nextID());

template <typename T>
const size_t ECSComponent<T>::SIZE(sizeof(T));

template <typename T>
const ECSComponentCreateFunction ECSComponent<T>::CREATE_FUNCTION(ECSComponentCreate<T>);

template <typename T>
const ECSComponentFreeFunction ECSComponent<T>::FREE_FUNCTION(ECSComponentFree<T>);

// TESTING CODE
struct TestComponent : public ECSComponent<TestComponent>
{
    float x;
    float y;
};

#endif // ECS_COMPONENT_H
