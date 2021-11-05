// fragment shader

// glsl version declaration
#version 430 core

// inputs from the vertex shader
in vec4 vertColor;

// the fragment shader has one output (by default) - the color of the fragment
out vec4 outColor;

void main()
{
  // TODO: do something with the vertColor here

  // the fragment shader MUST write to outColor before returning
  outColor = vertColor;
};