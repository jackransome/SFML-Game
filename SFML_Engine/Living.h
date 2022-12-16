#pragma once

enum FactionIdentifier {factionNeutral, factionHostile, factionFriendly};

class Living {
public:
	Living(float _maxHealth, float _regenRate, FactionIdentifier _faction);
	virtual void onDeath() {};
	float getHealth();
	float getMaxHealth();
	void doDamage(float damage);
	FactionIdentifier getFaction();

private:
	float maxHealth;
	float health;
	float regenRate;
	FactionIdentifier faction = factionNeutral;
};