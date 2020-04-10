#pragma once
#include "texture.h"
#include "rectangle.h"

class Sprite {
public:

	bool isPointIntersecting(Vector2 vec);
	bool isIntersecting(Sprite* other);
	bool destroyed;
	float x, y, z, rotation, scaleX, scaleY, width, height, textureX, textureY, textureW, textureH;
	Texture texture;
	Rectangle rect, collisionOffset;
	Sprite(Texture texture, float x = 0, float y = 0, float z = 0, float rotation = 0, float scaleX = 1, float scaleY = 1);
	virtual void update(double delta);
};