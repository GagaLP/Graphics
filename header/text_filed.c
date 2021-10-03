//
// Created by Gabriel Mitterrutzner on 2020-12-14.
//

#include "text_field.h"

#define STRING_STEPS 8

text_fields_t* texts_init(char* font_name, int font_size) {
    text_fields_t* text_fields = malloc(sizeof(text_fields_t));

    text_fields->font = TTF_OpenFont(font_name, font_size);
    text_fields->max_textures = STRING_STEPS;
    text_fields->texture_count = 0;

    text_fields->textures = malloc(text_fields->max_textures * sizeof(textures_t));

    return text_fields;
}

void add_text(graphic_window_t* window, text_fields_t* text_fields, char* text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(text_fields->font, text, color);

    if (text_fields->texture_count == text_fields->max_textures) {
        text_fields->max_textures += STRING_STEPS;
        text_fields->textures = realloc(text_fields->textures, text_fields->max_textures * sizeof(textures_t));
    }

    text_fields->textures[text_fields->texture_count].color = color;
    text_fields->textures[text_fields->texture_count].show = false;
    text_fields->textures[text_fields->texture_count].texture = create_texture_from_surface(window, surface, x, y);
    text_fields->texture_count++;

    SDL_FreeSurface(surface);
}

void show_texts(graphic_window_t* window, text_fields_t* text_fields) {
    for (int i = 0; i < text_fields->texture_count; i++) {
        if (text_fields->textures[i].show) {
            put_texture_on_screen(window, text_fields->textures[i].texture);
        }
    }
}

void change_text(graphic_window_t* window, text_fields_t* text_fields, char* text, int at) {
    if (text_fields->texture_count > at) {
        // save tings before they get overwritten
        SDL_Color color = text_fields->textures[at].color;
        // bool visibility = text_fields->textures[at].show;
        int x = text_fields->textures[at].texture->rect.x;
        int y = text_fields->textures[at].texture->rect.y;

        SDL_Surface* surface = TTF_RenderText_Solid(text_fields->font, text, color);

        destroy_texture(text_fields->textures[at].texture);

        text_fields->textures[at].texture = create_texture_from_surface(window, surface, x, y);

        SDL_FreeSurface(surface);
    }
}

void change_visibility_text(text_fields_t* text_fields, int at, bool visibility) {
    if (text_fields->texture_count > at) {
        text_fields->textures[at].show = visibility;
    }
}

void move_text(text_fields_t* text_fields, int at, int x, int y) {
    if (text_fields->texture_count > at) {
        move_texture(text_fields->textures[at].texture, x, y);
    }
}

void delete_text(text_fields_t* text_fields, int at) {
    if (text_fields->texture_count > at) {
        texture_t* texture_free = text_fields->textures[at].texture;

        for(int i = at; i < text_fields->texture_count - 1; i++) {
            text_fields->textures[i].texture = text_fields->textures[i + 1].texture;
            text_fields->textures[i].color = text_fields->textures[i + 1].color;
            text_fields->textures[i].show = text_fields->textures[i + 1].show;
        }

        destroy_texture(texture_free);

        text_fields->texture_count--;
    }
}

void texts_quit(text_fields_t* text_fields) {
    TTF_CloseFont(text_fields->font);

    for (int i = 0; i < text_fields->texture_count; i++) {
        destroy_texture(text_fields->textures[i].texture);
    }

    free(text_fields->textures);
    free(text_fields);
}
