#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 color;
layout(location = 4) in vec4 tangent;

layout(location = 5) in mat4 matrix_m;

out vec2 texCoords;
out vec3 normalWS;
out vec4 tangentWS;

layout(std140) uniform Camera {
    mat4 matrix_p;
    mat4 matrix_v;
};

void main() {
    texCoords = uv;
    normalWS = (matrix_m * vec4(normal, 0.0)).xyz;
    tangentWS = vec4((matrix_m * vec4(tangent.xyz, 0.0)).xyz, tangent.w);
    gl_Position = matrix_p * matrix_v * matrix_m * vec4(position, 1.0);
}
