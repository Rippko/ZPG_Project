#include "TextureModel.h"

TextureModel::TextureModel(std::vector<float> points)
{
	this->points = points;
	//vertex buffer object (VBO)
	this->VBO = 0;
	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * this->points.size()), this->points.data(), GL_STATIC_DRAW);
	this->VAO = 0;
	glGenVertexArrays(1, &(this->VAO)); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 6));
}

void TextureModel::drawArrays()
{
	glDrawArrays(GL_TRIANGLES, 0, (this->points.size() / 8));
}
