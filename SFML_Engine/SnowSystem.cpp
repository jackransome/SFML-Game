#include "SnowSystem.h"
#include <chrono>

SnowSystem::SnowSystem(SpriteCollection* _pSpriteCollection, int* _pScreenW, int* _pScreenH, glm::vec2 cameraPos){
	pSpriteCollection = _pSpriteCollection;
	
	pScreenW = _pScreenW;
	pScreenH = _pScreenH;
	//loop through array and fill
	for (int i = 0; i < maxSize; i++) {
		snowParts[i] = getNewSnowPart(cameraPos);
	}
	pTexture = pSpriteCollection->getPointerFromName("snow1");
}

void SnowSystem::run(glm::vec2 cameraPos) {
	time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//get direction vector
	glm::vec2 direction = glm::vec2(cos(fallAngle), sin(fallAngle));
	//get normal to direction vector
	glm::vec2 normalDirection = glm::vec2(direction.y*0.5, direction.x*0.5);
	for (int i = 0; i < size; i++) {
		if (snowParts[i].opacity < snowParts[i].maxOpacity) {
			snowParts[i].opacity += 0.01;
		}
		snowParts[i].x += direction.x * fallSpeed + sin(0.002 * time + snowParts[i].phase) * normalDirection.x;
		snowParts[i].y += direction.y * fallSpeed + sin(0.002 * time + snowParts[i].phase) * normalDirection.y;
		if ((snowParts[i].x < cameraPos.x - *pScreenW / 2 && direction.x < 0) ||
			(snowParts[i].y < cameraPos.y - *pScreenH / 2 && direction.y < 0) ||
			(snowParts[i].x > cameraPos.x + *pScreenW / 2 && direction.x > 0) ||
			(snowParts[i].y > cameraPos.y + *pScreenH / 2 && direction.y > 0)) {
			snowParts[i] = getNewSnowPart(cameraPos);
		}
	}
}

void SnowSystem::draw(float z){
	for (int i = 0; i < size; i++) {
		pSpriteCollection->addImageDraw(pTexture, snowParts[i].x - 800, snowParts[i].y - 800, z, 2, snowParts[i].opacity * opacity);
		
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
