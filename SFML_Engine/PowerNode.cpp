#include "PowerNode.h"


bool PowerNode::getGenerator(){
	return generator;
}

bool PowerNode::getBuilt(){
	return built;
}

void PowerNode::setBuilt(){
	built = true;
}

void PowerNode::removeConnection(int _id){
	for (int i = 0; i < connections.size(); i++) {
		if (connections[i]->getPowerId() == _id) {
			connections.erase(connections.begin() + i);
			return;
		}
	}
}

void PowerNode::addConnection(PowerNode* node){
	connections.push_back(node);
}

float PowerNode::getCapacityLeft(){
	return capacity - charge;
}

float PowerNode::getPercentage(){
	return charge/capacity;
}

void PowerNode::removeConnection(PowerNode* node){
	connections.erase(std::remove(connections.begin(), connections.end(), node), connections.end());
}

void PowerNode::distribute(){
	if (!distributor || charge < dischargeRate) return;
	int counter = 0;
	for (int i = 0; i < connections.size(); i++) {
		if (connections[i]->getBuilt() && !connections[i]->getGenerator() && connections[i]->getCapacityLeft() > 0) {
			counter++;
		}
	}
	for (int i = 0; i < connections.size(); i++) {
		if (connections[i]->getBuilt() && !connections[i]->getGenerator() && connections[i]->getCapacityLeft() > 0) {
			float amount = std::min(dischargeRate / counter, connections[i]->getCapacityLeft());
			discharge(amount);
			connections[i]->addCharge(amount);
		}
	}
}

void PowerNode::addCharge(float amount){
	charge += amount;
	if (charge > capacity) {
		charge = capacity;
	}
}

void PowerNode::discharge(float amount){
	charge -= amount;
	if (charge < 0) {
		charge = 0;
	}
}

void PowerNode::updatePosition(float _x, float _y){
	position.x = _x;
	position.y = _y;
}

glm::vec2 PowerNode::getPosition() {
	return position;
}

int PowerNode::getPowerId(){
	if (idPointer == nullptr) return -1;
	return *idPointer;
}

void PowerNode::removeFromConnections(){
	for (int i = 0; i < connections.size(); i++) {
		connections[i]->removeConnection(*idPointer);
	}
}

void PowerNode::drawConections(){
	glm::vec2 drawPos;
	glm::vec2 difference;
	float length;
	float rotation;
	for (int i = 0; i < connections.size(); i++){
		if (connections[i]->getBuilt() && connections[i]->getPowerId() < getPowerId()) {
			drawPos = position / 2.0f + connections[i]->getPosition() / 2.0f;
			difference = connections[i]->getPosition() - position;
			length = sqrt(difference.x * difference.x + difference.y * difference.y);
			if (length > 200) {
				connections.erase(connections.begin() + i);
				i--;
				continue;
			}
			rotation = -ppConsole->getAtan2Value(difference.x, difference.y) * 180.0 / 3.141592 - 90;
			pSpriteCollection->addRotatedImageDrawCut(pSpriteCollection->getPointerFromName("power_cable"), drawPos.x - length / 2, drawPos.y - 3, -1000000, 0, 0, length / 2, 3, 2, rotation);
		}
	}
	//void addRotatedImageDrawCut(TextureWrapper * pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation);
}
