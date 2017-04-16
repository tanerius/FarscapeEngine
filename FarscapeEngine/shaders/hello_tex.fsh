#version 410

in vec2 TexCoord;
in vec3 color;

out vec4 out_color;

uniform sampler2D textureSampler;

void main(void)
{
    out_color = texture(textureSampler,TexCoord);
}
