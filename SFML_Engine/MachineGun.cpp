#include "MachineGun.h"
#include <glm/gtx/vector_angle.hpp>

MachineGun::MachineGun(Console* _pConsole, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer) :
    Tool(3, ItemType::buildTool, _pConsole, _pSpriteCollection, "gun1Icon") {
    usedTexture = pSpriteCollection->getPointerFromName("machineGun");
    usedFlippedTexture = pSpriteCollection->getPointerFromName("machineGunFlipped");
    pSoundPlayer = _pSoundPlayer;
}

MachineGun::~MachineGun() {}

void MachineGun::activate(glm::vec2 position, glm::vec2 target, int _parentId) {
    if (!latch && !lastLatch) {
        float rotation = angleFromPositionToPosition(position, target) * (2.0 * 3.14159) / 360.0f;
        pConsole->addCommand(commandAddProjectile, position.x, position.y, rotation, 60.0f, _parentId, 0);
        pConsole->addCommand(commandPlaySound, "laser_shot2", 0.2);
        activated = true;
    }
    //pConsole->addCommand(commandAddBeam, position.x, position.y, target.x, target.y, _parentId);

    latch = true;
}

void MachineGun::drawUsing(glm::vec2 position, glm::vec2 target, int z) {
    float rotation = angleFromPositionToPosition(position, target);
    if (rotation > 270 || rotation < 90) {
        pSpriteCollection->addRotatedImageDrawCut(usedTexture, position.x - 40, position.y - 10, z, 0, 0, 40, 10, 2, rotation);
    }
    else {
        pSpriteCollection->addRotatedImageDrawCut(usedFlippedTexture, position.x - 40, position.y - 10, z, 0, 0, 40, 10, 2, rotation);
    }
}

float MachineGun::angleFromPositionToPosition(const glm::vec2& fromPos, const glm::vec2& toPos) {
    // Calculate the direction vector from fromPos to toPos
    glm::vec2 direction = toPos - fromPos;

    // Normalize the direction vector
    glm::vec2 normDirection = glm::normalize(direction);

    // Calculate the angle in radians from the positive x-axis
    double angleRadians = atan2(normDirection.y, normDirection.x);

    // Convert the angle to degrees
    double angleDegrees = glm::degrees(angleRadians);

    // Ensure the angle is in the range [0, 360)
    if (angleDegrees < 0) {
        angleDegrees += 360.0;
    }

    return angleDegrees;
}


void MachineGun::update() {
    lastLatch = latch;
    latch = false;
    /*if (activated) {
        if (!beamSoundPlaying) {
            beamSoundId = pSoundPlayer->playSoundByName("beam_1", 0.15);

            pSoundPlayer->loopSound(beamSoundId);
            beamSoundPlaying = true;
        }
    } if (!activated) {
        if (beamSoundPlaying) {
            pSoundPlayer->stopSound(beamSoundId);
            beamSoundPlaying = false;
        }
    }
    activated = false;*/
}
