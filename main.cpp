// Recommended for OpenGL 3.0 or lastest versions
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>

int main()
{
    Display display(800, 600, "BVoxel Test Window");

    Vertex vertices[] = { Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
                          Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 1.0f)),
                          Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)) };
    
    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
    Shader shader("./res/basicShader");
    Texture texture("./res/bricks.jpg");

    shader.bind();
    texture.bind(0);

    while(!display.isClosed())
    {
        display.clear(0.0f, 0.15f, 0.3f, 1.0f);

        mesh.draw();

        display.update();
    }

    return 0;
}
