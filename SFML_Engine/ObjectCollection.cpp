#include "ObjectCollection.h"

ObjectCollection::ObjectCollection() {}

ObjectCollection::ObjectCollection(InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera) {
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	pSoundPlayer = _pSoundPlayer;
	pCamera = _pCamera;
}

void ObjectCollection::draw() {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}
}

void ObjectCollection::update() {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->update();
	}
}

void ObjectCollection::addMainCharacter(float x, float y) {
	objects.push_back(new MainCharacter(pInputManager, pSpriteCollection, x, y));
}
