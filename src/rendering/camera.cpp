#include "camera.h"

voxey::rendering::Camera::Camera()
{
	registerCameraKeybinds();
}

voxey::rendering::Camera::~Camera()
{
}

void voxey::rendering::Camera::cameraUpdate(double deltaTime)
{
	(void)deltaTime;
}

void voxey::rendering::Camera::cameraInputUpdate(double deltaTime)
{
	(void)deltaTime;
}

void voxey::rendering::Camera::registerCameraKeybinds()
{
}
