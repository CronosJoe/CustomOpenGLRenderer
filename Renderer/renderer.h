#pragma once
#include "glew/GL/glew.h"
#include "glm/glm.hpp"

namespace aie
{
    struct vertex
    {
        glm::vec4 pos;
        glm::vec4 color;
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
    geometry makeGeometry(const vertex* verts, GLsizei vertCount, const GLuint* const indicies, GLsizei indexCount);

    void freeGeometry(geometry& geo);

    shader makeShader(const char* vertSource, const char* fragSource);

    void freeShader(shader &shad);

    void draw(const shader &shade, const geometry& geo);
}
