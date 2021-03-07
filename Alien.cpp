#include "Alien.h"

glm::vec3 Alien::alienColor = BLUE;

Alien::Alien()
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
	direction = glm::vec3(0, -1, 0);
}

Alien::Alien(glm::vec3 center, float init_size)
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
	direction = glm::vec3(0, -1, 0);
}

Alien::~Alien()
{
}

void Alien::setMatrix(glm::mat4 newMatrix)
{
	modelMatrix = newMatrix;
}

void Alien::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Alien::setLength(float newLength)
{
	length = newLength;
}

void Alien::setWidth(float newWidth)
{
	width = newWidth;
}

void Alien::setHeight(float newHeight)
{
	height = newHeight;
}

void Alien::setRendered(bool render)
{
	rendered = render;
}

void Alien::setColor(glm::vec3 newColor)
{
	color = newColor;
}

void Alien::setDirection(glm::vec3 newDirection)
{
	direction = newDirection;
}

void Alien::updateDirection(float deltaTimeSeconds)
{
	static float time = 0;
		
	time += deltaTimeSeconds;

	direction = glm::vec3(direction.x, direction.y, 0.35f * sin(time / 2));
}

void Alien::translate(float newX, float newY, float newZ)
{
	position.x += newX;
	position.y += newY;
	position.z += newZ;
}

void Alien::scale(float scaleX, float scaleY, float scaleZ)
{
	width *= scaleX;
	height *= scaleY;
	length *= scaleZ;

	position.x *= scaleX;
	position.y *= scaleY;
	position.z *= scaleZ;
}

glm::mat4 Alien::getMatrix()
{
	return modelMatrix * Transform3D::Translate(position.x, position.y, position.z)
		* Transform3D::Scale(width / init_size, height / init_size, length / init_size);
}

glm::vec3 Alien::getCenter()
{
	return center;
}

float Alien::getLength()
{
	return length;
}

float Alien::getWidth()
{
	return width;
}

float Alien::getHeight()
{
	return height;
}

float Alien::getInitSize()
{
	return init_size;
}

bool Alien::isRendered()
{
	return rendered;
}

glm::vec3 Alien::getPosition()
{
	return position;
}

glm::vec3 Alien::getColor()
{
	return color;
}

glm::vec3 Alien::getDirection()
{
	return direction;
}
