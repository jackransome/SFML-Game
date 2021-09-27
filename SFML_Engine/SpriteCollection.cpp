#include "SpriteCollection.h"
#include <iostream>
SpriteCollection::SpriteCollection() {}

SpriteCollection::SpriteCollection(sf::RenderWindow* pwindow) {
	pWindow = pwindow;
	spriteDraws = (SpriteDraw*)malloc(sizeof(SpriteDraw) * maxSpriteDraws);
}

void SpriteCollection::createSprite(std::string name, std::string path, int width, int height, int frames){
	sprites.push_back(new Sprite(pWindow, name, path, width, height, frames));
}

void SpriteCollection::createSprite(std::string name, std::string path){
	sprites.push_back(new Sprite(pWindow, name, path));
}

Sprite* SpriteCollection::getPointerFromName(std::string name) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getName().compare(name) == 0) {
			return sprites[i];
		}
	}
}

void SpriteCollection::setUseCamera(bool _useCamera) {
	useCamera = _useCamera;
}

void SpriteCollection::setPCamera(Camera* _pCamera) {
	pCamera = _pCamera;
}

void SpriteCollection::setOrderZ(bool _orderZ) {
	orderZ = _orderZ;
}

void SpriteCollection::addSpriteDraw(Sprite* pSprite, float x, float y, float z){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = SpriteDraw(pSprite, x, y, z);
	currentDrawIndex++;
}

void SpriteCollection::drawAll(){
	if (orderZ) {
		orderByZ();
	}
	glm::vec2 temp;
	for (int i = 0; i < currentDrawIndex; i++) {
		if (useCamera) {
			temp = pCamera->transformPosition(glm::vec2(spriteDraws[i].x, spriteDraws[i].y));
			spriteDraws[i].pSprite->draw(temp.x, temp.y);
		}
		else {
			spriteDraws[i].pSprite->draw(spriteDraws[i].x, spriteDraws[i].y);
		}
	}
	clearSpriteDraws();
}

void SpriteCollection::clearSpriteDraws() {
	currentDrawIndex = 0;
}

void SpriteCollection::orderByZ() {
	SpriteDraw temp;
	for (int i = 0; i < currentDrawIndex; i++) {
		for (int j = 0; j < currentDrawIndex - 1 - i; j++) {
			if (spriteDraws[j].z > spriteDraws[j + 1].z) {
				temp = spriteDraws[j + 1];
				spriteDraws[j + 1] = spriteDraws[j];
				spriteDraws[j] = temp;;
			}
		}
	}
}
