#include "renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"
#include "glm/ext.hpp"
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
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0); //float is 4 bytes
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)16);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)32); 
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)40); // 10 previous flaots to get to the start of this data
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
	void setUniform(const shader& shad, GLuint location, const glm::mat4& value)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}
	void setUniform(const shader& shad, GLuint location, const texture& value, int textureSlot)
	{
		//set up the slot
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		//bind the texture into that slot
		glBindTexture(GL_TEXTURE_2D, value.handle);

		//assign that slot to the shader
		glProgramUniform1i(shad.program, location, textureSlot);
	}
	void setUniform(const shader& shad, GLuint location, const glm::vec3& value)
	{
		glProgramUniform3fv(shad.program, location, 1, glm::value_ptr(value));
	}
	texture loadTexture(const char* imagePath)
	{
		int width, height, format;
		unsigned char* rawPixelData = nullptr;

		stbi_set_flip_vertically_on_load(true);
		rawPixelData = stbi_load(imagePath,
			&width,
			&height,
			&format,
			STBI_default);

		texture tex = makeTexture(width, height, format, rawPixelData);
		stbi_image_free(rawPixelData);
		return tex;
	}
	texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels)
	{
		texture tex = { 0, width, height, channels };

		// translate color channels into color format
		GLenum oglFormat;
		switch (channels)
		{
		case 1:
			oglFormat = GL_RED;
			break;
		case 2:
			oglFormat = GL_RG;
			break;
		case 3:
			oglFormat = GL_RGB;
			break;
		case 4:
			oglFormat = GL_RGBA;
			break;
		default:
			oglFormat = GL_RED;
			break;
		}
		glGenTextures(1, &tex.handle);
		glBindTexture(GL_TEXTURE_2D, tex.handle);
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 oglFormat,
					 width,
					 height,
					 0,
					 oglFormat,
					 GL_UNSIGNED_BYTE,
					 pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return tex;
	}
	void freeTexture(texture& tex)
	{
		glDeleteTextures(1, &tex.handle);
		tex = {};
	}
}
