#include "GItem.h"

GItem::GItem(const std::string text, std::function<void()> callBack, bool locked) {
	this->itemText = text;
	this->callBack = callBack;
	this->locked = locked;
}


std::string GItem::getText() const {
	return itemText;
}

void GItem::setText(const std::string text) {
	this->itemText = text;
}

void GItem::exec() {
	callBack();
}