#ifndef ECS_H
#define ECS_H

#include "ecsComponent.h"
#include "ecsSystem.h"
#include "../dStr/map.h"

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

public:
    ECS() {}
    ~ECS();

    // Entity Methods
    EntityHandle makeEntity(BaseECSComponent* components, const uint32* componentIDs, size_t numComponents);
    void removeEntity(EntityHandle handle);

    // Component Methods
    template <typename Component>
    void addComponent(EntityHandle entity, Component* component);

    template <typename Component>
    void removeComponent(EntityHandle entity);

    template <typename Component>
    void getComponent(EntityHandle entity);

    // System Methods
    inline void addSystem(BaseECSSystem& system)
    {
        systems.push_back(&system);
    }

    void updateSystems();
    void removeSystems(BaseECSSystem& system);
};

#endif // ECS_H
