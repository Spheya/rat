#version 330 core

uniform sampler2D MainTexture;

in vec2 texCoords;
in vec3 normalWS;
in vec4 tangentWS;

out vec4 FragColor;

void main() {
    FragColor = vec4(tangentWS.xyz, 1.0);//texture(MainTexture, texCoords);
}
