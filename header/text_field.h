//
// Created by Gabriel Mitterrutzner on 2020-12-14.
//

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#elif defined(_WIN32) || defined(WIN32)
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#endif

#include <string.h>
#include <stdbool.h>

#include "texture.h"

typedef struct {
    SDL_Color color;            // color
    bool show;                  // visible
    texture_t* texture;         // The created textures
} textures_t;

typedef struct {
    TTF_Font* font;             // The font of the window

    int max_textures;           // number of textures
    int texture_count;          // number of textures

    textures_t* textures;
} text_fields_t;

text_fields_t* texts_init(char* font_name, int font_size);
void add_text(graphic_window_t* window, text_fields_t* text_fields, char* text, SDL_Color color, int x, int y);
void show_texts(graphic_window_t* window, text_fields_t* text_fields);
void change_text(graphic_window_t* window, text_fields_t* text_fields, char* text, int at);
void move_text(text_fields_t* text_fields, int at, int x, int y);
void change_visibility_text(text_fields_t* text_fields, int at, bool visibility);
void delete_text(text_fields_t* text_fields, int at);
void texts_quit(text_fields_t* text_fields);

#endif    // TEXT_FIELD_H
