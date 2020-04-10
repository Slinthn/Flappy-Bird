#pragma once
#include "texture.h"
#include <map>

class Resource {
private:
	static std::map<const char*, Texture> textures;
public:
	static Texture getTexture(const char* path);
};