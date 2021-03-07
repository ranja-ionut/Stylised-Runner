#include "Generator.h"

Generator::Generator()
{
	for (int i = 0; i < PATTERN_COUNT; i++) {
		patterns[i] = new Pattern(rand() % 5 + 3, i);
		patterns[i]->createPlatforms();
		gone[i] = false;
	}

	max_distance = 0;

	furthest_pattern = -1;

	last_direction = NONE;
}

Generator::~Generator()
{
}

Pattern** Generator::getPatterns()
{
	return patterns;
}

bool Generator::isGone(int pattern_id)
{
	return gone[pattern_id];
}

void Generator::checkLanding(Player* player)
{
	for (int i = 0; i < PATTERN_COUNT; i++) {
		patterns[i]->checkLanding(player);
	}
}

void Generator::translate(float newX, float newY, float newZ)
{
	for (int i = 0; i < PATTERN_COUNT; i++) {
		patterns[i]->translate(newX, newY, newZ);
	}
}

void Generator::generate(Pattern* pattern)
{
	Platform** platforms = pattern->getPlatforms();
	int count = pattern->getCount();
	float anchor_length = platforms[0]->getLength();

	for (int i = 0; i < count; i++) {
		int scaleZ = rand() % 11 + 40;

		platforms[i]->scale(PLATFORM_SCALE_X, PLATFORM_SCALE_Y, scaleZ);

		anchor_length = platforms[0]->getLength();

		int choice = rand() % 2;

		if (choice) {
			platforms[i]->translate(0, PLATFORM_FLUCTUATE_Y, -anchor_length / 2);
		}
		else {
			platforms[i]->translate(0, -PLATFORM_FLUCTUATE_Y, -anchor_length / 2);
		}
	}

	float left = pattern->getLeft();
	float right = pattern->getRight();
	float up = pattern->getUp();
	float down = pattern->getDown();

	float pattern_width = right - left;
	float pattern_length = down - up;

	gone[pattern->getId()] = false;

	Pattern* fpat = patterns[furthest_pattern];

	if (furthest_pattern >= 0) {
		max_distance = -fpat->getDown() + fpat->getDown() - fpat->getUp() + JUMP_GAP + PLATFORM_GAP;

		furthest_pattern = (furthest_pattern + 1) % PATTERN_COUNT;
	}
	else {
		max_distance = START_PLATFORM_SIZE * 1.25f;
		furthest_pattern++;
	}

	int direction = 0;

	if (last_direction == NONE) {
		direction = MIDDLE;
	} else {
		int choice = rand() % 100;

		if (choice < 33) {
			direction = LEFT;
		}

		if (choice >= 33 && choice < 66) {
			direction = RIGHT;
		}

		if (choice >= 66) {
			direction = MIDDLE;
		}
	}

	float offsetX = 0;
	int middle = 0;

	switch (last_direction) {
		case LEFT:
				middle = fpat->getCount() / 2;
				offsetX = fpat->getPlatforms()[middle]->getPosition().x;
			break;
		case MIDDLE:
				offsetX = fpat->getPlatforms()[0]->getPosition().x;
			break;
		case RIGHT:
				middle = fpat->getCount() / 2;
				offsetX = fpat->getPlatforms()[middle]->getPosition().x;
			break;
		default: offsetX = 0;
	}

	last_direction = direction;

	pattern->generatePlatforms(offsetX, -max_distance, PLATFORM_DISTANCE + platforms[0]->getWidth(), direction);
}

void Generator::setGone(int pattern_id)
{
	gone[pattern_id] = true;
}
