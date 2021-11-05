#include "context.h"
#include "renderer.h"
#include "filePull.h"

using namespace aie;


int main()
{
	context window;
	window.init(640, 480, "Hello There");
	//create a triangle
	vertex triVerts[] =
	{
		{ //vertex 0 -bottom left
			{-.5f, -.5f, 0,1}, {1.0,0.0,0.0,1.0}
		},
		{ //vertex 0 -bottom right
			{.5f, -.5f, 0,1}, {0.0,1.0,0.0,1.0}
		},
		{ //vertex 0 -top middle
			{0.0f, .5f, 0,1}, {0.0,0.0,1.0,1.0}
		}
	};
	// bottom left => bottom right => top middle
	unsigned int triIndices[] = { 0, 1, 2 };

	geometry basicTriangleGeo = makeGeometry(triVerts, 3, triIndices,3);

	//create a square
	//vertex quadVerts[] =
	//{
	//	{ //vertex 0 -bottom left
	//		{-.5f, -.5f, 0, 1}, {1.0,0.0,0.0,1.0}
	//	},
	//	{ //vertex 0 -bottom right
	//		{.5f, -.5f, 0, 1}, {1.0,0.0,0.0,1.0}
	//	},
	//	{ //vertex 0 -top right
	//		{.5f, .5f, 0, 1}, {1.0,0.0,0.0,1.0}
	//	},
	//	{ //vertex 0 -top left
	//		{-.5f, .5f, 0, 1}, {1.0,0.0,0.0,1.0}
	//	}
	//};
	////bottom left 0  > bottom right 1 > top right 2> top left 3 > bottom left 0 > top right 2
	//unsigned int sixIndices[] = { 0,1,2,3,0,2 };
	//geometry basicPlaneGeo = makeGeometry(quadVerts, 6, sixIndices, 6);

	//create a shader
	/*const char *basicVert =
		"#version 430 core\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec4 color;\n"
		"out vec4 vertColor; \n"
		"void main () {gl_Position = position; vertColor = color; }";

	const char* basicFrag =
		"#version 430 core\n"
		"in vec4 vertColor; \n"
		"out vec4 outColor; \n"
		"void main() { outColor = vertColor;}";*/

	shader basicShad = loadShader("basic.vert", "basic.frag");

	while(!window.shouldClose())
	{
		//update
		window.tick();
		//draw
		window.clear(); //clear previous frames stuff
		//draw a triangle
		draw(basicShad, basicTriangleGeo);

		//draw a square
		/*draw(basicShad, basicPlaneGeo);*/
	}
	window.term();
	return 0;
}