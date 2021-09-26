#include "SpriteCollection.h"

SpriteCollection::SpriteCollection() {}

SpriteCollection::SpriteCollection(sf::RenderWindow* pwindow) {
	pWindow = pwindow;
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
