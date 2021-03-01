#include "Snake.h"
Snake::Snake(){
	// set start position for snake
	BlockX = 350;
	BlockY = 250;
	BlockAngle = 0;
}
Snake::~Snake(){}

void Snake::SetSnakeBlockCord(int x, int y, int angle){
	BlockX = x;
	BlockY = y;
	BlockAngle = angle;
}

int Snake::GetSnakeBlockX() {
	return BlockX;
}

int Snake::GetSnakeBlockY() {
	return BlockY;
}
int Snake::GetSnakeAngle() {
	return BlockAngle;
}