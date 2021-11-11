// fragment shader

// glsl version declaration
#version 430 core

layout (location = 3) uniform sampler2D albedo;
layout (location = 4) uniform vec3 ambientLight;
layout (location = 5) uniform vec3 lightDir;

// inputs from the vertex shader
in vec4 vertColor; //the color of each vertex
in vec2 vUV; 
in vec3 vNormal;

// the fragment shader has one output (by default) - the color of the fragment
out vec4 outColor;

void main()
{
   float d = max(0.0f, dot(vNormal, -lightDir));
   vec3 diffuse = d * vec3(1,1,1); //could also be written as vec3(d)

   vec4 tmpColor = texture(albedo, vUV) * vertColor; //applying vertex color and the albedo value
  // the fragment shader MUST write to outColor before returning

  outColor.rgb = tmpColor.rgb * (ambientLight + diffuse); //applying the light value
  outColor.a = tmpColor.a;
};