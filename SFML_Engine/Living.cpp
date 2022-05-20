#include "Living.h"

Living::Living(float _maxHealth, float _regenRate) {
	maxHealth = health = _maxHealth;
	regenRate = _regenRate;
}

float Living::getHealth() {
	return health;
}

void Living::doDamage(float damage) {
	health -= damage;
	if (health <= 0) {
		onDeath();
	}
}
