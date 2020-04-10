#include "bird.h"
#include <slengine/resource.h>
#include "base.h"

Bird::Bird(Game* game, float x, float y) :
	Sprite(Resource::getTexture("res/bird.png"), x, y, 1, 0, 1.5f, 1.5f),
	game(game), vy(0), smoothRotation(0) {

	this->width = 34;
	this->height = 24;
	this->textureW = 1.0f / 3.0f;

}

void Bird::update(double delta) {
	if (!this->game->freeze) {
		static int i = 3;
		static double delay = 0;
		delay += delta;

		if (delay > 0.1) {
			delay = 0;
			this->textureX = (i % 3) / 3.0f;
			i--;
		}
	}
	
	this->vy -= 22.5f * delta;
	if (this->game->window.keyPressed(GLFW_KEY_SPACE) && !this->game->freeze) {
		this->vy = 6;
		this->smoothRotation = 0;
	}

	if (this->vy < -30)
		this->vy = -30;

	this->y += this->vy; // TODO: Should I be multiplying this by delta?
	
	float height = this->rect.tr.y - this->rect.br.y;
	float minY = this->game->base->height / 2.0f + height / 2.0f;
	float maxY = this->game->window.height - height / 2.0f;
	if (this->y < minY) {
		this->y = minY;
		this->vy = 0;
	}
	else if (this->y > maxY) {
		this->y = maxY;
		this->vy = 0;
	}

	this->smoothRotation -= vy;
	if (this->smoothRotation > 90)
		this->smoothRotation = 90;

	this->rotation += (this->smoothRotation - this->rotation) * 0.5f;

	Sprite::update(delta);
}