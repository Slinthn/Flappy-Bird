#pragma once
#include <slengine/window.h>
#include <slengine/spritebatch.h>
#include <slengine/sprite.h>
#include <slengine/shader.h>
#include <vector>

class Bird;
class Base;

class Game {
public:
	Window window;
	bool freeze;
	int score;
	Bird* player;
	Base* base;
private:
	Spritebatch sb;
	Shader spriteShader;
public:
	std::vector<Sprite*> sprites;
	Game();
	void update(double delta);
	void reset();
};