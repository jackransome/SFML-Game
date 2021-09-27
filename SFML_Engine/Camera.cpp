#include "Camera.h"

Camera::Camera() {}

void Camera::setPosition(glm::vec2 newPosition) {
	position = newPosition;
}

void Camera::setScreenDimensions(int w, int h) {
	screenW = w;
	screenH = h;
}

glm::vec2 Camera::getPosition() {
	return position;
}

glm::vec2 Camera::transformPosition(glm::vec2 toTransform) {
	return toTransform - position + glm::vec2(screenW/2, screenH/2);;
}