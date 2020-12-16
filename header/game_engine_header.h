//
// Created by Gabriel Mitterrutzner on 2020-12-14.
//


#ifndef GAME_ENGINE_HEADER_H
#define GAME_ENGINE_HEADER_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#elif defined(_WIN32) || defined(WIN32)
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#endif

#include "game_engine_core.h"
#include "graphics_helper.h"
#include "text_field.h"
#include "texture.h"
#include "window.h"

#endif    // GAME_ENGINE_HEADER_H
