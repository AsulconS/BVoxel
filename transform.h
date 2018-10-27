#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform
{
private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

public:
    Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
    virtual ~Transform();
};

#endif // TRANSFORM_H
