#include "Pattern.h"

Pattern::Pattern()
{
	count = 3;
	pattern_id = 0;
	platforms = new Platform*[3];
	obstacles = new Obstacle*[1];
	collectables = new Collectable*[9 / 2];
	alien = new Alien(ORIGIN, DECOR_SIZE);
	star = new Star(ORIGIN, DECOR_SIZE);
	planet = new Planet(ORIGIN, DECOR_SIZE);
}

Pattern::Pattern(int count, int pattern_id)
{
	this->count = count;
	this->pattern_id = pattern_id;
	platforms = new Platform*[count];
	obstacles = new Obstacle*[count / 3];
	collectables = new Collectable*[3 * count / 2];
	alien = new Alien(ORIGIN, DECOR_SIZE);
	star = new Star(ORIGIN, DECOR_SIZE);
	planet = new Planet(ORIGIN, DECOR_SIZE);
}

Pattern::~Pattern()
{
}

int Pattern::getCount()
{
	return count;
}

int Pattern::getId()
{
	return pattern_id;
}

Platform** Pattern::getPlatforms()
{
	return platforms;
}

Obstacle** Pattern::getObstacles()
{
	return obstacles;
}

Collectable** Pattern::getCollectables()
{
	return collectables;
}

Alien* Pattern::getAlien()
{
	return alien;
}

Star* Pattern::getStar()
{
	return star;
}

Planet* Pattern::getPlanet()
{
	return planet;
}

float Pattern::getLeft()
{
	float left = platforms[0]->getPosition().x;

	for (int i = 0; i < count; i++) {
		if (platforms[i]->getPosition().x - platforms[i]->getWidth() / 2 < left) {
			left = platforms[i]->getPosition().x - platforms[i]->getWidth() / 2;
		}
	}

	return left;
}

float Pattern::getRight()
{
	float right = platforms[0]->getPosition().x;

	for (int i = 0; i < count; i++) {
		if (platforms[i]->getPosition().x + platforms[i]->getWidth() / 2 > right) {
			right = platforms[i]->getPosition().x + platforms[i]->getWidth() / 2;
		}
	}

	return right;
}

float Pattern::getUp()
{
	float up = platforms[0]->getPosition().z;

	for (int i = 0; i < count; i++) {
		if (platforms[i]->getPosition().z - platforms[i]->getLength() / 2 < up) {
			up = platforms[i]->getPosition().z - platforms[i]->getLength() / 2;
		}
	}

	return up;
}

float Pattern::getDown()
{
	float down = platforms[0]->getPosition().z;

	for (int i = 0; i < count; i++) {
		if (platforms[i]->getPosition().z + platforms[i]->getLength() / 2 > down) {
			down = platforms[i]->getPosition().z + platforms[i]->getLength() / 2;
		}
	}

	return down;
}

void Pattern::checkLanding(Player* player)
{
	for (int i = 0; i < count; i++) {
		platforms[i]->checkLanding(player);
	}

	for (int i = 0; i < count / 3; i++) {
		obstacles[i]->checkHit(player);
	}

	for (int i = 0; i < 3 * count / 2; i++) {
		collectables[i]->checkHit(player);
	}
}

void Pattern::translate(float newX, float newY, float newZ)
{
	for (int i = 0; i < count; i++) {
		platforms[i]->translate(newX, newY, newZ);
	}

	for (int i = 0; i < count / 3; i++) {
		obstacles[i]->translate(newX, newY, newZ);
	}

	for (int i = 0; i < 3 * count / 2; i++) {
		collectables[i]->translate(newX, newY, newZ);
	}

	alien->translate(newX, newY, newZ);
	star->translate(newX, newY, newZ);
	planet->translate(newX, newY, newZ);
}

void Pattern::createPlatforms()
{
	for (int i = 0; i < count; i++) {
		platforms[i] = new Platform(ORIGIN, PLATFORM_SIZE);
	}
	
	for (int i = 0; i < count / 3; i++) {
		obstacles[i] = new Obstacle(ORIGIN, OBSTACLE_SIZE);
	}

	for (int i = 0; i < 3 * count / 2; i++) {
		collectables[i] = new Collectable(ORIGIN, COLLECTABLE_SIZE);
	}
}

