#include "Console.h"
#include <chrono>

Console::Console() {
	commands = std::queue<Command>();
	int e = commands.size();
	int r = 4;
	trigTable.resize(361); // Resize the vector to hold 361 elements

	for (int i = 0; i <= 360; ++i) {
		float rad = i * 3.14159265358979323846f / 180.0f; // Use a more precise value of π
		trigTable[i] = glm::vec2(cos(rad), sin(rad));
	}
}

void Console::addCommand(CommandType _type) {
	commands.push(Command(_type));
}

void Console::addCommand(CommandType _type, int _a) {
	commands.push(Command(_type, _a));
}

void Console::addCommand(CommandType _type, float _f1) {
	commands.push(Command(_type, _f1));
}

void Console::addCommand(CommandType _type, float _f1, float _f2, float _f3, float _f4){
	commands.push(Command(_type, _f1, _f2, _f3, _f4));
}

void Console::addCommand(CommandType _type, float _f1, float _f2, float _f3, float _f4, int _a) {
	commands.push(Command(_type, _f1, _f2, _f3, _f4, _a));
}

void Console::addCommand(CommandType _type, float _f1, float _f2, float _f3, float _f4, int _a, int _b){
	commands.push(Command(_type, _f1, _f2, _f3, _f4, _a, _b));
}

void Console::addCommand(CommandType _type, std::string _string) {
	commands.push(Command(_type, _string));
}

void Console::addCommand(CommandType _type, std::string _string, float _f1){
	commands.push(Command(_type, _string, _f1));
}

void Console::addCommand(CommandType _type, std::string _string, float _f1, float _f2) {
	commands.push(Command(_type, _string, _f1, _f2));
}

void Console::addCommand(CommandType _type, ObjectType _objectType, float _f1, float _f2) {
	commands.push(Command(_type, _objectType, _f1, _f2));
}

void Console::addCommand(CommandType _type, ObjectType _objectType, float _f1, float _f2, float _f3) {
	commands.push(Command(_type, _objectType, _f1, _f2, _f3));
}

void Console::addCommand(CommandType _type, ObjectType _objectType, float _f1, float _f2, float _f3, float _f4) {
	commands.push(Command(_type, _objectType, _f1, _f2, _f3, _f4));
}

void Console::addCommand(CommandType _type, float _f1, float _f2) {
	commands.push(Command(_type, _f1, _f2));
}

void Console::addCommand(Command command) {
	commands.push(command);
}

void Console::addTime(std::string label){
	timeStamps.push(TimeStamp());
	timeStamps.back().label = label;
	timeStamps.back().time = getTime();
}

void Console::setControlPosition(glm::vec2 _controlPosition){
	controlPositon = _controlPosition;
}

glm::vec2 Console::getControlPosition(){
	return controlPositon;
}

TimeStamp Console::getTimeStamp(){
	TimeStamp temp = timeStamps.front();
	timeStamps.pop();
	return temp;
}

bool Console::hasTimeStamps(){
	return timeStamps.size() > 0;
}

int Console::getSize() {
	return commands.size();
}

int Console::getTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Console::incrementFrame() {
	frame++;
}

int Console::getFrame() {
	return frame;
}

Command Console::getCommand(bool toLog) {
	Command temp = commands.front();
	commands.pop();
	if (enableLogging && toLog) {
		log.push(temp);
	}
	return temp;
}

float Console::getSinValue(int degrees){
	if (degrees >= 360 || degrees < 0) {
		degrees = (degrees % 360 + 360) % 360;
	}
	return trigTable[degrees].y;
}

float Console::getCosValue(int degrees) {
	if (degrees >= 360 || degrees < 0) {
		degrees = (degrees % 360 + 360) % 360;
	}
	return trigTable[degrees].x;
}

glm::vec2 Console::getTrigValue(int degrees) {
	if (degrees >= 360 || degrees < 0) {
		degrees = (degrees % 360 + 360) % 360;
	}
	return trigTable[degrees];
}
