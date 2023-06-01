#version 330 core

in vec2 TexCoord;

uniform sampler2D Texture;

out vec4 Color;

void main()
{
    Color = texture(Texture, TexCoord);
}
