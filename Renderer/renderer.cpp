#include "renderer.h"
namespace aie 
{
	geometry aie::makeGeometry(const vertex* verts, GLsizei vertCount, const GLuint* const indicies, GLsizei indexCount)
	{
		//create an instance of geometry
		geometry newGeo = {};
		newGeo.size = indexCount;
		//creating buffers to stroe data
		glGenVertexArrays(1, &newGeo.vao);
		glGenBuffers(1, &newGeo.vbo);
		glGenBuffers(1, &newGeo.ibo);

		//bind those buffers together
		glBindVertexArray(newGeo.vao);
		glBindBuffer(GL_ARRAY_BUFFER, newGeo.vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newGeo.ibo);
		//buffed the data (aka upload to the GPU)
		glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(vertex), verts, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indicies, GL_STATIC_DRAW);
		//describe the data
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)16);
		//unbind the buffers when you're done with them
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//return the object
		return newGeo;
	}

	void freeGeometry(geometry &geo)
	{
		glDeleteBuffers(1, &geo.vbo);
		glDeleteBuffers(1, &geo.ibo);
		glDeleteBuffers(1, &geo.vao);

		geo = {}; // clear out the geo to prevent usage of it after we want it gone
	}
	shader makeShader(const char* vertSource, const char* fragSource)
	{
		//make the shader object
		shader newShade = {};
		//create the shader program
		newShade.program = glCreateProgram();
		//create the shader
		GLuint vert = glCreateShader(GL_VERTEX_SHADER);
		GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

		//load the source code
		glShaderSource(vert, 1, &vertSource, 0);
		glShaderSource(frag, 1, &fragSource, 0);
		glCompileShader(vert);
		glCompileShader(frag);
		//attach the shaders to the shader program
		glAttachShader(newShade.program, vert);
		glAttachShader(newShade.program, frag);
		//link the program
		glLinkProgram(newShade.program);
		//delete the shaders but not the program
		glDeleteShader(vert);
		glDeleteShader(frag);
		//return the shader object
		return newShade;
	}
	void freeShader(shader& shad)
	{
		glDeleteProgram(shad.program);
		shad = {};
	}
	void draw(const shader &shad, const geometry& geo)
	{
		// bind the shader program
		glUseProgram(shad.program);
		//Bind the vao
		glBindVertexArray(geo.vao);
		//draw the object - draw call
		glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, nullptr);
	}
}
