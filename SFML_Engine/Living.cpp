#include "Living.h"

Living::Living(float _maxHealth, float _regenRate) {
	maxHealth = health = _maxHealth;
	regenRate = _regenRate;
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