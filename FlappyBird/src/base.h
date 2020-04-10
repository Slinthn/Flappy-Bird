#pragma once
#include <slengine/sprite.h>
#include <slengine/resource.h>
#include "game.h"

class Base : public Sprite {
	Game* game;
	float screenW;
public:
	Base(Game* game, float screenW);
	void update(double delta);
};