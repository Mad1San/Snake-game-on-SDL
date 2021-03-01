#include"AppleManager.h"

AppleManager::AppleManager(){}
AppleManager::~AppleManager(){}

void AppleManager::CreateNewApple(std::list<Snake> snake) {
	while (true)
	{
		int counter = 0;
		apple.SetNewPosition(std::rand() % 14 * 50 + 50, std::rand() % 10 * 50 + 50);
		for (auto block : snake) {
			// find matches with the snake
			if (block.GetSnakeBlockX() == apple.GetAppleX() && block.GetSnakeBlockY() == apple.GetAppleY()) {
				counter++;
			}
		}
		if(counter == 0){
			break;
		}
	}
}
Apple AppleManager::GetApple() {
	return apple;
}