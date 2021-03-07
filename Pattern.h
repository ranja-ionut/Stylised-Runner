#pragma once

#include <Core/Engine.h>
#include "Platform.h"
#include "Obstacle.h"
#include "Object3D.h"
#include "Collectable.h"
#include "Alien.h"
#include "Star.h"
#include "Planet.h"

class Pattern {
	public:
		Pattern();
		Pattern(int count, int pattern_id);
		~Pattern();

		int getCount();
		int getId();
		Platform** getPlatforms();
		Obstacle** getObstacles();
		Collectable** getCollectables();
		Alien* getAlien();
		Star* getStar();
		Planet* getPlanet();
		float getLeft();
		float getRight();
		float getUp();
		float getDown();

		void checkLanding(Player* player);
		void translate(float newX, float newY, float newZ);
		void createPlatforms();
		void generatePlatforms(float offsetX, float offsetZ, float distance, int direction);
		void resetPlatforms();

	private:
		int count;
		int pattern_id;
		Platform** platforms;
		Obstacle** obstacles;
		Collectable** collectables;
		Planet* planet;
		Alien* alien;
		Star* star;
};