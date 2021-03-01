#pragma once
#include "DisplayRender.h"
#include "SnakeManager.h"
#include "AppleManager.h"


class GameManager
{
public:
	GameManager(SDL_Renderer* t_ren, SDL_Texture* t_texture);
	~GameManager();
	bool CreateGame();
	int WriteBestScore(int score);
private:
	bool gameOver;
	int wayX, wayY, wayAngle, BestScore;
	DisplayRender disp; 
	AppleManager apple;
};