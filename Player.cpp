#include "Player.h"

Player::Player()
{
	modelMatrix = glm::mat4(1);
	center = glm::vec3(0);
	diameter = 0;
	position = glm::vec3(0);
	ground = 0;
	oldGround = ground;
	jumping = false;
	falling = false;
	death = false;
	fuel = PLAYER_MAX_FUEL;
	fallTime = 0;
	acceleration = 0;
	oldAccel = 0;
	minAccel = 0;
	deathTime = 0;
	deathType = 2;
	difficultyTimer = 0;
	score = 0;
	shields = 2;
}

Player::Player(glm::vec3 center, float diameter)
{
	modelMatrix = glm::mat4(1);
	position = glm::vec3(0);
	ground = 0;
	oldGround = ground;
	jumping = false;
	falling = false;
	death = false;
	fuel = PLAYER_MAX_FUEL;
	fallTime = 0;
	acceleration = 0;
	deathTime = 0;
	deathType = 2;
	oldAccel = 0;
	minAccel = 0;
	difficultyTimer = 0;
	this->center = center;
	this->diameter = diameter;
	score = 0;
	shields = 2;
}

Player::~Player()
{
}

void Player::setMatrix(glm::mat4 newMatrix)
{
	modelMatrix = newMatrix;
}

void Player::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Player::setGround(float newGround)
{
	ground = newGround;
}

void Player::setJump(bool isJumping)
{
	jumping = isJumping;
}

void Player::setFall(bool isFalling)
{
	falling = isFalling;
}

void Player::setFallTime(float newTime)
{
	fallTime = newTime;
}

void Player::setOldGround(float ground)
{
	oldGround = ground;
}

void Player::setDeath(bool death)
{
	this->death = death;
}

void Player::setFuel(float newFuel)
{
	fuel = std::max(0.f, std::min(newFuel, PLAYER_MAX_FUEL));
}

void Player::setAcceleration(float newAcceleration)
{
	acceleration = std::max(-(float)GAME_SPEED / 2 + minAccel, std::min(newAcceleration, MAX_ACCEL));
}

void Player::setOldAccel(float oldAccel)
{
	this->oldAccel = oldAccel;
}

void Player::setMinAccel(float newAccel)
{
	minAccel = newAccel;
}

void Player::setDeathTime(float newTime)
{
	deathTime = newTime;
}

void Player::setDeathType(int newType)
{
	deathType = newType;
}

void Player::setDifficultyTime(float newTime)
{
	difficultyTimer = newTime;
}

void Player::setScore(int newScore)
{
	score += newScore;
}

void Player::setShields(int newShields)
{
	shields = newShields;
}

void Player::doJump(float deltaTime, float jumpHeight)
{
	float max_height = jumpHeight * 10;
	float gravity = 4.9f;
	float initialSpeed = sqrtf(2 * gravity * max_height);
	static float time = 0;

	time += deltaTime;

	float currentHeight = oldGround + initialSpeed * time - powf(gravity * time, 2);

	position.y = std::max(currentHeight, ground);

	if (position.y == ground) {
		time = 0;
		jumping = false;
	}
}

void Player::doFall(float deltaTime)
{
	if (position.y == PLAYER_DEATH) {
		death = true;
		return;
	}

	fallTime += deltaTime;

	float gravity = 4.9f;

	float currentHeight = oldGround - powf(gravity * fallTime, 2);

	position.y = std::max(currentHeight, ground);
}

void Player::translate(float newX, float newY, float newZ)
{
	position.x += newX;
	position.y += newY;
	position.z += newZ;
}

void Player::useFuel(float deltaTime)
{
	fuel = std::max(0.f, fuel - deltaTime * FUEL_CONS_RATE * std::max(1.f, acceleration));
}

glm::mat4 Player::getMatrix()
{
	return modelMatrix * Transform3D::Translate(position.x, position.y, position.z);
}

glm::vec3 Player::getCenter()
{
	return center;
}

glm::vec3 Player::getPosition()
{
	return position;
}

float Player::getDiameter()
{
	return diameter;
}

float Player::getGround()
{
	return ground;
}

float Player::getOldGround()
{
	return oldGround;
}

float Player::getFuel()
{
	return fuel;
}

float Player::getAcceleration()
{
	return acceleration;
}

float Player::getMinAccel()
{
	return minAccel;
}

float Player::getDeathTime()
{
	return deathTime;
}

int Player::getDeathType()
{
	return deathType;
}

int Player::getScore()
{
	return score;
}

int Player::getShields()
{
	return shields;
}

float Player::getDifficultyTime()
{
	return difficultyTimer;
}

bool Player::isJumping()
{
	return jumping;
}

bool Player::isFalling()
{
	return falling;
}

bool Player::isDead()
{
	return death;
}