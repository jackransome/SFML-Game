#pragma once
#include <glm/glm.hpp>

class Camera {
public:
	Camera();
	void setPosition(glm::vec2 newPosition);
	void setPosition(float x, float y);
	void setScreenDimensions(int* w, int* h);
	glm::vec2 getPosition();
	glm::vec2 transformPosition(glm::vec2 toTransform);
	void setScreenshakeAmount(float amount);
	void addScreenshake(float amount);
	void setScreenshakeDecay(float decay);
	void setScreenshakeCutoff(float cutoff);
	void runscreenShake();
	void setScale(float _scale);
private:
	float screenshake = 0;
	float maxScreenShake = 30;
	float screenshakeDecay;
	float screenshakeCutoff;
	int* pScreenW;
	int* pScreenH;
	float scale = 1;
	glm::vec2 position;
	glm::vec2 screenshakePosition;
};