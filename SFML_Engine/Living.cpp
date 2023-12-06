#include "Living.h"

Living::Living(float _maxHealth, float _regenRate, bool* objectFlag) {
	maxHealth = health = _maxHealth;
	regenRate = _regenRate;
	*objectFlag = true;
}

float Living::getHealth() {
	return health;
}

float Living::getMaxHealth(){
	return maxHealth;
}

void Living::doDamage(float damage) {
	if (health > 0) {
		health -= damage;
		if (health <= 0) {
			onDeath();
		}
	}
}