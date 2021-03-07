#include "Star.h"

glm::vec3 Star::starColor = YELLOW;

Star::Star()
{
	modelMatrix = glm::mat4(1);
	center = glm::vec3(0);
	position = glm::vec3(0);
	length = 0;
	width = 0;
	height = 0;
	init_size = 0;
	rendered = false;
	color = WHITE;
}

Star::Star(glm::vec3 center, float init_size)
{
	this->center = center;
	this->init_size = init_size;
	length = init_size;
	width = init_size;
	height = init_size;
	position = glm::vec3(0);
	modelMatrix = glm::mat4(1);
	rendered = false;
	color = WHITE;
}

Star::~Star()
{
}

void Star::setMatrix(glm::mat4 newMatrix)
{
	modelMatrix = newMatrix;
}

void Star::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Star::setLength(float newLength)
{
	length = newLength;
}

void Star::setWidth(float newWidth)
{
	width = newWidth;
}

void Star::setHeight(float newHeight)
{
	height = newHeight;
}

void Star::setRendered(bool render)
{
	rendered = render;
}

void Star::setColor(glm::vec3 newColor)
{
	color = newColor;
}

void Star::translate(float newX, float newY, float newZ)
{
	position.x += newX;
	position.y += newY;
	position.z += newZ;
}

void Star::scale(float scaleX, float scaleY, float scaleZ)
{
	width *= scaleX;
	height *= scaleY;
	length *= scaleZ;

	position.x *= scaleX;
	position.y *= scaleY;
	position.z *= scaleZ;
}

glm::mat4 Star::getMatrix()
{
	return modelMatrix * Transform3D::Translate(position.x, position.y, position.z)
		* Transform3D::Scale(4 * width / init_size, 4 * height / init_size, 4 * length / init_size);
}

glm::vec3 Star::getCenter()
{
	return center;
}

float Star::getLength()
{
	return length;
}

float Star::getWidth()
{
	return width;
}

float Star::getHeight()
{
	return height;
}

float Star::getInitSize()
{
	return init_size;
}

bool Star::isRendered()
{
	return rendered;
}

glm::vec3 Star::getPosition()
{
	return position;
}

glm::vec3 Star::getColor()
{
	return color;
}
