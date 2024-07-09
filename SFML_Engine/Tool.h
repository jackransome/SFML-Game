#pragma once
#include "Item.h"

class Tool : public Item {
public:
	Tool(int _maxAttachments);
	~Tool();
	virtual void activate() = 0;
	virtual void drawUsing() = 0;
	virtual void update() = 0;
	int getTotalAttachments();
	int getMaxAttachments();
	Item* getAttachment(int _index);
	void addAttachment(Item* _attachment);
	Item* removeAttachment(int _index);
private:
	int maxAttachments = 0;
	int totalAttachments = 0;
	Item** attachments;
};