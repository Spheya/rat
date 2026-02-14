#version 330 core

uniform sampler2D MainTexture;

in vec2 texCoords;

out vec4 FragColor;


void main() {
    FragColor = texture(MainTexture, texCoords);
}
