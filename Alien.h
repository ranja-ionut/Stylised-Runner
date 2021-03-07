#pragma once

#include <Core/Engine.h>
#include "Player.h"

class Alien {
	public:
		Alien();
		Alien(glm::vec3 center, float init_size);
		~Alien();

		void setMatrix(glm::mat4 newMatrix);
		void setPosition(glm::vec3 newPosition);
		void setLength(float newLength);
		void setWidth(float newWidth);
		void setHeight(float newHeight);
		void setRendered(bool render);
		void setColor(glm::vec3 newColor);
		void setDirection(glm::vec3 newDirection);

		void updateDirection(float deltaTimeSeconds);
		void translate(float newX, float newY, float newZ);
		void scale(float scaleX, float scaleY, float scaleZ);

		glm::mat4 getMatrix();
		glm::vec3 getCenter();
		float getLength();
		float getWidth();
		float getHeight();
		float getInitSize();
		bool isRendered();
		glm::vec3 getPosition();
		glm::vec3 getColor();
		glm::vec3 getDirection();

		static glm::vec3 alienColor;

	private:
		bool rendered;
		float init_size;
		glm::mat4 modelMatrix;
		glm::vec3 center;
		float width, length, height;
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 direction;
};