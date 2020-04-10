#include "pipe.h"
#include <slengine/resource.h>
#include "bird.h"

const float Pipe::speed = 170.0f;

Pipe::Pipe(Game* game, float x, float y, float rotation) : Sprite(Resource::getTexture("res/pipe-green.png"), x, y, 0, rotation, rotation == 180 ? -1.5f : 1.5f, 1.5f), game(game) {
}

void Pipe::update(double delta) {
	if (this->game->freeze)
		return;

	x -= Pipe::speed * (float)delta;
	float width = (this->rect.tr.x - this->rect.tl.x);
	if (x < -width) {
		this->destroyed = 1;
		return;
	}
	Sprite::update(delta);

	if (!this->game->freeze) {
		Bird* b = this->game->player;
		if (this->isIntersecting(b)) {
			b->vy = 4;
			this->game->freeze = 1;
		}
	}
}