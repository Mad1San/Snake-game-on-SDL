#include "GameManager.h"
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Renderer* ren = NULL;
SDL_Window* window = NULL;

int init() {

    //sdl 
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << SDL_GetError() << endl;
        return 1;
    }

    //text
    if (TTF_Init() != 0) {
        cout << SDL_GetError() << endl;
        return 1;
    }


    //img
    if (IMG_Init(IMG_INIT_PNG) == NULL) {
        cout << SDL_GetError() << endl;
        return 1;
    }


    //window
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << SDL_GetError() << endl;
        return 1;
    }

    //render
    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return 0;
}

SDL_Texture* loadTexturs() {
    // load texture for game
    SDL_Surface* tempTexture;
    tempTexture = IMG_Load("textursV2.png");
    SDL_Texture* texturs = NULL;

    if (tempTexture != NULL) {
        texturs = SDL_CreateTextureFromSurface(ren, tempTexture);
        SDL_FreeSurface(tempTexture);
    }

    return texturs;
}

int quit() {

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int main(int argc, char** args) {

    if (init() == 1) {
        return 1;
    }

    if (loadTexturs() == NULL) {
        return 1;
    }

    GameManager game = GameManager(ren, loadTexturs());

    // start game
    game.CreateGame();

    return quit();
}
