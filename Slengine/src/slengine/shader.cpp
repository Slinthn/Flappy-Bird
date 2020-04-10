#include "shader.h"
#include <fstream>
#include <GL/glew.h>
#include <cstdlib>

Shader* Shader::assigned;

static char* readFile(const char* path) {
	FILE* file;
	fopen_s(&file, path, "rb");

	fseek(file, 0, SEEK_END);
	long len = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* data = new char[len + 1];
	fread(data, 1, len, file);
	data[len] = 0;

	fclose(file);
	return data;
}

static unsigned int compileShader(char* data, unsigned int type) {
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &data, 0);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		char buffer[512];
		glGetShaderInfoLog(id, 512, 0, buffer);
		printf("Error compiling %s SHADER: %s", type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT", buffer);
		exit(0);
	}
	return id;
}

Shader::Shader(const char* vPath, const char* fPath) : id(glCreateProgram()) {
	unsigned int vId = compileShader(readFile(vPath), GL_VERTEX_SHADER);
	unsigned int fId = compileShader(readFile(fPath), GL_FRAGMENT_SHADER);

	glAttachShader(this->id, vId);
	glAttachShader(this->id, fId);
	glLinkProgram(this->id);
}

int Shader::getLocation(const char* variable) {
	int loc = glGetUniformLocation(this->id, variable);
	if (loc == -1)
		printf("Variable %s does not exist in this shader program.", variable);

	return loc;
}

void Shader::enable() {
	if (this->isEnabled())
		return;
	glUseProgram(this->id);
	Shader::assigned = this;
}

bool Shader::isEnabled() {
	return Shader::assigned == this;
}

void Shader::setMat4(const char* var, Matrix4* m) {
	if (!this->isEnabled())
		this->enable();
	glUniformMatrix4fv(this->getLocation(var), 1, !m->isNormalised(), m->pointer());
}

void Shader::setInteger(const char* var, int i) {
	if (!this->isEnabled())
		this->enable();
	glUniform1i(this->getLocation(var), i);
}

void Shader::setIntegerArray(const char* var, int size, int* i) {
	if (!this->isEnabled())
		this->enable();
	glUniform1iv(this->getLocation(var), size, i);
}

void Shader::disable() {
	glUseProgram(0);
}