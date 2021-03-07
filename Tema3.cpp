#include "Tema3.h"
#include <iostream>
#include <Core/Engine.h>

Tema3::Tema3()
{
	camera = new Cam::Camera();

	projectionMatrix = glm::mat4(1);

	player = new Player(ORIGIN, PLAYER_SIZE);

	start_platform = new Platform(ORIGIN, PLATFORM_SIZE);

	generator = new Generator();

	camera_mode = false;

	skysphere = 0;

	flame = 0;

	pause = true;

	spin = 0;

	speed = 0;
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	const std::string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "platform1.jpg").c_str(), GL_REPEAT);
		mapTextures["platform1"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "platform2.jpg").c_str(), GL_REPEAT);
		mapTextures["platform2"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "platform3.jpg").c_str(), GL_REPEAT);
		mapTextures["platform3"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "platform4.jpg").c_str(), GL_REPEAT);
		mapTextures["platform4"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "obstacle.jpg").c_str(), GL_REPEAT);
		mapTextures["obstacle"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "skysphere.jpg").c_str(), GL_REPEAT);
		mapTextures["skysphere"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "flame.jpg").c_str(), GL_REPEAT);
		mapTextures["flame"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "body.jpg").c_str(), GL_REPEAT);
		mapTextures["body"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "thruster.jpg").c_str(), GL_REPEAT);
		mapTextures["thruster"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "front.jpg").c_str(), GL_REPEAT);
		mapTextures["front"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "collectable.jpg").c_str(), GL_REPEAT);
		mapTextures["collectable"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "star.jpg").c_str(), GL_REPEAT);
		mapTextures["star"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "back.png").c_str(), GL_REPEAT);
		mapTextures["back"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "score.png").c_str(), GL_REPEAT);
		mapTextures["score"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "shield.png").c_str(), GL_REPEAT);
		mapTextures["shield"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "body_alien.png").c_str(), GL_REPEAT);
		mapTextures["body_alien"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "cockpit.png").c_str(), GL_REPEAT);
		mapTextures["cockpit"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "ray.png").c_str(), GL_REPEAT);
		mapTextures["ray"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "light.jpg").c_str(), GL_REPEAT);
		mapTextures["light"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "planet1.jpg").c_str(), GL_REPEAT);
		mapTextures["planet1"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "planet2.png").c_str(), GL_REPEAT);
		mapTextures["planet2"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "planet3.png").c_str(), GL_REPEAT);
		mapTextures["planet3"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "planet4.png").c_str(), GL_REPEAT);
		mapTextures["planet4"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "planet5.jpg").c_str(), GL_REPEAT);
		mapTextures["planet5"] = texture;
	}

	{
		Mesh* skysphere = Object3D::CreateSphere("skysphere", ORIGIN, 1, BLUE);
		AddMeshToList(skysphere);
	}

	{
		Mesh* form = Object3D::CreateCube("cube", ORIGIN, 1, BLUE, true);
		AddMeshToList(form);

		form = Object3D::CreateSphere("sphere", ORIGIN, 1, BLUE);
		AddMeshToList(form);

		form = Object3D::CreatePyramid("pyramid", ORIGIN, 1, BLUE);
		AddMeshToList(form);

		form = Object3D::CreateShield("shield", ORIGIN, 1, BLUE);
		AddMeshToList(form);
	}

	{
		Mesh* player_mesh = Object3D::CreateSphere("player", player->getCenter(), player->getDiameter(), RED);
		AddMeshToList(player_mesh);
	}

	{
		Mesh* start_platform_mesh = Object3D::CreateCube("start_platform", start_platform->getCenter(), start_platform->getLength(), WHITE, true);
		AddMeshToList(start_platform_mesh);

		start_platform->scale(START_PLATFORM_SIZE, PLATFORM_SCALE_Y, START_PLATFORM_SIZE);
		start_platform->translate(0, 0, -start_platform->getLength() / 2);
	}

	{
		Mesh* platform_mesh = Object3D::CreateCube("platform", ORIGIN, PLATFORM_SIZE, GREEN, true);
		AddMeshToList(platform_mesh);
	}

	{
		Mesh* obstacle_mesh = Object3D::CreateSphere("obstacle", ORIGIN, OBSTACLE_SIZE, WHITE);
		AddMeshToList(obstacle_mesh);
	}

	{
		Mesh* score_mesh = Object3D::CreateSquare("score", ORIGIN, FUEL_SIZE, GREEN);
		AddMeshToList(score_mesh);
	}

	player->translate(0, start_platform->getHeight() / 2 + player->getDiameter() / 2, 0);

	Pattern** patterns = generator->getPatterns();
	for (int i = 0; i < PATTERN_COUNT; i++) {
		generator->generate(patterns[i]);
	}

	{
		Shader* shader = new Shader("Shader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Light & material properties
	{
		materialShininess = 30;
		materialKd = 0.5f;
		materialKs = 0.5f;
	}
}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	Platform::willLand = false;
	glm::vec2 pixel = glm::vec2(1 / ((double)resolution.x / 2), 1 / ((double)resolution.y / 2));


	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(1 - 50 * pixel.x, 1 - 125 * pixel.y, 0);
	modelMatrix *= Transform3D::Scale(1, player->getScore() / 9999.f, 1);
	modelMatrix *= Transform3D::Scale(100, 250, 1);
	modelMatrix *= Transform3D::Scale(pixel.x, pixel.y, 1);

	RenderSimpleMesh(meshes["score"], shaders["Shader"], modelMatrix, mapTextures["score"], 3);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(1 - 50 * pixel.x, 1 - 125 * pixel.y, 0);
	modelMatrix *= Transform3D::Scale(100, 250, 1);
	modelMatrix *= Transform3D::Scale(pixel.x, pixel.y, 1);

	RenderSimpleMesh(meshes["score"], shaders["Shader"], modelMatrix, mapTextures["back"], 3);

	if (player->getShields() > 0) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(1 - 160 * pixel.x, 1 - 75 * pixel.y, 0);
		modelMatrix *= Transform3D::Scale(100, 100, 1);
		modelMatrix *= Transform3D::Scale(pixel.x, pixel.y, 1);

		RenderSimpleMesh(meshes["shield"], shaders["Shader"], modelMatrix, mapTextures["shield"], 3);

		if (player->getShields() > 1) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(1 - 270 * pixel.x, 1 - 75 * pixel.y, 0);
			modelMatrix *= Transform3D::Scale(100, 100, 1);
			modelMatrix *= Transform3D::Scale(pixel.x, pixel.y, 1);

			RenderSimpleMesh(meshes["shield"], shaders["Shader"], modelMatrix, mapTextures["shield"], 3);
		}
	}
}

