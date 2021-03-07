#define PLAYER_SIZE 1
#define PLAYER_JUMP_HEIGHT 2.8f
#define PLAYER_DEATH -10
#define PLAYER_LATERAL_SPEED 8.5f
#define PLAYER_MAX_FUEL 500.f
#define FUEL_CONS_RATE 0.85f
#define MAX_ACCEL 35.f
#define ACCEL_FACTOR 10
#define ORANGE_BLOCK 3
#define INVINCIBILITY 5
#define NOISE_TIME 0.2f
#define DEATH_TIME 3.f

#define GAME_SPEED 6.f
#define GAME_DIFF_INC 1.f
#define GAME_DIFF_TIME 5.f
#define FUEL_SIZE 0.5f

#define PLATFORM_SIZE 1
#define PLATFORM_SCALE_X 2
#define PLATFORM_SCALE_Y 0.3f
#define PLATFORM_DISTANCE 1.6f
#define JUMP_GAP 2
#define PLATFORM_GAP 2.5f
#define PLATFORM_DEATH 200
#define RANGE_DEATH 5.f
#define START_PLATFORM_SIZE 20
#define PLATFORM_FLUCTUATE_Y 0.35f

#define ORIGIN glm::vec3(0)
#define TOP_RIGHT glm::vec3(1, 1, 0)
#define SECTORS 100
#define STACKS 100
#define RED glm::vec3(1, 0, 0)
#define YELLOW glm::vec3(1, 1, 0)
#define ORANGE glm::vec3(1, 0.5f, 0)
#define GREEN glm::vec3(0, 1, 0)
#define GRAY glm::vec3(0.5f, 0.5f, 0.5f)
#define PURPLE glm::vec3(1, 0, 1)
#define PINK glm::vec3(1, 0.68f, 0.68f)
#define WHITE glm::vec3(1, 1, 1)
#define BLACK glm::vec3(0, 0, 0)
#define BLUE glm::vec3(0, 0, 1)
#define BROWN glm::vec3(0.64f, 0.16f, 0.16f)
#define BOTH glm::vec3(0.5f, 0.3f, 0.5f)
#define LIME glm::vec3(0.75f, 1, 0)
#define CYAN glm::vec3(0, 1, 1)

#define COLLECTABLE_SIZE 1
#define DECOR_SIZE 1

#define OBSTACLE_SIZE 1
#define OBSTACLE_COLOR WHITE

#define PATTERN_COUNT 10
#define MIDDLE 0
#define LEFT -1
#define RIGHT 1
#define NONE 100