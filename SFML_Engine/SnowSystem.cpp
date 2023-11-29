#include "SnowSystem.h"
#include <chrono>

SnowSystem::SnowSystem(SpriteCollection* _pSpriteCollection, Camera* _pCamera, int* _pScreenW, int* _pScreenH, glm::vec2 cameraPos){
	pSpriteCollection = _pSpriteCollection;
	pCamera = _pCamera;
	pScreenW = _pScreenW;
	pScreenH = _pScreenH;
	//loop through array and fill
	for (int i = 0; i < maxSize; i++) {
		snowParts[i] = getNewSnowPart(cameraPos);
	}
	pTexture = pSpriteCollection->getPointerFromName("snow1");
	pMenuTexture = pSpriteCollection->getPointerFromName("menu_snow");
}

void SnowSystem::run() {
	time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//get direction vector
	glm::vec2 direction = glm::vec2(cos(fallAngle), sin(fallAngle));
	glm::vec2 cameraPos = pCamera->getPosition();
	//get normal to direction vector
	glm::vec2 normalDirection = glm::vec2(direction.y*0.5, direction.x*0.5);
	for (int i = 0; i < size; i++) {
		if (snowParts[i].opacity < snowParts[i].maxOpacity) {
			snowParts[i].opacity += 0.01;
		}
		snowParts[i].x += direction.x * fallSpeed + sinMultiplier*sin(0.002 * time + snowParts[i].phase) * normalDirection.x;
		snowParts[i].y += direction.y * fallSpeed + sinMultiplier * sin(0.002 * time + snowParts[i].phase) * normalDirection.y;
		if ((snowParts[i].x < cameraPos.x - *pScreenW / 2 - 2*1000 && direction.x < 0) ||
			(snowParts[i].y < cameraPos.y - *pScreenH / 2 - 2*1000 && direction.y < 0) ||
			(snowParts[i].x > cameraPos.x + *pScreenW / 2 && direction.x > 0) ||
			(snowParts[i].y > cameraPos.y + *pScreenH / 2 && direction.y > 0)) {
			snowParts[i] = getNewSnowPart(cameraPos);
		}
	}
}

void SnowSystem::draw(float z){
	for (int i = 0; i < size; i++) {
		pSpriteCollection->addImageDraw(pTexture, snowParts[i].x, snowParts[i].y, z, 2, snowParts[i].opacity * opacity, 800*2, 800*2);
	}
	glm::vec2 cameraPos = pCamera->getPosition();
	//pSpriteCollection->addRectDraw(-19.2/2, -10.8/2, 19.2, 10.8, 1100000, sf::Color(0, 0, 255));
	pSpriteCollection->addRectDraw(cameraPos.x - *pScreenW / 2, cameraPos.x - *pScreenH / 2, *pScreenW, *pScreenH, 100000, sf::Color(255, 255, 255, 150*(size/maxSize)));
}

void SnowSystem::drawMenu(float z, float scale) {
	for (int i = 0; i < size; i++) {
		pSpriteCollection->addImageDraw(pMenuTexture, snowParts[i].x, snowParts[i].y, z, scale, snowParts[i].opacity * opacity, 1000 * scale, 1000 * scale);

		//pSpriteCollection->addRectDraw((snowParts[i].x - 800) / 100, (snowParts[i].y - 800) / 100, 16, 16, 1200000, sf::Color(0, 255, 0, 10));

	}
	//pSpriteCollection->addRectDraw(-19.2/2, -10.8/2, 19.2, 10.8, 1100000, sf::Color(0, 0, 255));
}

void SnowSystem::setFallAngle(float _fallAngle) {
	fallAngle = _fallAngle;
}

void SnowSystem::setSpeed(float _fallSpeed){
	fallSpeed = _fallSpeed;
}

void SnowSystem::setOpacity(float _opacity){
	opacity = _opacity;
}

void SnowSystem::setSize(int _size){
	size = _size;
}

void SnowSystem::changeSize(int change){
	size += change;
	if (size > maxSize) {
		size = maxSize;
	}
	else if (size < 0) {
		size = 0;
	}
}

void SnowSystem::setSinMultiplier(float sM){
	sinMultiplier = sM;
}

SnowPart SnowSystem::getNewSnowPart(glm::vec2 cameraPos){
	SnowPart temp = SnowPart();
	temp.x = cameraPos.x - borderSize - *pScreenW/2 + rand() % (*pScreenW + borderSize*2);
	temp.y = cameraPos.y - borderSize - *pScreenH/2 + rand() % (*pScreenH + borderSize * 2);
	glm::vec2 direction = glm::vec2(cos(fallAngle), sin(fallAngle));
	temp.x -= direction.x * 1000;
	temp.y -= direction.y * 1000;
	temp.maxOpacity = ((float)rand() / (float)RAND_MAX) / 1.5;
	temp.opacity = 0;
	temp.phase = (float)rand() / (float)RAND_MAX * 3.1415 * 2;
	return temp;
}
