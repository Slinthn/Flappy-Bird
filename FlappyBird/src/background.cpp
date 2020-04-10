#include "background.h"
#include <slengine/resource.h>
#include "pipe.h"

Background::Background(Game* game, float screenW) :
	Sprite(Resource::getTexture("res/background-day.png"), 0, 0, -1),
	game(game), screenW(screenW) {

	this->width = screenW;
	this->textureW = screenW / this->texture.width;
	this->y += this->height / 2.0f;
	this->x = this->width / 2.0f;
}

void Background::update(double delta) {
	if (this->game->freeze)
		return;

	this->textureX += this->textureW / (this->screenW / (Pipe::speed * (float)delta));
	Sprite::update(delta);
}