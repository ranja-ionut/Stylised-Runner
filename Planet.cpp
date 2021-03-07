#include "Planet.h"

Planet::Planet()
{
	modelMatrix = glm::mat4(1);
	center = glm::vec3(0);
	position = glm::vec3(0);
	length = 0;
	width = 0;
	height = 0;
	init_size = 0;
	speed = 1;
	texture = "planet1";
}

Planet::Planet(glm::vec3 center, float init_size)
{
	this->center = center;
	this->init_size = init_size;
	length = init_size;
	width = init_size;
	height = init_size;
	position = glm::vec3(0);
	modelMatrix = glm::mat4(1);
	speed = 1;
	texture = "planet1";
}

Planet::~Planet()
{
}

void Planet::setMatrix(glm::mat4 newMatrix)
{
	modelMatrix = newMatrix;
}

void Planet::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Planet::setLength(float newLength)
{
	length = newLength;
}

void Planet::setWidth(float newWidth)
{
	width = newWidth;
}

void Planet::setHeight(float newHeight)
{
	height = newHeight;
}

void Planet::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Planet::setTexture(std::string newTexture)
{
	texture = newTexture;
}

void Planet::translate(float newX, float newY, float newZ)
{
	position.x += newX;
	position.y += newY;
	position.z += newZ;
}

void Planet::scale(float scaleX, float scaleY, float scaleZ)
{
	width *= scaleX;
	height *= scaleY;
	length *= scaleZ;

	position.x *= scaleX;
	position.y *= scaleY;
	position.z *= scaleZ;
}

glm::mat4 Planet::getMatrix()
{
	return modelMatrix * Transform3D::Translate(position.x, position.y, position.z)
		* Transform3D::RotateOX(RADIANS(-90))
		* Transform3D::Scale(width / init_size, height / init_size, length / init_size);
}

glm::vec3 Planet::getCenter()
{
	return center;
}

float Planet::getLength()
{
	return length;
}

float Planet::getWidth()
{
	return width;
}

float Planet::getHeight()
{
	return height;
}

float Planet::getInitSize()
{
	return init_size;
}

int Planet::getSpeed()
{
	return speed;
}

glm::vec3 Planet::getPosition()
{
	return position;
}

std::string Planet::getTexture()
{
	return texture;
}
