#pragma once
#include "matrix4.h"

class Shader {
private:
	unsigned int id;
	static Shader* assigned;
	int getLocation(const char* variable);
public:
	Shader(const char* vPath, const char* fPath);
	void enable();
	bool isEnabled();
	void setMat4(const char* variable, Matrix4* matrix);
	void setInteger(const char* variabe, int integer);
	void setIntegerArray(const char* variabe, int size, int* integers);
	static void disable();
};