void Pattern::generatePlatforms(float offsetX, float offsetZ, float distance, int direction)
{
	translate(offsetX, 0, offsetZ);

	float scale = rand() % 8 + 1;

	planet->scale(scale, scale, scale);
	planet->setSpeed(scale);

	if (direction == MIDDLE) {
		int odd = 1;
		int even = 0;
		int j = 0;
		int k = 0;
		for (int i = 1; i < count; i++) {
			int chance = rand() % 100;

			if (i % 2 == 0) {
				platforms[i]->translate(-distance * (i - odd), 0, 0);
				if (chance >= 0 && chance < 25 && j < count / 3) {
					obstacles[j]->setRendered(true);
					obstacles[j++]->translate(-distance * (i - odd),
						OBSTACLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
						-platforms[i]->getLength() / 2);
				}

				if (chance >= 25 && chance < 50 && (k < 3 * count / 2 && (k+1) < 3 * count / 2 && (k + 2) < 3 * count / 2)) {
					collectables[k]->setRendered(true);
					collectables[k]->translate(-distance * (i - odd),
						COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
						-platforms[i]->getLength() / 2);

					collectables[k + 1]->setRendered(true);
					collectables[k + 1]->translate(-distance * (i - odd),
						COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
						-platforms[i]->getLength() / 2 - 10 * collectables[k + 1]->getLength());

					collectables[k + 2]->setRendered(true);
					collectables[k + 2]->translate(-distance * (i - odd),
						COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
						-platforms[i]->getLength() / 2 + 10 * collectables[k + 1]->getLength());
				
					k += 3;
				}
				odd++;
			}
			else {
				platforms[i]->translate(distance * (i - even), 0, 0);
				if (chance >= 50 && chance < 75 && j < count / 3) {
					obstacles[j]->setRendered(true);
					obstacles[j++]->translate(distance * (i - even),
						OBSTACLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y, 
						-platforms[i]->getLength() / 2);
				}

				if (chance >= 75 && chance < 100 && (k < 3 * count / 2 && (k + 1) < 3 * count / 2 && (k + 2) < 3 * count / 2)) {
					collectables[k]->setRendered(true);
					collectables[k]->translate(distance * (i - even),
						COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
						-platforms[i]->getLength() / 2);

					collectables[k + 1]->setRendered(true);
					collectables[k + 1]->translate(distance * (i - even),
						COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
						-platforms[i]->getLength() / 2 - 10 * collectables[k + 1]->getLength());

					collectables[k + 2]->setRendered(true);
					collectables[k + 2]->translate(distance * (i - even),
						COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
						-platforms[i]->getLength() / 2 + 10 * collectables[k + 1]->getLength());

					k += 3;
				}
				even++;
			}

			chance = rand() % 4 + 1;

			if (chance == 1) {
				platforms[i]->setTexture("platform1");
			}

			if (chance == 2) {
				platforms[i]->setTexture("platform2");
			}

			if (chance == 3) {
				platforms[i]->setTexture("platform3");
			}

			if (chance == 4) {
				platforms[i]->setTexture("platform4");
			}
		}

		float left = getLeft();
		float right = getRight();
		float middle = getUp() - getDown();
		int chance = rand() % 100;

		if (chance < 50) {
			alien->setRendered(true);
			
			chance = rand() % 100;

			if (chance >= 50) {
				alien->setPosition(glm::vec3(0, 0, offsetZ));
				alien->translate(left - 15, 6, middle / 2);
				alien->setDirection(glm::vec3(1, -1, 0));

				planet->setPosition(glm::vec3(0, 0, offsetZ));
				planet->translate(right + 25, rand() % 4, -rand() % (int)middle);
			}
			else {
				alien->setPosition(glm::vec3(0, 0, offsetZ));
				alien->translate(right + 15, 6, middle / 2);
				alien->setDirection(glm::vec3(-1, -1, 0));

				planet->setPosition(glm::vec3(0, 0, offsetZ));
				planet->translate(left - 25, rand() % 4, -rand() % (int)middle);
			}
		}
		else {
			star->setRendered(true);
			
			chance = rand() % 100;

			if (chance < 50) {
				star->setPosition(glm::vec3(0, 0, offsetZ));
				star->translate(left - 15, 6, middle / 2);

				planet->setPosition(glm::vec3(0, 0, offsetZ));
				planet->translate(right + 25, rand() % 4, -rand() % (int)middle);
			}
			else {
				star->setPosition(glm::vec3(0, 0, offsetZ));
				star->translate(right + 15, 6, middle / 2);

				planet->setPosition(glm::vec3(0, 0, offsetZ));
				planet->translate(left - 25, rand() % 4, -rand() % (int)middle);
			}
		}

	}

	if (direction == LEFT) {
		int j = 0;
		int k = 0;
		for (int i = 1; i < count; i++) {
			int chance = rand() % 100;
			platforms[i]->translate(-distance * i, 0, 0);
			if (chance < 30 && j < count / 3) {
				obstacles[j]->setRendered(true);
				obstacles[j++]->translate(-distance * i,
					OBSTACLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2);
			}

			if (chance >= 30 && (k < 3 * count / 2 && (k + 1) < 3 * count / 2 && (k + 2) < 3 * count / 2)) {
				collectables[k]->setRendered(true);
				collectables[k]->translate(-distance * i,
					COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2);

				collectables[k + 1]->setRendered(true);
				collectables[k + 1]->translate(-distance * i,
					COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2 - 10 * collectables[k + 1]->getLength());

				collectables[k + 2]->setRendered(true);
				collectables[k + 2]->translate(-distance * i,
					COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2 + 10 * collectables[k + 1]->getLength());

				k += 3;
			}

			chance = rand() % 4 + 1;
			
			if (chance == 1) {
				platforms[i]->setTexture("platform1");
			}

			if (chance == 2) {
				platforms[i]->setTexture("platform2");
			}

			if (chance == 3) {
				platforms[i]->setTexture("platform3");
			}

			if (chance == 4) {
				platforms[i]->setTexture("platform4");
			}
		}

		float right = getRight();
		float left = getLeft();
		float middle = getUp() - getDown();
		int chance = rand() % 100;

		if (chance < 50) {
			alien->setRendered(true);
			alien->setPosition(glm::vec3(0, 0, offsetZ));
			alien->translate(right + 15, 6, middle / 2);
			alien->setDirection(glm::vec3(-1, -1, 0));

			planet->setPosition(glm::vec3(0, 0, offsetZ));
			planet->translate(left - 25, rand() % 4, -rand() % (int)middle);
		}
		else {
			star->setRendered(true);
			star->setPosition(glm::vec3(0, 0, offsetZ));
			star->translate(right + 15, 6, middle / 2);

			planet->setPosition(glm::vec3(0, 0, offsetZ));
			planet->translate(left - 25, rand() % 4, -rand() % (int)middle);
		}
	}

	if (direction == RIGHT) {
		int j = 0;
		int k = 0;
		for (int i = 1; i < count; i++) {
			int chance = rand() % 100;
			platforms[i]->translate(distance * i, 0, 0);
			if (chance > 60 && j < count / 3) {
				obstacles[j]->setRendered(true);
				obstacles[j++]->translate(distance * i,
					OBSTACLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2);
			}

			if (chance <= 60 && (k < 3 * count / 2 && (k + 1) < 3 * count / 2 && (k + 2) < 3 * count / 2)) {
				collectables[k]->setRendered(true);
				collectables[k]->translate(distance* i,
					COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2);

				collectables[k + 1]->setRendered(true);
				collectables[k + 1]->translate(distance* i,
					COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2 - 10 * collectables[k + 1]->getLength());

				collectables[k + 2]->setRendered(true);
				collectables[k + 2]->translate(distance* i,
					COLLECTABLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2 + 10 * collectables[k + 1]->getLength());

				k += 3;
			}

			chance = rand() % 4 + 1;

			if (chance == 1) {
				platforms[i]->setTexture("platform1");
			}

			if (chance == 2) {
				platforms[i]->setTexture("platform2");
			}

			if (chance == 3) {
				platforms[i]->setTexture("platform3");
			}

			if (chance == 4) {
				platforms[i]->setTexture("platform4");
			}
		}

		float left = getLeft();
		float right = getRight();
		float middle = getUp() - getDown();
		int chance = rand() % 100;

		if (chance < 50) {
			alien->setRendered(true);
			alien->setPosition(glm::vec3(0, 0, offsetZ));
			alien->translate(left - 15, 6, middle / 2);
			alien->setDirection(glm::vec3(1, -1, 0));

			planet->setPosition(glm::vec3(0, 0, offsetZ));
			planet->translate(right + 25, rand() % 4, -rand() % (int)middle);
		}
		else {
			star->setRendered(true);
			star->setPosition(glm::vec3(0, 0, offsetZ));
			star->translate(left - 15, 6, middle / 2);

			planet->setPosition(glm::vec3(0, 0, offsetZ));
			planet->translate(right + 25, rand() % 4, -rand() % (int)middle);
		}
	}

	if (star->isRendered()) {
		if (Star::starColor == YELLOW) {
			star->setColor(BLUE);
			Star::starColor = BLUE;
		}
		else {
			star->setColor(YELLOW);
			Star::starColor = YELLOW;
		}
	}

	if (alien->isRendered()) {
		if (Alien::alienColor == RED) {
			alien->setColor(CYAN);
			Alien::alienColor = CYAN;
		}
		else {
			alien->setColor(RED);
			Alien::alienColor = RED;
		}
	}

	int chance = rand() % 5 + 1;

	if (chance == 1) {
		planet->setTexture("planet1");
	}

	if (chance == 2) {
		planet->setTexture("planet2");
	}

	if (chance == 3) {
		planet->setTexture("planet3");
	}

	if (chance == 4) {
		planet->setTexture("planet4");
	}

	if (chance == 5) {
		planet->setTexture("planet5");
	}
}

