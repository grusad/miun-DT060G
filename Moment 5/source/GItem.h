#pragma once

#include <string>
#include <functional>

class GItem {

private:
	std::string itemText;
	std::function<void()> callBack;
	bool locked = false;

public:

	GItem(const std::string text, std::function<void()> callback, bool locked);

	std::string getText() const;
	void setText(const std::string text);
	void exec();
	void setLocked(const bool locked) { this->locked = locked; };
	bool isLocked() const { return locked; };


};