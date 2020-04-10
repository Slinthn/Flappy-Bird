#include "sprite.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

Sprite::Sprite(Texture t, float x, float y, float z, float rotation, float scaleX, float scaleY) :
	texture(t), x(x), y(y), z(z), width(t.width), height(t.height),
	rotation(rotation), scaleX(scaleX), scaleY(scaleY),
	textureX(0), textureY(0), textureW(1), textureH(1), destroyed(0) {

	this->collisionOffset.bl = Vector2();
	this->collisionOffset.tl = Vector2();
	this->collisionOffset.br = Vector2();
	this->collisionOffset.tr = Vector2();
}

bool Sprite::isPointIntersecting(Vector2 p) {
	std::vector<Vector2> points;
	points.push_back(Vector2::subtract(this->rect.tr, this->collisionOffset.tr));
	points.push_back(Vector2::subtract(this->rect.tl, this->collisionOffset.tl));
	points.push_back(Vector2::subtract(this->rect.br, this->collisionOffset.br));
	points.push_back(Vector2::subtract(this->rect.bl, this->collisionOffset.bl));
	int i, j, nvert = points.size();
	bool c = false;

	for (i = 0, j = nvert - 1; i < nvert; j = i++)
		if (
			((points[i].y >= p.y) != (points[j].y >= p.y)) &&
			(p.x <= (points[j].x - points[i].x) * (p.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)
			)
			c = !c;

	return c;
}

bool Sprite::isIntersecting(Sprite* other) {
	return isPointIntersecting(other->rect.tr) || isPointIntersecting(other->rect.tl)
		|| isPointIntersecting(other->rect.br) || isPointIntersecting(other->rect.bl);
}

void Sprite::update(double delta) {
	if (destroyed)
		return;

	float x = this->x;
	float y = this->y;
	float sx = this->scaleX;
	float sy = this->scaleY;
	float ar = -this->rotation * M_PI / 180.0f;
	float ca = (float)cos(ar);
	float sa = (float)sin(ar);
	float tw = this->width / 2.0f;
	float th = this->height / 2.0f;

	this->rect.tl.x = sx * ((-tw * ca) - (+th * sa)) + x;
	this->rect.tl.y = sy * ((-tw * sa) + (+th * ca)) + y;

	this->rect.bl.x = sx * ((-tw * ca) - (-th * sa)) + x;
	this->rect.bl.y = sy * ((-tw * sa) + (-th * ca)) + y;

	this->rect.br.x = sx * ((+tw * ca) - (-th * sa)) + x;
	this->rect.br.y = sy * ((+tw * sa) + (-th * ca)) + y;

	this->rect.tr.x = sx * ((+tw * ca) - (+th * sa)) + x;
	this->rect.tr.y = sy * ((+tw * sa) + (+th * ca)) + y;
}