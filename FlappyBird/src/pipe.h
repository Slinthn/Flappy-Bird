#pragma once
#include <slengine/sprite.h>
#include "game.h"

class Pipe : public Sprite {
	Game* game;
public:
	static const float speed;
	Pipe(Game* game, float x, float y, float rotation);
	void update(double delta);
};
