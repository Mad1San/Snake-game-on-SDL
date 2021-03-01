#include "GameManager.h"

GameManager::GameManager(SDL_Renderer* t_ren, SDL_Texture* t_texture) {
	wayX = 0;
	wayY = 0;
    wayAngle = 0;
    gameOver = false;
    disp = DisplayRender(t_ren,t_texture);

    
}
GameManager::~GameManager() {}

int GameManager::WriteBestScore(int score) {
    SDL_RWops* file = NULL;
    int BestScore;
    file = SDL_RWFromFile("BestScore.bin", "r+b");
    if (file != NULL) { // open file and read
        SDL_RWread(file, &BestScore, sizeof(BestScore), 1);
        SDL_RWclose(file);
    }
    else {
        BestScore = score;
    }
    if (score >= BestScore) { // write better score
        BestScore = score;
        file = SDL_RWFromFile("BestScore.bin", "w+b");
        SDL_RWwrite(file, &score, sizeof(score), 1);
        SDL_RWclose(file);
    }
    return BestScore;
}


bool GameManager::CreateGame () {
    SDL_Event event;
    int appleTemp = 1, key = 0, score = 0, press = 0;
    SnakeManeger snake = SnakeManeger(Snake());
    Snake block;

    // render textures
    disp.ShowBackgtound();
    disp.ShowWall();
    disp.ScoreText(score);
    disp.StartText();

    // start game
    while (gameOver != true)
    {
        // user press some key
        while(SDL_PollEvent(&event) != NULL) {

            if (event.type == SDL_QUIT) {
                return false;
            }
           
            // set new way 
            switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                if (key == SDLK_LEFT) break;
                wayX = 1;
                wayY = 0;
                wayAngle = 90;
                key = SDLK_RIGHT;
                break;
            case SDLK_LEFT:
                if (key == SDLK_RIGHT) break;
                wayX = -1;
                wayY = 0;
                wayAngle = 270;
                key = SDLK_LEFT;
                break;
            case SDLK_UP:
                if (key == SDLK_DOWN) break;
                wayY = -1;
                wayX = 0;
                wayAngle = 0;
                key = SDLK_UP;
                break;
            case SDLK_DOWN:
                if (key == SDLK_UP) break;
                wayY = 1;
                wayX = 0;
                wayAngle = 180;
                key = SDLK_DOWN;
                break;
            }
        }

        // clear start text before press key
        if (press == 0 && key != 0) {
            disp.StartTextClear();
            press = 1;
        }
        
        // set new cord
        block.SetSnakeBlockCord(block.GetSnakeBlockX() + wayX * 50, block.GetSnakeBlockY() + wayY * 50, wayAngle);
        
        // outside the playing field
        if (block.GetSnakeBlockX() < 50 || block.GetSnakeBlockX() >= 750 || block.GetSnakeBlockY() < 50 || block.GetSnakeBlockY() >= 550) {
            gameOver = true;
            break;
        }

        // snake bite snake
        for (auto bite : snake.GetSnakeList()) {
            if (block.GetSnakeBlockX() == bite.GetSnakeBlockX() && block.GetSnakeBlockY() == bite.GetSnakeBlockY() && score > 1) {
                gameOver = true;
                break;
            }
        }

        // add new snake block
        snake.AddBlockSnake(block);

        // create new apple
        if (appleTemp == 1) {
            apple.CreateNewApple(snake.GetSnakeList());
            disp.ShowRandowApple(apple.GetApple());
            appleTemp = 0;
        }

        // snake eat apple
        if (block.GetSnakeBlockX() == apple.GetApple().GetAppleX() && block.GetSnakeBlockY() == apple.GetApple().GetAppleY()) {
            snake.AddBlockSnake(block);
            score++;
            disp.ScoreText(score);
            appleTemp = 1;
        }

        // display snake
        disp.ShowHead(snake.GetSnakeList());

        // delete last snake block
        snake.RemoveBlockSnake();

        // wait some time
        SDL_Delay(180);
    }
    // game over
    disp.GameOverText();

    // write score in file
    disp.BestScoreText(WriteBestScore(score));

    // clear texture, close font
    disp.Clear();

    // wait some time again
    SDL_Delay(2000);

	return false;
}