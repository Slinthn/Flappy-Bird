#pragma once

struct Vector2 {
	float x, y;
	Vector2() : Vector2(0, 0) {}
	Vector2(float x, float y) : x(x), y(y) {}
	static Vector2 subtract(Vector2 a, Vector2 b) {
		return Vector2(a.x - b.x, a.y - b.y);
	}
};