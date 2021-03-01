#pragma once
#include <iostream>
class Apple {
public:
	Apple();
	~Apple();
	void SetNewPosition(int x, int y);
	int GetAppleX();
	int GetAppleY();
private:
	int AppleX, AppleY;
};