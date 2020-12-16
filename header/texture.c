//
// Created by Gabriel Mitterrutzner on 2020-12-15.
//

#include "texture.h"

texture_t* create_texture_from_surface(graphic_window_t* window, SDL_Surface* surface, int pos_x, int pos_y) {
    texture_t *my_texture = malloc(sizeof(texture_t));
    my_texture->texture = SDL_CreateTextureFromSurface(window->screen.renderer, surface);

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(my_texture->texture, NULL, NULL, &texW, &texH);
    my_texture->rect = (SDL_Rect) {pos_x, pos_y, texW, texH};

    return my_texture;
}

void put_texture_on_screen(graphic_window_t* window, texture_t* texture) {
    SDL_RenderCopy(window->screen.renderer, texture->texture, NULL, &(texture->rect));
}

void move_texture(texture_t* texture, int x, int y) {
    texture->rect.x = x;
    texture->rect.y = y;
}


void destroy_texture(texture_t* texture) {
    SDL_DestroyTexture(texture->texture);
    free(texture);
}
