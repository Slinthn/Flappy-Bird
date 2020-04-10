#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 textures;
layout(location = 2) in float texturesIndex;

out vec2 textureUV;
flat out int textureIndex;

uniform mat4 orthographic;

void main() {
	gl_Position = orthographic * vec4(vertex, 1);
	textureUV = textures;
	textureIndex = int(texturesIndex);
}