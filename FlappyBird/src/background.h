#pragma once
#include <slengine/sprite.h>
#include "game.h"

class Background : public Sprite {
	float screenW;
	Game* game;
public:
	Background(Game* game, float screenW);
	void update(double delta);
};