#pragma once

#include <Core/Engine.h>
#include "Player.h"

class Collectable {
	public:
		Collectable();
		Collectable(glm::vec3 center, float init_size);
		~Collectable();

		void setMatrix(glm::mat4 newMatrix);
		void setPosition(glm::vec3 newPosition);
		void setLength(float newLength);
		void setWidth(float newWidth);
		void setHeight(float newHeight);
		void setRendered(bool render);

		void checkHit(Player* player);
		void translate(float newX, float newY, float newZ);
		void scale(float scaleX, float scaleY, float scaleZ);

		glm::mat4 getMatrix(float deltaTimeSeconds);
		glm::vec3 getCenter();
		float getLength();
		float getWidth();
		float getHeight();
		float getInitSize();
		bool isRendered();
		glm::vec3 getPosition();

	private:
		bool rendered;
		float init_size;
		glm::mat4 modelMatrix;
		glm::vec3 center;
		float width, length, height;
		glm::vec3 position;
};