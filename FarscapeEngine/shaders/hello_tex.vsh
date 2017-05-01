#version 410

// VERTEX SHADER

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 texCoord0;
out vec3 surfaceNormal;
out vec3 directionToLight;

uniform mat4 MVP;
uniform mat4 TransformationMatrix;
uniform vec3 lightPosition;


void main(void)
{
    vec3 sn = (TransformationMatrix * vec4(normal, 0.0)).xyz;
    gl_Position = MVP * vec4(position, 1.0f);
    texCoord0 = texCoord;
    surfaceNormal = normalize(sn);
    directionToLight = lightPosition - sn;
}
