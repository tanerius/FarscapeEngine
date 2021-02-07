#version 330

// VERTEX SHADER

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoord;

out vec2 passTextureCoord;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;


void main(void)
{
    gl_Position = vec4(inVertexPosition, 1.0);
    
    passTextureCoord = inTextureCoord;
}