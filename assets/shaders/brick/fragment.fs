#version 330 core

out vec4 color;
uniform vec3 brickColor;

void main() {
    color = vec4(brickColor, 1.0f);
}
