#include "spritebatch.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <GL/glew.h>

static bool sortStyle(Sprite* s1, Sprite* s2) {
	return s1->texture.id < s2->texture.id;
}

Spritebatch::Spritebatch() {
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 6 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, 0, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 1, GL_FLOAT, 0, 6 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

	glBindVertexArray(0);
}

void Spritebatch::draw(Sprite* s) {
	this->sprites.push_back(s);
}

void Spritebatch::flush() {
	int amt = this->sprites.size();
	if (amt == 0)
		return;
	// TODO: Change sort to render lower z first then higher z? Sorting by texture doesn't exactly matter
	// The code would only have to be changed to expect texture ids not in order but by random
	std::sort(this->sprites.begin(), this->sprites.end(), sortStyle);
	float* data = new float[amt * 24];
	int* indices = new int[amt * 6];
	Texture* currentTexture = nullptr;

	int texture = -1;
	for (int i = 0; i < amt; i++) {
		Sprite* s = this->sprites[i];
		if (currentTexture == nullptr || currentTexture->id != s->texture.id) {
			texture++;
			currentTexture = &s->texture;
			glActiveTexture(GL_TEXTURE0 + texture);
			glBindTexture(GL_TEXTURE_2D, currentTexture->id);
		}

		// TL
		data[0 + i * 24] = s->rect.tl.x;
		data[1 + i * 24] = s->rect.tl.y;
		data[2 + i * 24] = s->z;
		data[3 + i * 24] = s->textureX;
		data[4 + i * 24] = s->textureY + s->textureH;
		data[5 + i * 24] = (float)texture;

		// BL
		data[6 + i * 24] = s->rect.bl.x;
		data[7 + i * 24] = s->rect.bl.y;
		data[8 + i * 24] = s->z;
		data[9 + i * 24] = s->textureX;
		data[10 + i * 24] = s->textureY;
		data[11 + i * 24] = (float)texture;

		// BR
		data[12 + i * 24] = s->rect.br.x;
		data[13 + i * 24] = s->rect.br.y;
		data[14 + i * 24] = s->z;
		data[15 + i * 24] = s->textureX + s->textureW;
		data[16 + i * 24] = s->textureY;
		data[17 + i * 24] = (float)texture;

		// TR
		data[18 + i * 24] = s->rect.tr.x;
		data[19 + i * 24] = s->rect.tr.y;
		data[20 + i * 24] = s->z;
		data[21 + i * 24] = s->textureX + s->textureW;
		data[22 + i * 24] = s->textureY + s->textureH;
		data[23 + i * 24] = (float)texture;

		// Indices
		indices[0 + i * 6] = 0 + i * 4;
		indices[1 + i * 6] = 1 + i * 4;
		indices[2 + i * 6] = 2 + i * 4;
		indices[3 + i * 6] = 2 + i * 4;
		indices[4 + i * 6] = 3 + i * 4;
		indices[5 + i * 6] = 0 + i * 4;
	}

	glBindVertexArray(this->vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * amt * 24, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * amt * 24, data);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * amt * 6, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(int) * amt * 6, indices);

	glDrawElements(GL_TRIANGLES, amt * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	this->sprites.resize(0);
	delete[] data, indices;
}