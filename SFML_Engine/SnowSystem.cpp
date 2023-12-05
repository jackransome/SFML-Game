#include "SnowSystem.h"
#include <chrono>

SnowSystem::SnowSystem(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, int* _pScreenW, int* _pScreenH, glm::vec2 cameraPos){
	pSpriteCollection = _pSpriteCollection;
	pCamera = _pCamera;
	pScreenW = _pScreenW;
	pScreenH = _pScreenH;
	pSoundPlayer = _pSoundPlayer;
	windSoundID = pSoundPlayer->playSoundByName("wind", 0.15);
	pSoundPlayer->loopSound(windSoundID);
	//loop through array and fill
	for (int i = 0; i < maxSize; i++) {
		snowParts[i] = getNewSnowPart(cameraPos);
	}
	pTexture = pSpriteCollection->getPointerFromName("snow1");
	pMenuTexture = pSpriteCollection->getPointerFromName("menu_snow");
}

void SnowSystem::run() {
	if (abs(fallAngle - fallAngleTarget) < 0.1) {
		fallAngle = fallAngleTarget;
	}
	if (abs(fallSpeed - fallAngleTarget) < 0.1) {
		fallSpeed = fallAngleTarget;
	}
	if (abs(opacity - opacityTarget) < 0.01) {
		opacity = opacityTarget;
	}

	if (size < sizeTarget) {
		size += 0.3;
	}
	else if (size > sizeTarget) {
		size -= 0.3;
	}
	if (opacity > opacityTarget) {
		opacity -= 0.01;
	}
	else if (opacity < opacityTarget)  {
		opacity += 0.01;
	}

	if (fallSpeed > fallSpeedTarget) {
		fallSpeed -= 0.1;
	}
	else if (opacity < opacityTarget) {
		fallSpeed += 0.1;
	}
	if (fallAngle > fallAngleTarget) {
		fallAngle -= 0.01;
	}
	else if (opacity < opacityTarget) {
		fallAngle += 0.01;
	}




	time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//get direction vector
	glm::vec2 direction = glm::vec2(cos(fallAngle), sin(fallAngle));
	glm::vec2 cameraPos = pCamera->getPosition();
	//get normal to direction vector
	glm::vec2 normalDirection = glm::vec2(direction.y*0.5, direction.x*0.5);
	for (int i = 0; i < floor(size); i++) {
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
	if (menuMode || !active) {
		pSoundPlayer->setVolume(windSoundID, 0);
	}
	else {
		pSoundPlayer->setVolume(windSoundID, 0.5*(float(size) / float(maxSize)));
	}
}

void SnowSystem::draw(float z){
	menuMode = false;
	for (int i = 0; i < floor(size); i++) {
		pSpriteCollection->addImageDraw(pTexture, snowParts[i].x, snowParts[i].y, z, 2, snowParts[i].opacity * opacity, 800*2, 800*2);
	}
	glm::vec2 cameraPos = pCamera->getPosition();
	pSpriteCollection->addImageDrawCut(pSpriteCollection->getPointerFromName("white_background"), cameraPos.x - *pScreenW / 2, cameraPos.x - *pScreenH / 2, 100000, 0, 0, *pScreenW, *pScreenH, 1, 0.33 * (float(size) / float(maxSize)));
	pSpriteCollection->addImageDrawCut(pSpriteCollection->getPointerFromName("white_surround"), cameraPos.x - 2000, cameraPos.y - 2000, 100000, 0, 0, 4000, 4000, 1, 0.8 * (float(size) / float(maxSize)));

}

void SnowSystem::drawMenu(float z, float scale) {
	menuMode = true;
	for (int i = 0; i < floor(size); i++) {
		pSpriteCollection->addImageDraw(pMenuTexture, snowParts[i].x, snowParts[i].y, z, scale, snowParts[i].opacity * opacity, 1000 * scale, 1000 * scale);

		//pSpriteCollection->addRectDraw((snowParts[i].x - 800) / 100, (snowParts[i].y - 800) / 100, 16, 16, 1200000, sf::Color(0, 255, 0, 10));

	}
	//pSpriteCollection->addRectDraw(-19.2/2, -10.8/2, 19.2, 10.8, 1100000, sf::Color(0, 0, 255));
}

void SnowSystem::setFallAngle(float _fallAngle) {
	fallAngle = _fallAngle;
	fallAngleTarget = _fallAngle;
}

void SnowSystem::setSpeed(float _fallSpeed){
	fallSpeed = _fallSpeed;
	fallSpeedTarget = _fallSpeed;
}

void SnowSystem::setOpacity(float _opacity){
	opacity = _opacity;
	opacityTarget = _opacity;
}

void SnowSystem::setSize(int _size){
	size = _size;
	sizeTarget = _size;
}

void SnowSystem::changeFallAngle(float _fallAngle) {
	fallAngleTarget = _fallAngle;
}

void SnowSystem::changeSpeed(float _fallSpeed) {
	fallSpeedTarget = _fallSpeed;
}

void SnowSystem::changeOpacity(float _opacity) {
	opacityTarget = _opacity;
}

void SnowSystem::changeSize(int _size) {
	sizeTarget = _size;
}

void SnowSystem::setSinMultiplier(float sM){
	sinMultiplier = sM;
}

void SnowSystem::setActive(bool _active){
	active = _active;
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
