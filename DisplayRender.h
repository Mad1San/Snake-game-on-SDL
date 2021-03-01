#pragma once
#include<SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include<string>
#include <list>
#include "Snake.h"
#include "Apple.h"

class DisplayRender
{
public:
	DisplayRender(SDL_Renderer* t_ren, SDL_Texture* t_texture);
	DisplayRender();
	~DisplayRender();

	void ShowBackgtound();
	void ShowRandowApple(Apple apple);
	void ShowWall();
	void ShowHead(std::list<Snake> snake);
	void ScoreText(int score);
	void GameOverText();
	void BestScoreText(int score);
	void StartText();
	void StartTextClear();
	void Clear();
private:
	SDL_Texture* texture;
	SDL_Renderer* ren;
	TTF_Font* font;
};