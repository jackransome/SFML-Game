#include "Living.h"

Living::Living(float _maxHealth, float _regenRate, FactionIdentifier _faction) {
	maxHealth = health = _maxHealth;
	regenRate = _regenRate;
	faction = _faction;
}

float Living::getHealth() {
	return health;
}

float Living::getMaxHealth(){
	return maxHealth;
}

void Living::doDamage(float damage) {
	health -= damage;
	if (health <= 0) {
		onDeath();
	}
}

FactionIdentifier Living::getFaction(){
	return faction;
}
