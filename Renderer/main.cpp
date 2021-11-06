#include "context.h"
#include "renderer.h"
#include "filePull.h"
#include "GLM/ext.hpp"
using namespace aie;


int main()
{
	context window;
	window.init(640, 480, "Hello There");
	//create a triangle
	vertex triVerts[] =
	{
		{ //vertex 0 -bottom left
			{-.5f, -.5f, 0,1}, {1.0,0.0,0.0,1.0}, {0,0}
		},
		{ //vertex 0 -bottom right
			{.5f, -.5f, 0,1}, {0.0,1.0,0.0,1.0}, {1,0}
		},
		{ //vertex 0 -top middle
			{0.0f, .5f, 0,1}, {0.0,0.0,1.0,1.0}, {0.5f,1.0f}
		}
	};
	// bottom left => bottom right => top middle
	unsigned int triIndices[] = { 0, 1, 2 };

	geometry basicTriangleGeo = makeGeometry(triVerts, 3, triIndices,3);

	////create a square
	//vertex quadVerts[] =
	//{
	//	{ //vertex 0 -bottom left
	//		{-.5f, -.5f, 0, 1}, {0.0,1.0,0.0,1.0}
	//	},
	//	{ //vertex 0 -bottom right
	//		{.5f, -.5f, 0, 1}, {1.0,0.0,0.0,1.0}
	//	},
	//	{ //vertex 0 -top right
	//		{.5f, .5f, 0, 1}, {0.0,0.0,1.0,1.0}
	//	},
	//	{ //vertex 0 -top left
	//		{-.5f, .5f, 0, 1}, {1.0,1.0,1.0,1.0}
	//	}
	//};
	////bottom left 0  > bottom right 1 > top right 2> top left 3 > bottom left 0 > top right 2
	//unsigned int sixIndices[] = { 0,1,2,3,0,2 };
	//geometry basicPlaneGeo = makeGeometry(quadVerts, 6, sixIndices, 6);
		//create a cube
	//vertex Square[] =
	//{
	//	{ //vertex 0 -front bottom left
	//		{-.5f, -.5f, .5f, 1}, {0.0,1.0,0.0,1.0}
	//	},
	//	{ //vertex 0 -front bottom right
	//		{.5f, -.5f, .5f, 1}, {1.0,0.0,0.0,1.0}
	//	},
	//	{ //vertex 0 -front top right
	//		{.5f, .5f, .5f, 1}, {0.0,0.0,1.0,1.0}
	//	},
	//	{ //vertex 0 -front top left
	//		{-.5f, .5f, .5f, 1}, {1.0,1.0,1.0,1.0}
	//	},
	//	{ //vertex 0 - back top left
	//		{-.5f, .5f, -.5f, 1}, {1.0,1.0,1.0,1.0}
	//	},
	//	{ //vertex 0 -back bottom left
	//		{-.5f, -.5f, -.5f, 1}, {0.0,1.0,0.0,1.0}
	//	},
	//	{ //vertex 0 -back bottom right
	//		{.5f, -.5f, -.5f, 1}, {1.0,0.0,0.0,1.0}
	//	},
	//	{ //vertex 0 -back top right
	//		{.5f, .5f, -.5f, 1}, {0.0,0.0,1.0,1.0}
	//	}
	//};
	////bottom left 0  > bottom right 1 > top right 2> top left 3 > bottom left 0 > top right 2
	//unsigned int tooManyIndices[] = { 0,1,2,3,0,2 };
	//geometry basicThirdPersonSquare = makeGeometry(Square, 6, tooManyIndices, 6);

	//create a shader
	shader basicShad = loadShader("new.vert", "new.frag"); // loading the shaders
	texture checker = loadTexture("uvchecker.jpg");
	glm::mat4 tri_model = glm::identity<glm::mat4>(); // needs to have #include "GLM/ext.hpp"

	// creates a scaling matrix
	tri_model = glm::scale(tri_model, glm::vec3(2, 2,2));
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0,1,5), //eye
									 glm::vec3(0,0,0), //lookout
									 glm::vec3(0,1,0)); //up
	glm::mat4 cam_proj = glm::perspective(glm::radians(60.0f), //fov
										  640.0f / 480.0f, // aspect ratio
										  0.1f, //near plane
										  100.0f); //far plane


	while(!window.shouldClose())
	{
		//update
		window.tick();
		tri_model = glm::rotate(tri_model, 0.2f, glm::vec3(0, 1, 0));
		//draw
		window.clear(); //clear previous frames stuff
		
		//Setting uniforms
		setUniform(basicShad, 0, cam_proj);
		setUniform(basicShad, 1, cam_view);
		setUniform(basicShad, 2, tri_model);
		
		setUniform(basicShad, 3, checker, 0);
		//draw a shape
		draw(basicShad, basicTriangleGeo);

		//draw a square
		/*draw(basicShad, basicPlaneGeo);*/
	}
	window.term();
	return 0;
}