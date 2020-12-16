//
// Created by Gabriel Mitterrutzner on 2020-12-14.
//

#include "text_field.h"

#define STRING_STEPS 8

text_fields_t* create_text(char* font_name, int font_size) {
    text_fields_t* text_fields = malloc(sizeof(text_fields_t));

    text_fields->font = TTF_OpenFont(font_name, font_size);
    text_fields->max_textures = STRING_STEPS;
    text_fields->texture_count = 0;

    text_fields->textures = malloc(text_fields->max_textures * sizeof(texture_t*));

    return text_fields;
}

void add_text(graphic_window_t* window, text_fields_t* text_fields, char* text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(text_fields->font, text, color);

    if (text_fields->texture_count == text_fields->max_textures) {
        text_fields->max_textures += STRING_STEPS;
        text_fields->textures = realloc(text_fields->textures, text_fields->max_textures * sizeof(texture_t*));
    }

    text_fields->textures[text_fields->texture_count] = create_texture_from_surface(window, surface, x, y);
    text_fields->texture_count++;

    SDL_FreeSurface(surface);
}

void print_text_window(graphic_window_t* window, text_fields_t* text_fields) {
    for (int i = 0; i < text_fields->texture_count; i++) {
        put_texture_on_screen(window, text_fields->textures[i]);
    }
}

void change_text_at(graphic_window_t* window, text_fields_t* text_fields, char* text, int at) {
    if (text_fields->texture_count > at) {
        SDL_Surface* surface = TTF_RenderText_Solid(text_fields->font, text, (SDL_Color) {255, 255, 255});
        int x = text_fields->textures[at]->rect.x;
        int y = text_fields->textures[at]->rect.y;

        destroy_texture(text_fields->textures[at]);

        text_fields->textures[at] = create_texture_from_surface(window, surface, x, y);

        SDL_FreeSurface(surface);
    }
}

void move_text_at(text_fields_t* text_fields, int at, int x, int y) {
    if (text_fields->texture_count > at) {
        move_texture(text_fields->textures[at], x, y);
    }
}

void delete_text_at(text_fields_t* text_fields, int at) {
    if (text_fields->texture_count > at) {
        texture_t* texture_free = text_fields->textures[at];

        for(int i = at; i < text_fields->texture_count - 1; i++) {
            text_fields->textures[i] = text_fields->textures[i + 1];
        }

        destroy_texture(texture_free);

        text_fields->texture_count--;
    }
}

void free_texture(text_fields_t* text_fields) {
    TTF_CloseFont(text_fields->font);

    for (int i = 0; i < text_fields->texture_count; i++) {
        destroy_texture(text_fields->textures[i]);
    }

    free(text_fields->textures);
    free(text_fields);
}
