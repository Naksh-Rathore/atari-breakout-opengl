#version 330 core

out vec4 color;

in vec2 texCoord;

uniform sampler2D textureSampler;
uniform vec3 brickColor;

void main() {
    color = texture(textureSampler, texCoord) * vec4(brickColor, 1.0f);
}
