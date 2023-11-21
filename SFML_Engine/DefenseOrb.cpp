#include "DefenseOrb.h"

DefenseOrb::DefenseOrb(InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float _x, float _y) :
Object(_x, _y, 16, 16, 0, controllable, true),
Living(100, 2, factionFriendly),
Controllable(200) {
	pSpriteCollection = _pSpriteCollection;
	pInputManager = _pInputManager;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	type = objectDefenseOrb;
	mainStack = SpriteStack(pSpriteCollection, "DefenseOrb_stack", 10, 10, 14, 2); //CHANGE
}

DefenseOrb::~DefenseOrb(){
	if (beamSoundPlaying) {
		pSoundPlayer->stopSound(beamSoundId);
	}
}

void DefenseOrb::update(){
	glm::vec2 center = getCenter();
	
	if (controlled) {
		target = glm::vec2(pInputManager->translatedMouseX, pInputManager->translatedMouseY);

		float speed = 0.4;
		float dxv = 0;
		float dyv = 0;
		if (pInputManager->isKeyDown(w)) {
			dyv = -speed;
		}
		if (pInputManager->isKeyDown(a)) {
			dxv = - speed;
		}
		if (pInputManager->isKeyDown(s)) {
			dyv = speed;
		}
		if (pInputManager->isKeyDown(d)) {
			dxv = speed;
		}
		if (dxv != 0 && dyv != 0) {
			dxv *= 1 / sqrt(2);
			dyv *= 1 / sqrt(2);
		}
		boundingBox.xv += dxv;
		boundingBox.yv += dyv;
		
	}
	boundingBox.xv *= 0.90;
	boundingBox.yv *= 0.90;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	rotation = 180.0f * atan2((target.y - center.y), (target.x - center.x)) / (3.1415);
	if (controlled) {
		if (pInputManager->isKeyDown(mouseL)) {
			//glm::vec2 center = getCenter();
			glm::vec2 shootPos = getCenter() + glm::vec2(12 * cos(3.1415 * rotation / 180.0f), 12 * sin(3.1415 * rotation / 180.0f) - 8 + sin(bob_counter) * 3);
			pConsole->addCommand(commandAddBeam, shootPos.x, shootPos.y, target.x, target.y, id);
			if (!beamSoundPlaying) {
				beamSoundId = pSoundPlayer->playSoundByName("beam_1", 0.1);
				pSoundPlayer->loopSound(beamSoundId);
				beamSoundPlaying = true;
			}
		}
		else {
			if (beamSoundPlaying) {
				pSoundPlayer->stopSound(beamSoundId);
			}
			beamSoundPlaying = false;
		}
		if (pInputManager->onKeyDown(mouseR)) {
			glm::vec2 shootPos = getCenter() + glm::vec2(12 * cos(3.1415 * rotation / 180.0f), 12 * sin(3.1415 * rotation / 180.0f) - 8 + sin(bob_counter) * 3);
			//pConsole->addCommand(commandAddProjectile, shootPos.x, shootPos.y, target.x, target.y, id);
			float radians = atan2((target.y - shootPos.y), (target.x - shootPos.x));

			pConsole->addCommand(commandAddProjectile, shootPos.x, shootPos.y, radians, 60, id);

			
			pConsole->addCommand(commandPlaySound, "laser_shot2", 0.2);
		}
	}
}

void DefenseOrb::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 10 + rand() % 10);
}

void DefenseOrb::draw()
{
	float bobHeight = sin(bob_counter) * 4;
	bob_counter += 0.15;
	
	glm::vec2 lightPos = getCenter() + glm::vec2(4 * cos(3.1415 * (rotation + 135) / 180.0f), 4 * sin(3.1415 * (rotation + 135) / 180.0f) - 28 + sin(bob_counter) * 3);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 2, 1);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 0.2, 0);
	mainStack.draw(boundingBox.x - 2, boundingBox.y - 2 + bobHeight, boundingBox.y, rotation + 90);
}

