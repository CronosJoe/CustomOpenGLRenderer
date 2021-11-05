#include "context.h"

#include "glew/GL/glew.h" // glew needs to be first it's picky that way with GL stuff
#include "GLFW/glfw3.h"

#include <iostream>

// Error callback called by OpenGL whenever a problem occurs (vendor-dependent)
void APIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message,
	const void* userParam)
{
	std::cerr << message << std::endl;
}
bool aie::context::init(int width, int height, const char* title)
{
	//init glfw
	glfwInit();
	//create window
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	//set active
	glfwMakeContextCurrent(window);

	//init glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		return false;
	}

	std::cout << "OpenGL Version: " << (const char*)glGetString(GL_VERSION) << "\n";
	std::cout << "Renderer: " << (const char*)glGetString(GL_RENDERER) << "\n";
	std::cout << "Vendor: " << (const char*)glGetString(GL_VENDOR) << "\n";
	std::cout << "GLSL: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n"; // "\n"; is the same as std::endl;

#if _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif


	glEnable(GL_BLEND); // blending
	glEnable(GL_DEPTH_TEST); // depth testing
	glEnable(GL_CULL_FACE); // culling

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // set the blend function
	glDepthFunc(GL_LEQUAL);                             // depth test function
	glFrontFace(GL_CCW);                                // set front face winding order
	glCullFace(GL_BACK);                                // cull backfaces

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	//update-draw loop
	return true;
}

void aie::context::tick()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void aie::context::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void aie::context::term()
{
	//destroying the window
	glfwDestroyWindow(window);
	//terminating glfw
	glfwTerminate();
}

bool aie::context::shouldClose() const
{
	return glfwWindowShouldClose(window);
}
