#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;

out vec3 color;
out vec2 TexCoord;

uniform mat4 transformationMatrix;

void main(void)
{
    gl_Position = transformationMatrix * vec4(position, 1.0f);
    TexCoord = textureCoords;
    color = vec3(0.0, 1.0, 0.0);
}
