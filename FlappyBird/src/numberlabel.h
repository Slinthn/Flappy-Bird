#pragma once
#include <slengine/sprite.h>
#include <slengine/resource.h>
#include "game.h"

class NumberLabel : public Sprite {
	Game* game;
	int digit;
public:
	NumberLabel(Game* game, int digit, float x, float y);
	void update(double delta);
};