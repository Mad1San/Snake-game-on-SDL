#pragma once
#include<list>
#include"Snake.h"
class SnakeManeger
{
public:
	SnakeManeger(Snake block);
	~SnakeManeger();
	void AddBlockSnake(Snake block);
	void RemoveBlockSnake();
	std::list<Snake> GetSnakeList();
private:
	std::list<Snake> snake;
};