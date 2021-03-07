#pragma once

#include <Component/SimpleScene.h>
#include "Camera.h"
#include "Object3D.h"
#include "Transform3D.h"
#include "Player.h"
#include "Platform.h"
#include "Constants.h"
#include "Pattern.h"
#include "Generator.h"
#include "Matrix.h"

class Tema3 : public SimpleScene
{
	public:
		Tema3();
		~Tema3();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture, const int type);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		std::unordered_map<std::string, Texture2D*> mapTextures;
		std::unordered_map<std::string, glm::mat4> playerModelMatrix, alienModelMatrix;
		Cam::Camera *camera;
		glm::mat4 projectionMatrix;
		Player* player;
		Platform* start_platform;
		Generator* generator;
		bool camera_mode;
		int skysphere, flame, spin, speed;
		glm::vec3 lightPosition[PATTERN_COUNT];
		glm::vec3 lightColor[PATTERN_COUNT];
		int spots[PATTERN_COUNT];
		float angle[PATTERN_COUNT];
		glm::vec3 lightDirection[PATTERN_COUNT];
		unsigned int materialShininess;
		float materialKd;
		float materialKs;
		bool pause;
};
