#include "game.h"
#include <slengine/resource.h>
#include "bird.h"
#include "pipe.h"
#include "numberlabel.h"
#include "background.h"
#include "base.h"
#include <ctime>

#define WIN_WIDTH 500
#define WIN_HEIGHT 500
static Game* game;

void intrUpdate(double delta) {
	game->update(delta);
}

Game::Game() :
	window(Window(WIN_WIDTH, WIN_HEIGHT, "2D")), spriteShader(Shader("res/sprite.vsh", "res/sprite.fsh")),
	player(new Bird(this, WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0)), freeze(0), score(0) {
	game = this;

	this->window.setIcon("res/flappy.png");

	this->spriteShader.setMat4("orthographic", &Matrix4::orthographic(0, (float)WIN_WIDTH, 0, (float)WIN_HEIGHT, -2, 2));
	this->spriteShader.setIntegerArray("textures", 32, new int[32]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 });

	this->reset();
	this->window.start(intrUpdate, 60.0);
}

void Game::update(double delta) {
	this->window.clear(1, 1, 1);
	for (int i = 0; i < this->sprites.size(); i++)
		if (i < this->sprites.size() && this->sprites[i]->destroyed) {
			delete this->sprites[i];
			this->sprites.erase(this->sprites.begin() + i);
		}

	for (Sprite* s : sprites) {
		s->update(delta);
		this->sb.draw(s);
	}

	this->sb.flush();
	this->window.swapBuffers();

	if (!this->freeze) {
		const double delay = 1.25;
		static double time = delay;
		time += delta;

		while (time > delay) {
			double bottom = -170.0 + (double)(rand() % (260));
			double forward = (double)Pipe::speed * (time - delay);
			this->score++;
			this->sprites.push_back(new Pipe(this, WIN_WIDTH + 52 - forward, bottom, 0));
			this->sprites.push_back(new Pipe(this, WIN_WIDTH + 52 - forward, bottom + 490 + 140, 180));
			time -= delay;
		}
	}

	if (this->freeze) {
		static double delay = 0;
		delay += delta;
		if (delay > 1 && this->window.keyPressed(GLFW_KEY_SPACE)) {
			this->reset();
			delay = 0;
		}
	}
}

void Game::reset() {
	srand(time(0));

	this->freeze = 0;
	this->score = 0;
	for (Sprite* s : this->sprites)
		delete s;
	this->sprites.resize(0);


	NumberLabel* l = new NumberLabel(this, 1, 0, WIN_HEIGHT - 50);
	l->update(0);
	l->x = WIN_WIDTH / 2.0f - (l->rect.tr.x - l->rect.tl.x) / 2.0f - 5;
	this->sprites.push_back(l);

	l = new NumberLabel(this, 0, 0, WIN_HEIGHT - 50);
	l->update(0);
	l->x = WIN_WIDTH / 2.0f + (l->rect.tr.x - l->rect.tl.x) / 2.0f + 5;
	this->sprites.push_back(l);

	this->base = new Base(this, WIN_WIDTH);
	this->sprites.push_back(this->base);
	this->sprites.push_back(new Background(this, WIN_WIDTH));

	this->player = new Bird(this, WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0);
	this->sprites.push_back(this->player);
}