void Tema3::Update(float deltaTimeSeconds)
{
	player->setDifficultyTime(player->getDifficultyTime() + deltaTimeSeconds);

	if (player->getDifficultyTime() > GAME_DIFF_TIME) {
		player->setMinAccel(player->getMinAccel() + GAME_DIFF_INC);
		player->setDifficultyTime(0);
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 300.0f);
	
	if (!pause) {
		if (camera_mode) {
			camera->Set(player->getPosition() - glm::vec3(0, 0, player->getDiameter() / 2),
				player->getPosition() - glm::vec3(0, 0, player->getDiameter() / 2 + 1),
				glm::vec3(0, 1, 0));
		}
		else {
			camera->Set(player->getPosition() + glm::vec3(0, 4.5f * player->getDiameter() / 2, 2.85f * player->getDiameter()),
				player->getPosition() - glm::vec3(0, 0, 1.5f),
				glm::vec3(0, 1, 0));
		}

		if (!player->isDead()) {
			generator->translate(0, 0, (GAME_SPEED + player->getAcceleration()) * deltaTimeSeconds);
			start_platform->translate(0, 0, (GAME_SPEED + player->getAcceleration()) * deltaTimeSeconds);
		}
	}

	skysphere = 1;
	RenderSimpleMesh(meshes["skysphere"], shaders["Shader"], glm::mat4() * Transform3D::Translate(player->getPosition().x, player->getPosition().y, 0) * Transform3D::Scale(400, 325, 400)
														  * Transform3D::RotateOX(RADIANS(-90)), mapTextures["skysphere"], 10);
	skysphere = 0;


	Pattern** patterns = generator->getPatterns();
	for (int i = 0; i < PATTERN_COUNT; i++) {
		if (patterns[i]->getUp() > PLATFORM_DEATH) {
			generator->setGone(i);
		}

		if (generator->isGone(i)) {
			patterns[i]->resetPlatforms();
			generator->generate(patterns[i]);
		}

		Alien* alien = patterns[i]->getAlien();
		Star* star = patterns[i]->getStar();

		if (alien->isRendered()) {
			alien->updateDirection(deltaTimeSeconds);
			lightPosition[i] = alien->getPosition() + glm::vec3(0, -0.5f * 4, 0);
			lightColor[i] = alien->getColor();
			lightDirection[i] = alien->getDirection();
			spots[i] = 1;
			angle[i] = 0;
		}

		if (star->isRendered()) {
			lightPosition[i] = star->getPosition();
			lightColor[i] = star->getColor();
			lightDirection[i] = glm::vec3(0);
			spots[i] = 0;
			angle[i] = 0;
		}
	}

	for (int i = 0; i < PATTERN_COUNT; i++) {
		int count = patterns[i]->getCount();

		Platform** platforms = patterns[i]->getPlatforms();
		Obstacle** obstacles = patterns[i]->getObstacles();
		Collectable** collectables = patterns[i]->getCollectables();
		Alien* alien = patterns[i]->getAlien();
		Star* star = patterns[i]->getStar();
		Planet* planet = patterns[i]->getPlanet();

		if (patterns[i]->getUp() < RANGE_DEATH) {

			spin = 1;
			speed = planet->getSpeed();
			RenderSimpleMesh(meshes["sphere"], shaders["Shader"], planet->getMatrix(), mapTextures[planet->getTexture()], 0);
			spin = 0;
			speed = 0;

			if (alien->isRendered()) {
				alienModelMatrix = Matrix::alienModelMatrix();

				spin = 1;
				speed = 2;
				RenderSimpleMesh(meshes["sphere"], shaders["Shader"], alien->getMatrix() * alienModelMatrix["body"], mapTextures["body_alien"], 0);
				speed = 0;
				spin = 0;
				RenderSimpleMesh(meshes["sphere"], shaders["Shader"], alien->getMatrix() * alienModelMatrix["cockpit"], mapTextures["cockpit"], 0);
				RenderSimpleMesh(meshes["pyramid"], shaders["Shader"], alien->getMatrix() * alienModelMatrix["ray"], mapTextures["ray"], 0);
				spin = 1;
				speed = 2;
				RenderSimpleMesh(meshes["sphere"], shaders["Shader"], alien->getMatrix() * alienModelMatrix["light"], mapTextures["light"], 0);
				spin = 0;
				speed = 0;
			}

			if (star->isRendered()) {
				RenderSimpleMesh(meshes["sphere"], shaders["Shader"], star->getMatrix(), mapTextures["star"], 0);
			}

			for (int j = 0; j < count; j++) {
				RenderSimpleMesh(meshes["platform"], shaders["Shader"], platforms[j]->getMatrix(), mapTextures[platforms[j]->getTexture()], 0);
			}

			for (int j = 0; j < count / 3; j++) {
				if (obstacles[j]->isRendered()) {
					RenderSimpleMesh(meshes["obstacle"], shaders["Shader"], obstacles[j]->getMatrix(), mapTextures["obstacle"], 0);
				}
			}

			for (int j = 0; j < 3 * count / 2; j++) {
				if (collectables[j]->isRendered()) {
					RenderSimpleMesh(meshes["cube"], shaders["Shader"], collectables[j]->getMatrix(deltaTimeSeconds), mapTextures["collectable"], 0);
				}
			}
		}
	}

	generator->checkLanding(player);

	RenderSimpleMesh(meshes["start_platform"], shaders["Shader"], start_platform->getMatrix(), mapTextures["platform1"], 0);
	start_platform->checkLanding(player);

	if (!player->isDead() && !camera_mode) {
		playerModelMatrix = Matrix::playerModelMatrix();

		RenderSimpleMesh(meshes["pyramid"], shaders["Shader"], player->getMatrix() * playerModelMatrix["front"], mapTextures["front"], 0);
		RenderSimpleMesh(meshes["cube"], shaders["Shader"], player->getMatrix() * playerModelMatrix["body"], mapTextures["body"], 0);
		RenderSimpleMesh(meshes["pyramid"], shaders["Shader"], player->getMatrix() * playerModelMatrix["thruster1"], mapTextures["thruster"], 0);
		RenderSimpleMesh(meshes["pyramid"], shaders["Shader"], player->getMatrix() * playerModelMatrix["thruster2"], mapTextures["thruster"], 0);
		flame = 1;
		RenderSimpleMesh(meshes["sphere"], shaders["Shader"], player->getMatrix() * playerModelMatrix["flame1"], mapTextures["flame"], 0);
		RenderSimpleMesh(meshes["sphere"], shaders["Shader"], player->getMatrix() * playerModelMatrix["flame2"], mapTextures["flame"], 0);
		flame = 0;
	}

	if (player->isDead()) {
		camera_mode = false;

		playerModelMatrix = Matrix::playerModelMatrix();
		flame = 1;
		RenderSimpleMesh(meshes["sphere"], shaders["Shader"], player->getMatrix(), mapTextures["flame"], player->getDeathType());
		flame = 0;

		player->setDeathTime(player->getDeathTime() + deltaTimeSeconds);

		if (player->getDeathTime() >= DEATH_TIME) {
			printf("GAME OVER\n");
			exit(1);
		}
	}

	if (!Platform::willLand) {
		player->setGround(PLAYER_DEATH);
		if (!player->isJumping()) {
			player->setFall(true);
		}
		else {
			player->setFall(false);
		}
	}

	if (!player->isDead()) {
		if (player->isJumping() && !player->isFalling()) {
			player->doJump(deltaTimeSeconds, PLAYER_JUMP_HEIGHT);
		}

		if (player->isFalling()) {
			player->doFall(deltaTimeSeconds);
		}
	}
}

