#pragma once

#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"
#include "../../include/glm/glm.hpp"

#include "../input/input.h"

namespace voxey::rendering
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void cameraUpdate(double deltaTime);
		void cameraInputUpdate(double deltaTime);

		void registerCameraKeybinds();

	private:
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 view = glm::mat4(0.0f);
	};

}

