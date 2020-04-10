#include "base.h"
#include <slengine/resource.h>
#include "pipe.h"

Base::Base(Game* game, float screenW) :
	Sprite(Resource::getTexture("res/base.png"), 0, 0, .5f),
	game(game), screenW(screenW) {
	
	this->width = screenW;
	this->textureW = screenW / this->texture.width;
	this->x = this->width / 2.0f;
}

void Base::update(double delta) {
	if (this->game->freeze)
		return;

	this->textureX += this->textureW / (this->screenW / (Pipe::speed * (float)delta));
	Sprite::update(delta);
}