#include "texture2D.h"

Texture2D::Texture2D() {
    glGenTextures(1, &m_id);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_id);
}

void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::generate(
    unsigned width,
    unsigned height,
    unsigned numChannels,
    const unsigned char* data
) {
    m_width = width;
    m_height = height;
    m_numChannels = numChannels;

    if (!m_formatOverride)
        updateImageFormat();
    m_formatOverride = false;

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0,
        m_imageFormat, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMag);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setInternalFormat(unsigned internalFormat) {
    m_formatOverride = true;
    m_internalFormat = internalFormat;
}

void Texture2D::setImageFormat(unsigned imageFormat) {
    m_formatOverride = true;
    m_imageFormat = imageFormat;
}

void Texture2D::setWrapS(unsigned wrapS) {
    m_wrapS = wrapS;
}

void Texture2D::setWrapT(unsigned wrapT) {
    m_wrapT = wrapT;
}

void Texture2D::setFilterMin(unsigned filterMin) {
    m_filterMin = filterMin;
}

void Texture2D::setFilterMag(unsigned filterMag) {
    m_filterMag = filterMag;
}

void Texture2D::updateImageFormat() {
    switch (m_numChannels) {
    case 1:
        m_imageFormat = GL_RED;
        m_internalFormat = GL_RED;
        break;
    case 4:
        m_imageFormat = GL_RGBA;
        m_internalFormat = GL_RGBA;
        break;
    case 3:
    default:
        m_imageFormat = GL_RGB;
        m_internalFormat = GL_RGB;
    }
}

void Texture2D::error(
    const GLchar* level,
    const GLchar* summary,
    const GLchar* message
) {
    fprintf(stderr, "TEXTURE2D::%s::%s\n%s\n", level, summary, message);
}
