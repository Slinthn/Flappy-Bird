#pragma once

class Matrix4 {
	float d[16];
public:
	Matrix4(float identity = 1);
	bool isNormalised();
	float* pointer();
	static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
};