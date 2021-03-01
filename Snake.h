#pragma once
#include <iostream>
class Snake
{
public:
	Snake();
	~Snake();
	void SetSnakeBlockCord(int x, int y, int angle);
	int GetSnakeBlockX();
	int GetSnakeBlockY();
	int GetSnakeAngle();
private:
	int BlockX, BlockY, BlockAngle;
	
};