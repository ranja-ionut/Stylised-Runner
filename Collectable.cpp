#include "Collectable.h"

Collectable::Collectable()
{
	modelMatrix = glm::mat4(1);
	center = glm::vec3(0);
	position = glm::vec3(0);
	length = 0;
	width = 0;
	height = 0;
	init_size = 0;
	rendered = false;
}

Collectable::Collectable(glm::vec3 center, float init_size)
{
	this->center = center;
	this->init_size = init_size;
	length = init_size;
	width = init_size;
	height = init_size;
	position = glm::vec3(0);
	modelMatrix = glm::mat4(1);
	rendered = false;
}

Collectable::~Collectable()
{
}

void Collectable::setMatrix(glm::mat4 newMatrix)
{
	modelMatrix = newMatrix;
}

void Collectable::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Collectable::setLength(float newLength)
{
	length = newLength;
}

void Collectable::setWidth(float newWidth)
{
	width = newWidth;
}

void Collectable::setHeight(float newHeight)
{
	height = newHeight;
}

void Collectable::setRendered(bool render)
{
	rendered = render;
}

void Collectable::checkHit(Player* player)
{
	glm::vec3 sphere = player->getPosition();

	float x = std::max(-0.75f * width / 2 + position.x, std::min(sphere.x, 0.75f * width / 2 + position.x));
	float y = std::max(-0.75f * height / 2 + position.y, std::min(sphere.y, 0.75f * height / 2 + position.y));
	float z = std::max(-0.75f * length / 2 + position.z, std::min(sphere.z, 0.75f * length / 2 + position.z));

	float distance = sqrtf((x - sphere.x) * (x - sphere.x) +
		(y - sphere.y) * (y - sphere.y) +
		(z - sphere.z) * (z - sphere.z));

	bool gotHit = distance < player->getDiameter();

	if (gotHit && rendered) {
		player->setScore(10);
		rendered = false;
	}
}

void Collectable::translate(float newX, float newY, float newZ)
{
	position.x += newX;
	position.y += newY;
	position.z += newZ;
}

void Collectable::scale(float scaleX, float scaleY, float scaleZ)
{
	width *= scaleX;
	height *= scaleY;
	length *= scaleZ;

	position.x *= scaleX;
	position.y *= scaleY;
	position.z *= scaleZ;
}

glm::mat4 Collectable::getMatrix(float deltaTimeSeconds)
{
	static float time = 0;

	time += deltaTimeSeconds * 0.035f;

	return modelMatrix * Transform3D::Translate(position.x, position.y + 0.3f * sin(time), position.z)
		* Transform3D::Scale(width / init_size * 0.75f, height / init_size * 0.75f, length / init_size * 0.75f)
		* Transform3D::RotateOY(time);
}

glm::vec3 Collectable::getCenter()
{
	return center;
}

float Collectable::getLength()
{
	return length;
}

float Collectable::getWidth()
{
	return width;
}

float Collectable::getHeight()
{
	return height;
}

float Collectable::getInitSize()
{
	return init_size;
}

bool Collectable::isRendered()
{
	return rendered;
}

glm::vec3 Collectable::getPosition()
{
	return position;
}
