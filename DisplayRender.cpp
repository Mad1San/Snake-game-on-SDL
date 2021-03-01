#include "DisplayRender.h"

DisplayRender::DisplayRender(SDL_Renderer* t_ren, SDL_Texture* t_texture) {
    ren = t_ren;
    texture = t_texture;
    font = TTF_OpenFont("somefont.ttf", 30);
}

DisplayRender::~DisplayRender() {}
DisplayRender::DisplayRender() {}

void DisplayRender::ShowBackgtound() {
    
    SDL_Rect Sprits[2];

    // BG sprite
    Sprits[0] = { 50, 50, 50, 50 };

    Sprits[1] = { 0, 100, 50, 50 };
    while (Sprits[0].x < 750) {

        while (Sprits[0].y < 550) {
            SDL_RenderCopy(ren, texture, &Sprits[1], &Sprits[0]);
            Sprits[0].y += 50;
        }
        Sprits[0].y = 50;
        Sprits[0].x += 50;
    }
    SDL_RenderPresent(ren);
}

void DisplayRender::ShowWall() {
    SDL_Rect Sprits[3];
    
    Sprits[0] = { 0, 0, 50, 50 };
    Sprits[2] = { 750, 550, 50, 50 };

    // Wall sprite
    Sprits[1] = { 50, 100, 50, 50 };

    while (Sprits[0].x < 800) {
        SDL_RenderCopy(ren, texture, &Sprits[1], &Sprits[0]);
        SDL_RenderCopy(ren, texture, &Sprits[1], &Sprits[2]);
        Sprits[0].x += 50;
        Sprits[2].x -= 50;
    }
    Sprits[0].x = 0;
    Sprits[2].x = 750;
    while (Sprits[0].y < 600) {
        SDL_RenderCopy(ren, texture, &Sprits[1], &Sprits[0]);
        SDL_RenderCopy(ren, texture, &Sprits[1], &Sprits[2]);
        Sprits[0].y += 50;
        Sprits[2].y -= 50;
    }

    SDL_RenderPresent(ren);
}


void DisplayRender::ShowRandowApple(Apple apple) {
    SDL_Rect Sprits[2];
    
    //apple sprite
    Sprits[0] = { 50, 0, 50, 50 };

    Sprits[1] = { apple.GetAppleX(), apple.GetAppleY(), 50, 50 };
    SDL_RenderCopy(ren, texture, &Sprits[0], &Sprits[1]);
    SDL_RenderPresent(ren);
}

void DisplayRender::ShowHead(std::list<Snake> snake) {
    SDL_Rect Sprits[5];

    // body sprite
    Sprits[0] = { 0,50,50,50 };

    // head sprite
    Sprits[3] = { 0,0,50,50 };
    
    // tail sprite
    Sprits[4] = { 50,50,50,50 };

    // BG sprite
    Sprits[2] = { 0,100,50,50 };

    int counter = 1, len;
    len = snake.size();
    for (auto block : snake) {
        int x, y;
        x = block.GetSnakeBlockX();
        y = block.GetSnakeBlockY();
        Sprits[1] = { x, y, 50, 50 }; 
        if (counter == 1) {
            SDL_RenderCopy(ren, texture, &Sprits[2], &Sprits[1]);
            counter = 2;
            continue;
        }

        // code for display tail, but he have bugs *idk how to fix this*  if you want to see this , just uncomment
        /*if (len > 2 && i == 2) {   
            SDL_RenderCopyEx(ren, texture, &Sprits[4], &Sprits[1], block.GetSnakeAngle(), 0, SDL_FLIP_HORIZONTAL);
            k = 3;
            i++;
            continue;
        }
        else {*/

        if (counter == len) { //head
            SDL_RenderCopyEx(ren, texture, &Sprits[3], &Sprits[1], block.GetSnakeAngle(), 0, SDL_FLIP_HORIZONTAL);
        }
        else { //body 
            SDL_RenderCopyEx(ren, texture, &Sprits[0], &Sprits[1], block.GetSnakeAngle(), 0, SDL_FLIP_HORIZONTAL);
        }
        counter++;

    }
    SDL_RenderPresent(ren);
}


