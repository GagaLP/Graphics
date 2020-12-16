//
// Created by Gabriel Mitterrutzner on 2020-12-15.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif defined(_WIN32) || defined(WIN32)
#include <SDL.h>
#include <SDL_main.h>
#endif

#include <stdio.h>
#include "window.h"

typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
} texture_t;

texture_t* create_texture_from_surface(graphic_window_t* window, SDL_Surface* surface, int pos_x, int pos_y);
void put_texture_on_screen(graphic_window_t* window, texture_t* texture);
void move_texture(texture_t* texture, int x, int y);
void destroy_texture(texture_t* texture);

#endif    // WINDOW_H
