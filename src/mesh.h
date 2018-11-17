#ifndef MESH_H
#define MESH_H

#include "obj_loader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Vertex
{
    friend class Mesh;

private:
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;

public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))
        : pos(pos), texCoord(texCoord), normal(normal) {}
    
    inline glm::vec3* getPos() { return &pos; }
    inline glm::vec2* getTexCoord() { return &texCoord; }
    inline glm::vec3* getNormal() { return &normal; }
};

class Mesh
{
private:
    void initMesh(const IndexedModel& model);
    
    enum
    {
        POSITION_VB,
        TEXTCOORD_VB,
        NORMAL_VB,

        INDEX_VB,

        NUM_BUFFERS,
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int drawCount;

public:
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    Mesh(const std::string& fileName);
    virtual ~Mesh();

    void draw();
};

#endif // MESH_H
