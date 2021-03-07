#pragma once

#include <Core/Engine.h>
#include "Transform3D.h"
#include "Constants.h"

class Player {
	public:
		Player();
		Player(glm::vec3 center, float diameter);
		~Player();

		void setMatrix(glm::mat4 newMatrix);
		void setPosition(glm::vec3 newPosition);
		void setGround(float newGround);
		void setJump(bool isJumping);
		void setFall(bool isFalling);
		void setFallTime(float newTime);
		void setOldGround(float ground);
		void setDeath(bool death);
		void setFuel(float newFuel);
		void setAcceleration(float newAcceleration);
		void setOldAccel(float oldAccel);
		void setMinAccel(float newAccel);
		void setDeathTime(float newTime);
		void setDeathType(int newType);
		void setDifficultyTime(float newTime);
		void setScore(int newScore);
		void setShields(int newShields);

		void doJump(float deltaTime, float jumpHeight);
		void doFall(float deltaTime);
		void translate(float newX, float newY, float newZ);
		void useFuel(float deltaTime);

		glm::mat4 getMatrix();
		glm::vec3 getCenter();
		glm::vec3 getPosition();
		float getDiameter();
		float getGround();
		float getOldGround();
		float getFuel();
		float getAcceleration();
		float getMinAccel();
		float getDeathTime();
		float getDifficultyTime();
		int getDeathType();
		int getScore();
		int getShields();
		bool isJumping();
		bool isFalling();
		bool isDead();


	private:
		glm::mat4 modelMatrix;
		glm::vec3 center;
		float diameter;
		glm::vec3 position;
		float ground, oldGround;
		bool jumping;
		bool falling;
		bool death;
		float fuel;
		float fallTime;
		float acceleration, oldAccel, minAccel;
		float difficultyTimer;
		float deathTime;
		int deathType;
		int score;
		int shields;
};