void DisplayRender::ScoreText(int score) {
    SDL_Surface* tempTexture;
    int mWidth, mHeight;
    SDL_Color color = { 255, 255, 255 };
    SDL_Rect Rect[4];

    tempTexture = TTF_RenderText_Blended(font, std::to_string(score).c_str(), color);

    // width, height text
    mWidth = tempTexture->w;
    mHeight = tempTexture->h;

    // texture(text)
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(ren, tempTexture);

    // textsize
    Rect[0] = { 400 - mWidth/2, 0, mWidth, mHeight};
    Rect[1] = { 50, 100, 50, 50}; // BD sprite
    Rect[2] = { 350, 0, 50, 50};
    Rect[3] = { 400, 0, 50, 50};

    // clearTexture
    SDL_FreeSurface(tempTexture);

    //clear after score
    SDL_RenderCopy(ren, texture, &Rect[1], &Rect[2]);
    SDL_RenderCopy(ren, texture, &Rect[1], &Rect[3]);

    // write new score
    SDL_RenderCopy(ren, textureText, NULL, &Rect[0]);
    SDL_RenderPresent(ren);
}

void DisplayRender::GameOverText() {
    SDL_Surface* tempTexture;
    int mWidth, mHeight;
    SDL_Color color = { 255, 255, 255 };
    SDL_Rect Rect[1];


    TTF_Font* font = TTF_OpenFont("somefont.ttf", 50);
    tempTexture = TTF_RenderText_Blended(font, "Game Over", color);

    // width, height text
    mWidth = tempTexture->w;
    mHeight = tempTexture->h;

    // texture(text)
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(ren, tempTexture);

    // textsize
    Rect[0] = { 400-mWidth/2, 250-mHeight/2, mWidth , mHeight };

    // clear
    SDL_FreeSurface(tempTexture);

    // write text
    SDL_RenderCopy(ren, textureText, NULL, &Rect[0]);
    SDL_RenderPresent(ren);
}


void DisplayRender::BestScoreText(int score) {
    SDL_Surface* tempTexture;
    int mWidth, mHeight;
    SDL_Color color = { 255, 255, 255 };
    SDL_Rect Rect[1];

    //text
    std::string str = "Best score: ";
    str = str + std::to_string(score);

    tempTexture = TTF_RenderText_Blended(font, str.c_str(), color);

    // width, height text
    mWidth = tempTexture->w;
    mHeight = tempTexture->h;

    // texture(text)
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(ren, tempTexture);

    // textsize
    Rect[0] = { 400 - mWidth / 2, 300 - mHeight / 2, mWidth , mHeight };

    // clear
    SDL_FreeSurface(tempTexture);

    // write score
    SDL_RenderCopy(ren, textureText, NULL, &Rect[0]);
    SDL_RenderPresent(ren);
}


void DisplayRender::StartText() {
    SDL_Surface* tempTexture;
    int mWidth, mHeight;
    SDL_Color color = { 255, 255, 255 };
    SDL_Rect Rect[1];

    tempTexture = TTF_RenderText_Blended(font, "Press\n Up / Down / Right / Left\nto start", color);

    // width, height text
    mWidth = tempTexture->w;
    mHeight = tempTexture->h;

    // texture(text)
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(ren, tempTexture);

    // textsize
    Rect[0] = { 400 - mWidth / 2, 100 - mHeight / 2, mWidth , mHeight };

    // clear
    SDL_FreeSurface(tempTexture);

    // write start text
    SDL_RenderCopy(ren, textureText, NULL, &Rect[0]);
    SDL_RenderPresent(ren);
}

void DisplayRender::StartTextClear() {

    SDL_Rect Sprits[3];

    Sprits[0] = { 50, 50, 50, 50 }; 
    Sprits[2] = { 50, 100, 50, 50 };

    // BG sprite
    Sprits[1] = { 0, 100, 50, 50 };


    while (Sprits[0].x < 750) {
        SDL_RenderCopy(ren, texture, &Sprits[1], &Sprits[0]);
        SDL_RenderCopy(ren, texture, &Sprits[1], &Sprits[2]);
        Sprits[0].x += 50;
        Sprits[2].x += 50;
    }

    // clear text
    SDL_RenderPresent(ren);
}

void DisplayRender::Clear() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}