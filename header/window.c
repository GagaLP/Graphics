//
// Created by Gabriel Mitterrutzner on 2019-02-16.
//

#include "window.h"

void window_init(graphic_window_t *window) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        printf("Error %s", SDL_GetError());
        exit(-1);
    }

    window->screen.window = SDL_CreateWindow(window->screen.name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             window->screen.w,
                                             window->screen.h, SDL_WINDOW_SHOWN);

    if (window->screen.window == NULL) {
        printf("Error %s", SDL_GetError());
        exit(-2);
    }

    window->screen.renderer = SDL_CreateRenderer(window->screen.window, -1, SDL_RENDERER_ACCELERATED);

    if (window->screen.renderer == NULL) {
        printf("Error %s", SDL_GetError());
        SDL_DestroyWindow(window->screen.window);
        exit(-3);
    }

    window->running = SDL_TRUE;
}

void window_quit(graphic_window_t *window) {
    SDL_DestroyRenderer(window->screen.renderer);
    SDL_DestroyWindow(window->screen.window);

    window->screen.renderer = NULL;
    window->screen.window = NULL;

    free(window);
    SDL_Quit();
}

graphic_window_t *create_window(unsigned int height, unsigned int width, double scale, char *name) {
    graphic_window_t *window = malloc(sizeof(graphic_window_t));
    window->screen.w = (unsigned int)(width * scale);
    window->screen.h = (unsigned int)(height * scale);
    window->screen.name = name;
    return window;
}

void draw_loop(graphic_window_t *window, uint32_t delay, void (*draw_func)(graphic_window_t *, void *), void *arg_draw, void *(*check_event)(graphic_window_t *, void *), void *return_val_event, void *arg_event) {
    while (window->running) {
        if (return_val_event != NULL) {
            return_val_event = check_event(window, arg_event);
        } else {
            check_event(window, arg_event);
        }

        SDL_RenderClear(window->screen.renderer);

        draw_func(window, arg_draw);

        SDL_SetRenderDrawColor(window->screen.renderer, 0, 0, 0, 255);
        SDL_RenderPresent(window->screen.renderer);
        SDL_Delay(delay);
    }
}

void window_set_running(graphic_window_t *window, SDL_bool running) {
    window->running = running;
}
