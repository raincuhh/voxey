#pragma once

#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/matrix_transform.hpp"

#include "../input/input.h"

namespace voxey::rendering
{
	class Camera
	{
	public:
		Camera(glm::vec3 pos, float width, float height, GLFWwindow* window);
		~Camera();

		void cameraUpdate(double deltaTime);
		void cameraInputUpdate(double deltaTime);

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjMatrix() const;

	private:
		GLFWwindow* mWindow;

		float screenWidth;
		float screenHeight;
		

		float sensitivty = 0.1f;
		float speed = 4.5f;

		glm::vec3 position;
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);

		//glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
	};
}

