#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Texture2D {
public:
    Texture2D();
    ~Texture2D();

    void bind();
    void generate(unsigned width, unsigned height, unsigned numChannels, const unsigned char* data);

    void setInternalFormat(unsigned internalFormat);
    void setImageFormat(unsigned imageFormat);
    void setWrapS(unsigned wrapS);
    void setWrapT(unsigned wrapT);
    void setFilterMin(unsigned filterMin);
    void setFilterMag(unsigned filterMag);

private:
    void updateImageFormat();

    static void error(const GLchar* level, const GLchar* summary, const GLchar* message);

    unsigned m_id;
    unsigned m_width = 0;
    unsigned m_height = 0;
    unsigned m_numChannels = 0;
    unsigned m_internalFormat = GL_RGB;
    unsigned m_imageFormat = GL_RGB;
    unsigned m_wrapS = GL_REPEAT;
    unsigned m_wrapT = GL_REPEAT;
    unsigned m_filterMin = GL_LINEAR;
    unsigned m_filterMag = GL_LINEAR;
    bool m_formatOverride = false;
};
