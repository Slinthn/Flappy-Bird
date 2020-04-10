#version 330 core
out vec4 colour;

in vec2 textureUV;
flat in int textureIndex;

uniform sampler2D textures[32];

void main() {
	colour = texture(textures[textureIndex], textureUV);
	if (colour.a < 0.1)
		discard; // TODO: Change? **Maybe** not good for performance
}