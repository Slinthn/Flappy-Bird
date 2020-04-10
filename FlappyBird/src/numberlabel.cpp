#include "numberlabel.h"

NumberLabel::NumberLabel(Game* game, int digit, float x, float y) :
	Sprite(Resource::getTexture("res/numbers.png"), x, y, 0.5f, 0, 1.5f, 1.5f), digit(digit), game(game) {

	this->width = 24;
	this->height = 36;
	this->textureW = 1.0f / 10.0f;
	this->textureH = 1;
}

void NumberLabel::update(double delta) {
	Sprite::update(delta);

	int num = (int)((double)this->game->score / pow(10, this->digit)) % 10;
	this->textureX = (num % 10) / 10.0f;
}