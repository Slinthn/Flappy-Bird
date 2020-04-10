#include "resource.h"
#include <stb_image.h>
#include <GL/glew.h>

std::map<const char*, Texture> Resource::textures;

Texture Resource::getTexture(const char* path) {
	auto ir = Resource::textures.find(path);
	if (Resource::textures.end() == ir) {
		Texture t;
		stbi_set_flip_vertically_on_load(1);
		int n;
		unsigned char* buffer = stbi_load(path, &t.width, &t.height, &n, 0);

		glGenTextures(1, &t.id);
		glBindTexture(GL_TEXTURE_2D, t.id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t.width, t.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(buffer);
		Resource::textures.emplace(std::make_pair(path, t));
		return t;
	}
	return ir->second;
}