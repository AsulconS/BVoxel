#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "ecsComponent.h"

class BaseECSSystem
{
private:
    Vector<uint32> componentTypes;

public:
    BaseECSSystem(const Vector<uint32>& _componentTypes) : componentTypes(_componentTypes) {}
    virtual void updateComponents(BaseECSComponent** components) = 0;
    const Vector<uint32>& getComponentTypes() { return componentTypes; }
};

#endif // ECS_SYSTEM_H
