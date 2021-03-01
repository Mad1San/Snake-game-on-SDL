#include"Apple.h"
Apple::Apple(){
	// set random cord for first apple
	AppleX = std::rand() % 14 * 50 + 50;
	AppleY = std::rand() % 10 * 50 + 50;
}
Apple::~Apple() {}

void Apple::SetNewPosition(int x, int y) {
	AppleX = x;
	AppleY = y;
}

int Apple::GetAppleX() {
	return AppleX;
}

int Apple::GetAppleY() {
	return AppleY;
}