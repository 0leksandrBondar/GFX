#version 460 core

out vec4 FragColor;

in vec2 vUV;

uniform sampler2D uTexture;
uniform vec4 uColor;

void main()
{
    FragColor = texture(uTexture, vUV) * uColor;
}
