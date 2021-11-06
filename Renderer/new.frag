// fragment shader

// glsl version declaration
#version 430 core

layout (location = 3) uniform sampler2D albedo;

// inputs from the vertex shader
in vec4 vertColor;
in vec2 vUV;

// the fragment shader has one output (by default) - the color of the fragment
out vec4 outColor;

void main()
{
   outColor = texture(albedo, vUV);
  // the fragment shader MUST write to outColor before returning
  outColor *= vertColor;
};