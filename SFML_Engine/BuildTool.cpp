#include "BuildTool.h"
#include <glm/gtx/vector_angle.hpp>

BuildTool::BuildTool(Console* _pConsole, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer) :
	Tool(3, ItemType::buildTool, _pConsole, _pSpriteCollection, "buildToolIcon") {
	usedTexture = pSpriteCollection->getPointerFromName("buildTool");
    usedFlippedTexture = pSpriteCollection->getPointerFromName("buildToolFlipped");
    pSoundPlayer = _pSoundPlayer;
}

BuildTool::~BuildTool() { }

void BuildTool::activate(glm::vec2 position, glm::vec2 target, int _parentId) {
    pConsole->addCommand(commandAddBeam, position.x, position.y, target.x, target.y, _parentId);
    activated = true;
}

void BuildTool::drawUsing(glm::vec2 position, glm::vec2 target, int z) {
	float rotation = angleFromPositionToPosition(position, target);
    if (rotation > 270 || rotation < 90) {
        pSpriteCollection->addRotatedImageDrawCut(usedTexture, position.x - 31, position.y - 14, z, 0, 0, 31, 14, 2, rotation);
    }
    else {
        pSpriteCollection->addRotatedImageDrawCut(usedFlippedTexture, position.x - 31, position.y - 14, z, 0, 0, 31, 14, 2, rotation);
    }
}

float BuildTool::angleFromPositionToPosition(const glm::vec2& fromPos, const glm::vec2& toPos) {
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


void BuildTool::update() {
    if (activated) {
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
    activated = false;
}
