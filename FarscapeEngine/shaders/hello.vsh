#version 410 core

in vec3 position;
in vec2 textureCoords;
out vec3 color;

void main(void)
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    color = vec3(0.0, 1.0, 0.0);
}
