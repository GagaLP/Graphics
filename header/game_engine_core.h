//
// Created by Gabriel Mitterrutzner on 2019-02-16.
//

#ifndef GAME_ENGINE_CORE_H
#define GAME_ENGINE_CORE_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#elif defined(_WIN32) || defined(WIN32)
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#endif

#include <stdio.h>

void inti_game_engine(void) __attribute__ ((constructor));
void quit_game_engine(void) __attribute__ ((destructor));

#endif    // GAME_ENGINE_CORE_H
