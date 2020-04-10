#pragma once
#include <slengine/sprite.h>
#include "game.h"

class Bird : public Sprite {
	Game* game;
	float smoothRotation;
public:
	float vy;
	Bird(Game* game, float x, float y);
	void update(double delta);
};