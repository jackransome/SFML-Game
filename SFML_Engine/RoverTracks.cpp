#include "RoverTracks.h"

RoverTracks::RoverTracks(SpriteCollection* _pSpriteCollection, float x, float y, float _rotation) :
	Decoration(_pSpriteCollection, x, y) {
	opacity = 1;
	decay = 0.97;
	rotation = _rotation;
	type = objectRoverTracks;
}

void RoverTracks::draw() {
	//pSpriteCollection->addRectDraw(boundingBox.x, boundingBox.y, 16, 16, -10000, sf::Color(0, 0, 0, opacity));
	pSpriteCollection->addRotatedImageDraw(pSpriteCollection->getPointerFromName("decoration_rover_tracks_1"), boundingBox.x-14, boundingBox.y-10, -10001, 2, opacity, rotation, 14, 10);
	//pSpriteCollection->addCircleDraw()
}

void RoverTracks::update() {
	opacity *= decay;
	if (opacity < 0.05) {
		toDestroy = true;
	}
}