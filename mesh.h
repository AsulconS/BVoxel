#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Vertex
{
    friend class Mesh;

private:
    glm::vec3 pos;
    glm::vec2 texCoord;

public:
    Vertex(const glm::vec3& pos, const glm::vec2 texCoord)
        : pos(pos), texCoord(texCoord) {}
};

class Mesh
{
private:
    enum
    {
        POSITION_VB,
        TEXTCOORD_VB,
        NUM_BUFFERS,
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int drawCount;

public:
    Mesh(Vertex* vertices, unsigned int numVertices);
    virtual ~Mesh();

    void draw();
};

#endif // MESH_H
