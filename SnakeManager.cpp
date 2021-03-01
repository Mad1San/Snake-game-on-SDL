#include "SnakeManager.h"
SnakeManeger:: SnakeManeger(Snake block) {
	snake.push_back(block);
}

SnakeManeger::~SnakeManeger(){}

void SnakeManeger::AddBlockSnake(Snake block) {
	snake.push_back(block);
}


void SnakeManeger::RemoveBlockSnake() {
	snake.pop_front();
}

std::list<Snake> SnakeManeger::GetSnakeList() {
	return snake;
}
