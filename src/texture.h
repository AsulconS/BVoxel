#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"

#include <GL/glew.h>
#include <string>
#include <cassert>
#include <iostream>

class Texture
{
private:
    GLuint texture;

public:
    Texture(const std::string& fileName);
    virtual ~Texture();

    void bind(unsigned int unit);
};

#endif // TEXTURE_H
