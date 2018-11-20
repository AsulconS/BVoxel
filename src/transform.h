#ifndef TRANSFORM_H
#define TRANSFORM_H
#define GLM_ENABLE_EXPERIMENTAL

#include "math/math.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

public:
    Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
        : pos(pos), rot(rot), scale(scale) {}
    virtual ~Transform() {}

    inline glm::mat4 getModel() const
    {
        glm::mat4 posMatrix = glm::translate(pos);
        glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1,0,0));
        glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0,1,0));
        glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0,0,1));
        glm::mat4 scaleMatrix = glm::scale(scale);

        glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

        return posMatrix * rotMatrix * scaleMatrix;
    }

    inline glm::vec3 getPos() const { return glm::vec3(pos.z, pos.x * -1.0f, pos.y); }
    inline glm::vec3 getRot() const { return glm::vec3(rot.z, rot.x * -1.0f, rot.y); }
    inline glm::vec3 getScale() const { return glm::vec3(scale.z, scale.x * -1.0f, scale.y); }

    inline glm::vec3& getNativePos() { return pos; }
    inline glm::vec3& getNativeRot() { return rot; }
    inline glm::vec3& getNativeScale() { return scale; }

    inline void setPosition(const glm::vec3& _pos)
    {
        this->pos.x = _pos.y * -1.0f;
        this->pos.y = _pos.z;
        this->pos.z = _pos.x;
    }
    inline void setTranslation(const glm::vec3& offset)
    {
        this->pos.x += offset.y * -1.0f;
        this->pos.y += offset.z;
        this->pos.z += offset.x;
    }
    inline void setAngle(const glm::vec3& _rot)
    {
        this->rot.x = _rot.y * -1.0f;
        this->rot.y = _rot.z;
        this->rot.z = _rot.x;
    }
    inline void setRotation(const glm::vec3& offset)
    {
        this->rot.x += offset.y * -1.0f;
        this->rot.y += offset.z;
        this->rot.z += offset.x;
    }
    inline void setScale(const glm::vec3& _scale)
    {
        this->scale.x = _scale.y * -1.0f;
        this->scale.y = _scale.z;
        this->scale.z = _scale.x;
    }
};

#endif // TRANSFORM_H
