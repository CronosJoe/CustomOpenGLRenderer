#pragma once
#include "glew/GL/glew.h"
#include "glm/glm.hpp"

namespace aie
{
    struct vertex
    {
        glm::vec4 pos;
        glm::vec4 color;
        glm::vec2 uv;
    };

    struct geometry
    {
        GLuint vao, vbo, ibo;   // ogl buffer names
        GLuint size;            // ogl index count
    };
    struct shader
    {
        GLuint program;
    };
    struct texture
    {
        GLuint handle;          // ogl texture name
        unsigned width, height, channels;
    };
    geometry makeGeometry(const vertex* verts, GLsizei vertCount, const GLuint* const indicies, GLsizei indexCount);

    void freeGeometry(geometry& geo);

    shader makeShader(const char* vertSource, const char* fragSource);

    void freeShader(shader &shad);

    void draw(const shader &shade, const geometry& geo);

    void setUniform(const shader& shad, GLuint location, const glm::mat4& value);
    void setUniform(const shader& shad, GLuint location, const texture& value, int textureSlot);

    texture loadTexture(const char *imagePath);

    texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels);

    void freeTexture(texture& tex);

   
}
