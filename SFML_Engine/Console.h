#pragma once
#include <string>
#include <queue>
#include <glm/glm.hpp>

enum CommandType{ commandShakeScreen, commandPlaySound, commandAddObject, commandEnableDebug,
	commandSetCameraPos, commandDrawGreenRect, commandDrawRedRect, commandDoAEODamage, commandNull,
	commandDamageAtMouse, commandLoopSound, commandStopSound, commandSetCameraFocusId, commandEnableObjectControls,
	commandDisableObjectControls, commandPickUp, commandDrop, commandSellObjects, commandBlink, commandAddProjectile
};
enum ObjectType{ objectFootprint, objectAction1animation, objectRoverTracks, objectCrate, objectRover, objectMainCharacter, objectRelay, objectNull, objectWall, objectEnemy, objectScrapMetalDrop};

struct Command {
	Command() {}
	Command(CommandType _type) {
		type = _type;
	}
	Command(CommandType _type, float _f1) {
		type = _type;
		f1 = _f1;
	}
	Command(CommandType _type, int _a) {
		type = _type;
		a = _a;
	}
	Command(CommandType _type, std::string _string) {
		type = _type;
		string = _string;
		f1 = 1;
		f2 = 1;
	}
	Command(CommandType _type, std::string _string, float _f1) {
		type = _type;
		string = _string;
		f1 = _f1;
		f2 = 1;
	}
	Command(CommandType _type, std::string _string, float _f1, float _f2) {
		type = _type;
		string = _string;
		f1 = _f1;
		f2 = _f2;
	}
	Command(CommandType _type, float _f1, float _f2) {
		type = _type;
		f1 = _f1;
		f2 = _f2;
	}

	Command(CommandType _type, float _f1, float _f2, float _f3) {
		type = _type;
		f1 = _f1;
		f2 = _f2;
		f3 = _f3;
	}

	Command(CommandType _type, float _f1, float _f2, float _f3, float _f4) {
		type = _type;
		f1 = _f1;
		f2 = _f2;
		f3 = _f3;
		f4 = _f4;
	}

	Command(CommandType _type, float _f1, float _f2, float _f3, float _f4, int _a) {
		type = _type;
		f1 = _f1;
		f2 = _f2;
		f3 = _f3;
		f4 = _f4;
		a = _a;
	}

	Command(CommandType _type, ObjectType _objectType, float _f1, float _f2) {
		type = _type;
		objectType = _objectType;
		f1 = _f1;
		f2 = _f2;
	}
	Command(CommandType _type, ObjectType _objectType, float _f1, float _f2, float _f3) {
		type = _type;
		objectType = _objectType;
		f1 = _f1;
		f2 = _f2;
		f3 = _f3;
	}
	Command(CommandType _type, ObjectType _objectType, float _f1, float _f2, float _f3, float _f4) {
		type = _type;
		objectType = _objectType;
		f1 = _f1;
		f2 = _f2;
		f3 = _f3;
		f4 = _f4;
	}
	CommandType type = commandNull;
	ObjectType objectType = objectNull;
	std::string string;
	float f1 = 0;
	float f2 = 0;
	float f3 = 0;
	float f4 = 0;
	int a = 0;
	int b = 0;
	int c = 0;
};

struct TimeStamp {
	std::string label;
	int time;
};

class Console {
public:
	Console();
	void addCommand(CommandType _type);
	void addCommand(CommandType _type, float _f1);
	void addCommand(CommandType _type, int _a);
	void addCommand(CommandType _type, float _f1, float _f2, float _f3, float _f4);
	void addCommand(CommandType _type, float _f1, float _f2, float _f3, float _f4, int _a);
	void addCommand(CommandType _type, std::string _string);
	void addCommand(CommandType _type, std::string _string, float _f1);
	void addCommand(CommandType _type, std::string _string, float _f1, float _f2);
	void addCommand(CommandType _type, ObjectType _objectType, float _f1, float _f2);
	void addCommand(CommandType _type, ObjectType _objectType, float _f1, float _f2, float _f3);
	void addCommand(CommandType _type, ObjectType _objectType, float _f1, float _f2, float _f3, float _f4);
	void addCommand(CommandType _type, float _f1, float _f2);
	void addCommand(Command command);
	void addTime(std::string label);
	void setControlPosition(glm::vec2 _controlPosition);
	glm::vec2 getControlPosition();
	TimeStamp getTimeStamp();
	bool hasTimeStamps();
	int getSize();
	int getTime();
	void incrementFrame();
	int getFrame();
	Command getCommand(bool toLog = true);
private:
	glm::vec2 controlPositon = glm::vec2(0, 0);
	long int frame = 0;
	bool enableLogging = false;
	std::queue<Command> commands;
	std::queue<Command> log;
	std::queue<TimeStamp> timeStamps;
};