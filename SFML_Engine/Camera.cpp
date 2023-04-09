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

void Camera::setScreenDimensions(int* w, int* h) {
	pScreenW = w;
	pScreenH = h;
}

glm::vec2 Camera::getPosition() {
	return position - screenshakePosition;
}

glm::vec2 Camera::transformPosition(glm::vec2 toTransform) {
	return toTransform - position + glm::vec2(*pScreenW /2, *pScreenH /2) + screenshakePosition;
}

void Camera::setScreenshakeAmount(float amount){
	screenshake = amount;
}

void Camera::addScreenshake(float amount){
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
	if (screenshake > 0) {
		int e = 3;
	}
	screenshakePosition.x = ((double)rand() / (RAND_MAX)) * screenshake - screenshake / 2;
	screenshakePosition.y = ((double)rand() / (RAND_MAX)) * screenshake - screenshake / 2;
}
