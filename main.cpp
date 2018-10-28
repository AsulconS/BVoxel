// Recommended for OpenGL 3.0 or lastest versions
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

int main()
{
    Display display(WIDTH, HEIGHT, "BVoxel Test Window");

    Vertex vertices[] = { Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
                          Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 1.0f)),
                          Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)) };
    
    unsigned int indices[] = { 0, 1, 2 };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
    Mesh mesh2("./res/basicman.obj");
    Shader shader("./res/basicShader");
    Texture texture("./res/bricks.jpg");
    Camera camera(glm::vec3(0, 0, -24), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
    Transform transform;

    float counter = 0.0f;

    while(!display.isClosed())
    {
        display.clear(0.0f, 0.15f, 0.3f, 1.0f);

        float sinCounter = sinf(counter);
        float cosCounter = cosf(counter);

        /*transform.getPos().x = sinCounter;
        transform.getPos().z = cosCounter;
        transform.getRot().x = counter;
        transform.getRot().y = counter;
        transform.getRot().z = counter;*/
        //transform.setScale(glm::vec3(cosCounter, cosCounter, cosCounter));
        transform.getRot().y = counter;

        shader.bind();
        texture.bind(0);
        shader.update(transform, camera);
        mesh2.draw();

        display.update();
        counter += 0.0001f;
    }

    return 0;
}
