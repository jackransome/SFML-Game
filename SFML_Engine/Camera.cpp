#include "Camera.h"

Camera::Camera() {
	screenshakePosition.x = 0;
	screenshakePosition.y = 0;
}

void Camera::setPosition(glm::vec2 newPosition) {
	position = newPosition;
}

void Camera::setPosition(float x, float y) {
	position = glm::vec2(x, y);
}

void Camera::setScreenDimensions(int w, int h) {
	screenW = w;
	screenH = h;
}

glm::vec2 Camera::getPosition() {
	return position + screenshakePosition;
}

glm::vec2 Camera::transformPosition(glm::vec2 toTransform) {
	return toTransform - position + glm::vec2(screenW/2, screenH/2) + screenshakePosition;
}

void Camera::setScreenshakeAmount(int amount){
	screenshake = amount;
}

void Camera::addScreenshake(int amount){
	screenshake += amount;
}

void Camera::setScreenshakeDecay(float decay) {
	screenshakeDecay = decay;
}

void Camera::setScreenshakeCutoff(float cutoff) {
	screenshakeCutoff = cutoff;
}

void Camera::runscreenShake(){
	if (screenshake < screenshakeCutoff) {
		screenshake = 0;
	}
	screenshake *= screenshakeDecay;
	screenshakePosition.x = ((double)rand() / (RAND_MAX)) * screenshake;
	screenshakePosition.y = ((double)rand() / (RAND_MAX)) * screenshake;
}
