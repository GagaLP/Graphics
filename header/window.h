//
// Created by Gabriel Mitterrutzner on 2019-02-16.
//

#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif defined(_WIN32) || defined(WIN32)
#include <SDL.h>
#include <SDL_main.h>
#endif

typedef struct {
    SDL_bool running;
    struct {
        unsigned int w;
        unsigned int h;
        const char *name;
        SDL_Window *window;
        SDL_Renderer *renderer;
    } screen;
} graphic_window_t;

graphic_window_t *create_window(unsigned int height, unsigned int width, double scale, char *name);
void draw_loop(graphic_window_t *window, uint32_t delay, void (*draw_func)(graphic_window_t *, void *), void *arg_draw, void *(*check_event)(graphic_window_t *, void *), void *return_val_event, void *arg_event);
void window_init(graphic_window_t *window);
void window_quit(graphic_window_t *window);

#endif    //GRAPHICS_WINDOW_H
