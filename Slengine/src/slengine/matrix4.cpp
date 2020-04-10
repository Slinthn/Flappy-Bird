#include "matrix4.h"

Matrix4::Matrix4(float identity) {
	for (int i = 0; i < 16; i++)
		if (i % 5 == 0)
			this->d[i] = identity;
		else
			this->d[i] = 0;
}

bool Matrix4::isNormalised() {
	return 0;
}

float* Matrix4::pointer() {
	return this->d;
}

Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float near, float far) {
	Matrix4 m = Matrix4();
	// Scale
	m.d[0] = 2 / (right - left);
	m.d[5] = 2 / (top - bottom);
	m.d[10] = -2 / (far - near);

	// Translation
	m.d[3] = -((right + left) / (right - left));
	m.d[7] = -((top + bottom) / (top - bottom));
	m.d[11] = -((far + near) / (far - near));

	return m;
}