void Pattern::resetPlatforms()
{
	for (int i = 0; i < count; i++) {
		float width = platforms[i]->getWidth();
		float height = platforms[i]->getHeight();
		float length = platforms[i]->getLength();
		float init = platforms[i]->getInitSize();
		
		platforms[i]->scale(init/width, init/height, init/length);

		platforms[i]->setPosition(glm::vec3(0));

		platforms[i]->setColor(WHITE);
	}

	for (int i = 0; i < count / 3; i++) {
		float width = obstacles[i]->getWidth();
		float height = obstacles[i]->getHeight();
		float length = obstacles[i]->getLength();
		float init = obstacles[i]->getInitSize();

		obstacles[i]->scale(init / width, init / height, init / length);

		obstacles[i]->setPosition(glm::vec3(0));

		obstacles[i]->setColor(WHITE);

		obstacles[i]->setRendered(false);
	}

	for (int i = 0; i < 3 * count / 2; i++) {
		float width = collectables[i]->getWidth();
		float height = collectables[i]->getHeight();
		float length = collectables[i]->getLength();
		float init = collectables[i]->getInitSize();

		collectables[i]->scale(init / width, init / height, init / length);

		collectables[i]->setPosition(glm::vec3(0));

		collectables[i]->setRendered(false);
	}

	float width = alien->getWidth();
	float height = alien->getHeight();
	float length = alien->getLength();
	float init = alien->getInitSize();

	alien->scale(init / width, init / height, init / length);

	alien->setPosition(glm::vec3(0));

	alien->setRendered(false);

	width = star->getWidth();
	height = star->getHeight();
	length = star->getLength();
	init = star->getInitSize();

	star->scale(init / width, init / height, init / length);

	star->setPosition(glm::vec3(0));

	star->setRendered(false);

	width = planet->getWidth();
	height = planet->getHeight();
	length = planet->getLength();
	init = planet->getInitSize();

	planet->scale(init / width, init / height, init / length);

	planet->setPosition(glm::vec3(0));

	planet->setSpeed(1);
}