void Tema3::FrameEnd()
{
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture, const int type)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	int light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(light_position, PATTERN_COUNT, glm::value_ptr(lightPosition[0]));

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3fv(light_direction, PATTERN_COUNT, glm::value_ptr(lightDirection[0]));

	glm::vec3 eyePosition = camera->position;
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);

	glUniform1f(glGetUniformLocation(shader->program, "border"), 200);
	glUniform3fv(glGetUniformLocation(shader->program, "light_color"), PATTERN_COUNT, glm::value_ptr(lightColor[0]));
	glUniform1iv(glGetUniformLocation(shader->program, "spot"), PATTERN_COUNT, spots);
	glUniform1fv(glGetUniformLocation(shader->program, "angle"), PATTERN_COUNT, angle);
	glUniform1i(glGetUniformLocation(shader->program, "speed"), speed);

	float timeLoc = glGetUniformLocation(shader->program, "time");
	glUniform1f(timeLoc, Engine::GetElapsedTime());
	
	int deathLoc = glGetUniformLocation(shader->program, "death");
	glUniform1f(deathLoc, player->getDeathTime());

	int location = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	location = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	location = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->program, "type");
	glUniform1i(location, type);

	location = glGetUniformLocation(shader->program, "isSkySphere");
	glUniform1i(location, skysphere);

	location = glGetUniformLocation(shader->program, "isFlame");
	glUniform1i(location, flame);

	location = glGetUniformLocation(shader->program, "spin");
	glUniform1i(location, spin);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
	glUniform1i(glGetUniformLocation(shader->program, "texture_in"), 0);


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	float playerSpeed = PLAYER_LATERAL_SPEED * deltaTime;
	static float speed = 2;

	if (window->KeyHold(GLFW_KEY_1)) {
		speed += 0.1f;
	}

	if (window->KeyHold(GLFW_KEY_2)) {
		speed -= 0.1f;
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = speed * deltaTime;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->MoveForward(cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->MoveForward(-cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpward(-cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpward(cameraSpeed);
		}
	}
	else {

		if (window->KeyHold(GLFW_KEY_W)) {
			player->setAcceleration(player->getAcceleration() + deltaTime * ACCEL_FACTOR);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			player->setAcceleration(player->getAcceleration() - deltaTime * ACCEL_FACTOR);
		}

		if (!player->isDead()) {
			if (window->KeyHold(GLFW_KEY_A)) {
				player->translate(-playerSpeed, 0, 0);
			}

			if (window->KeyHold(GLFW_KEY_D)) {
				player->translate(playerSpeed, 0, 0);
			}
		}
	}
}

void Tema3::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE && !player->isJumping() && !player->isFalling()) {
		player->setJump(true);
	}

	if (key == GLFW_KEY_C) {
		camera_mode = !camera_mode;
	}

	if (key == GLFW_KEY_ENTER) {
		pause = !pause;
	}
}

void Tema3::OnKeyRelease(int key, int mods)
{
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-sensivityOY * deltaY);
			camera->RotateFirstPerson_OY(-sensivityOX * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-sensivityOY * deltaY);
			camera->RotateThirdPerson_OY(-sensivityOX * deltaX);
		}

	}
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}
