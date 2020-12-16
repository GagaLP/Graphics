//
// Created by Gabriel Mitterrutzner on 2019-02-16.
//

#include "game_engine_core.h"

void inti_game_engine(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        printf("Error %s", SDL_GetError());
        exit(-1);
    }

    TTF_Init();
}

void quit_game_engine(void) {
    TTF_Quit();
    SDL_Quit();
}

