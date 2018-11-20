// Recommended for OpenGL 3.0 or lastest versions
#include "core/common.h"
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "gameEventHandler.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>

#define WIDTH 1600
#define HEIGHT 900

typedef glm::vec3 Vector3f;
typedef glm::vec2 Vector2f;

int main()
{
    Display display(WIDTH, HEIGHT, "BVoxel Test Window");
    GameEventHandler eventHandler;
    
    InputControl xAxis;
    InputControl yAxis;
    InputControl zAxis;
    InputControl rotAxis;

    /*
    eventHandler.addKeyControl(Input::KEY_A, yAxis, -1.0f);
    eventHandler.addKeyControl(Input::KEY_D, yAxis, 1.0f);
    eventHandler.addKeyControl(Input::KEY_LEFT, yAxis, -1.0f);
    eventHandler.addKeyControl(Input::KEY_RIGHT, yAxis, 1.0f);
    eventHandler.addKeyControl(Input::KEY_W, zAxis, 1.0f);
    eventHandler.addKeyControl(Input::KEY_S, zAxis, -1.0f);
    eventHandler.addKeyControl(Input::KEY_UP, zAxis, 1.0f);
    eventHandler.addKeyControl(Input::KEY_DOWN, zAxis, -1.0f);
    */

    eventHandler.addKeyControl(Input::KEY_A, yAxis, -1.0f);
    eventHandler.addKeyControl(Input::KEY_D, yAxis, 1.0f);
    eventHandler.addKeyControl(Input::KEY_LEFT, yAxis, -1.0f);
    eventHandler.addKeyControl(Input::KEY_RIGHT, yAxis, 1.0f);
    eventHandler.addKeyControl(Input::KEY_W, xAxis, 1.0f);
    eventHandler.addKeyControl(Input::KEY_S, xAxis, -1.0f);
    eventHandler.addKeyControl(Input::KEY_UP, xAxis, 1.0f);
    eventHandler.addKeyControl(Input::KEY_DOWN, xAxis, -1.0f);
    eventHandler.addKeyControl(Input::KEY_Q, rotAxis, 1.0f);
    eventHandler.addKeyControl(Input::KEY_E, rotAxis, -1.0f);

    Vertex vertices[] = { Vertex(Vector3f(-0.5f, -0.5f, 0.0f), Vector2f(0.0f, 0.0f)),
                          Vertex(Vector3f(0.0f, 0.5f, 0.0f), Vector2f(0.5f, 1.0f)),
                          Vertex(Vector3f(0.5f, -0.5f, 0.0f), Vector2f(1.0f, 0.0f)) };
    
    unsigned int indices[] = { 0, 1, 2 };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
    Mesh mesh2("./res/basicman.obj");
    Shader shader("./res/basicShader");
    Texture texture("./res/bricks.jpg");
    Camera camera(Vector3f(0, 0, -24), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
    Transform transform;

    float xPos = 0.0f;
    float yPos = 0.0f;
    float zPos = 0.0f;
    float rot  = 0.0f;

    while(!display.isClosed())
    {
        display.clear(0.0f, 0.15f, 0.3f, 1.0f);

        xPos = xAxis.getAmt()   / 250.0f;
        yPos = yAxis.getAmt()   / 250.0f;
        zPos = zAxis.getAmt()   / 250.0f;
        rot  = rotAxis.getAmt() / 500.0f;

        transform.setTranslation(Vector3f(xPos, yPos, zPos));
        transform.setRotation(Vector3f(0.0f, 0.0f, rot));

        shader.bind();
        texture.bind(0);
        shader.update(transform, camera);
        mesh2.draw();

        display.update(eventHandler);

        // Monitoring
        std::cout <<
        "x: " << '(' << transform.getPos().x << ')' << " : " <<
        "y: " << '(' << transform.getPos().y << ')' << " : " <<
        "z: " << '(' << transform.getPos().z << ')' <<
        std::endl;
        // Monitoring
    }
    return 0;
}
