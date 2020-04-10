#pragma once
#include <vector>
#include "sprite.h"

class Spritebatch {
	unsigned int vao, vbo, ebo;
	std::vector<Sprite*> sprites;
public:
	Spritebatch();
	void draw(Sprite* sprite);
	void flush();
};