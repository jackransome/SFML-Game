#include "Tool.h"
#include "iostream"
Tool::Tool(int _maxAttachments) {
	maxAttachments = _maxAttachments;
	attachments = new Item*[maxAttachments];
}

Tool::~Tool() {}

int Tool::getTotalAttachments(){
	return totalAttachments;
}

int Tool::getMaxAttachments() {
	return maxAttachments;
}

Item* Tool::getAttachment(int _index) {
	if (_index > totalAttachments - 1) {
		std::cout << "attachment does not exist\n";
		return nullptr;
	}
	return attachments[_index];
}

void Tool::addAttachment(Item* _attachment){
	if (totalAttachments == maxAttachments) {
		std::cout << "not enough space for attachment\n";
	}
	attachments[totalAttachments] = _attachment;
	totalAttachments++;
}

Item* Tool::removeAttachment(int _index){
	if (_index > totalAttachments - 1) {
		std::cout << "attachment does not exist\n";
		return nullptr;
	}
	Item* temp = attachments[_index];
	//shift the other attachments
	for (int i = _index; i < totalAttachments - 1; i++) {
		attachments[i] = attachments[i + 1];
	}
	totalAttachments--;

	return temp;
}
