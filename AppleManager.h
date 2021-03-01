#pragma once
#include "Apple.h"
#include "Snake.h"
#include <list>
class AppleManager {
public:
	AppleManager();
	~AppleManager();
	void CreateNewApple(std::list<Snake> snake);
	Apple GetApple();
private:
	Apple apple;
};