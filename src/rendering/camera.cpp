#include "camera.h"

voxey::rendering::Camera::Camera(glm::vec3 pos, float width, float height, GLFWwindow* window) :
	screenWidth(width),
	screenHeight(height),
	position(pos),
	mWindow(window)
{
}

voxey::rendering::Camera::~Camera()
{
}

void voxey::rendering::Camera::cameraUpdate(const double deltaTime)
{
	(void)deltaTime;

	//cameraFront = glm::normalize(voxey::input::Input::getDirection());
	right = glm::normalize(glm::cross(front, up));
	up = glm::normalize(glm::cross(right, front));

	std::cout << "pos: (" << static_cast<int>(position.x) << ", " << static_cast<int>(position.y) << ", " << static_cast<int>(position.z) << ")" << std::endl;
}

void voxey::rendering::Camera::cameraInputUpdate(const double deltaTime)
{
	if (voxey::input::Input::isActionPressed("W"))
	{
		position += front * speed * (float)deltaTime;
	}

	if (voxey::input::Input::isActionPressed("S"))
	{
		position -= front * speed * (float)deltaTime;
	}

	if (voxey::input::Input::isActionPressed("A"))
	{
		position -= right * speed * (float)deltaTime;
	}

	if (voxey::input::Input::isActionPressed("D"))
	{
		position += right * speed * (float)deltaTime;
	}

	if (voxey::input::Input::isActionPressed("SPACE"))
	{
		position.y += speed * (float)deltaTime;
	}
	if (voxey::input::Input::isActionPressed("LEFT_SHIFT"))
	{
		position.y -= speed * (float)deltaTime;
	}
}

glm::mat4 voxey::rendering::Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 voxey::rendering::Camera::getProjMatrix() const
{
	return glm::perspective(glm::radians(90.0f), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 100.0f);
}
