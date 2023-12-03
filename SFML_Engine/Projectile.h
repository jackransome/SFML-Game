#include "SpriteCollection.h"
#include "Console.h"

class Projectile {
public:
	Projectile(SpriteCollection* _pSpriteCollection, Console* _pConsole, float _x, float _y, float rotation, float speed, int fromID);
	glm::vec2 getPosition() { return position; }
	glm::vec2 getLastPosition() { return lastPosition; }
	void run();
	void pull(float _force, glm::vec2 _position);
	void draw();
	bool toDelete = false;;
	void setPosition(glm::vec2 _position);
	int getFromID();
private:
	int fromID = -1;
	glm::vec2 position;
	int range = 500;
	float distanceTraveled = 0;
	float rotation;
	float speed;
	glm::vec2 velocity;
	glm::vec2 lastPosition;
	SpriteCollection* pSpriteCollection;
	Console* pConsole;
};
