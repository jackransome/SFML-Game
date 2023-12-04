#pragma once

class Living {
public:
	Living(float _maxHealth, float _regenRate);
	virtual void onDeath() {};
	float getHealth();
	float getMaxHealth();
	void doDamage(float damage);

private:
	float maxHealth;
	float health;
	float regenRate;
};