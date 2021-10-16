#include "Console.h"

Console::Console() {
	commands = std::queue<Command>();
	int e = commands.size();
	int r = 4;
}

void Console::addCommand(CommandType _type) {
	commands.push(Command(_type));
}

void Console::addCommand(CommandType _type, float _f1) {
	commands.push(Command(_type, _f1));
}

void Console::addCommand(CommandType _type, std::string _string) {
	commands.push(Command(_type, _string));
}

void Console::addCommand(CommandType _type, ObjectType _objectType, float _f1, float _f2) {
	commands.push(Command(_type, _objectType, _f1, _f2));
}

void Console::addCommand(CommandType _type, ObjectType _objectType, float _f1, float _f2, float _f3, float _f4) {
	commands.push(Command(_type, _objectType, _f1, _f2, _f3, _f4));
}

void Console::addCommand(CommandType _type, float _f1, float _f2) {
	commands.push(Command(_type, _f1, _f2));
}


int Console::getSize() {
	return commands.size();
}

Command Console::getCommand() {
	Command temp = commands.front();
	commands.pop();
	if (enableLogging) {
		log.push(temp);
	}
	return temp;
}