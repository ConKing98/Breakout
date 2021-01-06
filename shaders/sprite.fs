#version 330 core
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D image;
uniform vec3 spriteColor;

void main() {
    vec4 color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
    if (color.a < 0.1)
        discard;
    FragColor = color;
}
