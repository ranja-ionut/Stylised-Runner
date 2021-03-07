#pragma once

#include <Core/Engine.h>
#include "Player.h"

class Planet {
	public:
		Planet();
		Planet(glm::vec3 center, float init_size);
		~Planet();

		void setMatrix(glm::mat4 newMatrix);
		void setPosition(glm::vec3 newPosition);
		void setLength(float newLength);
		void setWidth(float newWidth);
		void setHeight(float newHeight);
		void setSpeed(float newSpeed);
		void setTexture(std::string newTexture);

		void translate(float newX, float newY, float newZ);
		void scale(float scaleX, float scaleY, float scaleZ);

		glm::mat4 getMatrix();
		glm::vec3 getCenter();
		float getLength();
		float getWidth();
		float getHeight();
		float getInitSize();
		int getSpeed();
		glm::vec3 getPosition();
		std::string getTexture();

		static glm::vec3 starColor;

	private:
		float init_size;
		int speed;
		glm::mat4 modelMatrix;
		glm::vec3 center;
		float width, length, height;
		glm::vec3 position;
		std::string texture;
};