#version 460 core

out vec4 FragColor;

in vec2 vUV;

uniform sampler2D uFontAtlas;
uniform vec4 uColor;

void main()
{
    float alpha = texture(uFontAtlas, vUV).r;
    FragColor = vec4(uColor.rgb, uColor.a * alpha);
}
