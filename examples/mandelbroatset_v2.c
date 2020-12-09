//
// Created by Gabriel Mitterrutzner on 2019-02-18.
//

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#include "header/graphics_helper.h"
#include "header/window.h"

#define SCREEN_W 680
#define SCREEN_H 760
#define SCREEN_SCALE 1
#define SCREEN_NAME "Mandelbroat / Julia"

#define MAX_ITERATION_J 50
#define MAX_ITERATION_M 50

void julia(int** array) {
    int x_m, y_m;
    double half_scrn = (double)SCREEN_H * SCREEN_SCALE / 2;

    SDL_GetMouseState(&x_m, &y_m);
    double x_mouse = (double)x_m, y_mouse = (double)y_m;

    if (y_mouse > (half_scrn)) {
        y_mouse = half_scrn;
    }

    y_mouse = map_d(y_mouse, 0, half_scrn, -1, 1);
    x_mouse = map_d(x_mouse, 0, SCREEN_W * SCREEN_SCALE, -1, 1);

    double x_temp;
    int iteration;
    double x_new;
    double y_new;
    int color;

    for (int i = 150; i < SCREEN_W * SCREEN_SCALE + 150; ++i) {
        for (int j = (int)half_scrn; j < SCREEN_H * SCREEN_SCALE; ++j) {
            x_new = map_d(i, 0, SCREEN_W * SCREEN_SCALE, -2.5, 1);
            y_new = map_d(j, half_scrn, SCREEN_H * SCREEN_SCALE, -1, 1);

            iteration = 0;

            while (x_new * x_new + y_new * y_new <= 4 && iteration < MAX_ITERATION_J) {
                x_temp = x_new * x_new - y_new * y_new + x_mouse;
                y_new = 2 * x_new * y_new + y_mouse;
                x_new = x_temp;
                iteration++;
            }

            color = map(iteration, 0, MAX_ITERATION_J, 0, 255);
            *(*(array + i - 150) + j) = color;
        }
    }
}

void mandelbroat(int** array) {
    double x;
    double y;
    double x_temp;
    int iteration;
    double x_new;
    double y_new;
    int color;
    double half_scrn = (double)SCREEN_H * SCREEN_SCALE / 2;

    for (int i = 0; i < SCREEN_W * SCREEN_SCALE; ++i) {
        for (int j = 0; j < half_scrn; ++j) {
            x_new = map_d(i, 0, SCREEN_W * SCREEN_SCALE, -2.5, 1);
            y_new = map_d(j, 0, half_scrn, -1, 1);

            x = 0.0;
            y = 0.0;
            iteration = 0;

            while (x * x + y * y <= 2 * 2 && iteration < MAX_ITERATION_M) {
                x_temp = x * x - y * y + x_new;
                y = 2 * x * y + y_new;
                x = x_temp;
                iteration++;
            }

            color = map(iteration, 0, MAX_ITERATION_M, 0, 255);
            *(*(array + i) + j) = color;
        }
    }
}

void* check_event(graphic_window_t* window, void* nothing) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            window->running = SDL_FALSE;
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case 'q':
                    window->running = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }
    return nothing;
}

void free_object(int** array) {
    for (int i = 0; i < SCREEN_W * SCREEN_SCALE; ++i) {
        free(*(array + i));
    }
    free(array);
}

void print(graphic_window_t* window, int** array) {
    for (int i = 0; i < SCREEN_W * SCREEN_SCALE; ++i) {
        for (int j = 0; j < SCREEN_H * SCREEN_SCALE; ++j) {
            set_color_hsv(window->screen.renderer, *(*(array + i) + j));
            SDL_RenderDrawPoint(window->screen.renderer, i, j);
        }
    }
}

void draw(graphic_window_t* window, void* pixelarray) {
    julia((int**)pixelarray);
    print(window, (int**)pixelarray);
}

int main(void) {
    graphic_window_t* window = create_window(SCREEN_H, SCREEN_W, SCREEN_SCALE, SCREEN_NAME);

    int** pixelarray = malloc(sizeof(int*) * SCREEN_W * SCREEN_SCALE);
    for (int i = 0; i < SCREEN_W * SCREEN_SCALE; ++i) {
        *(pixelarray + i) = malloc(sizeof(int) * SCREEN_H * SCREEN_SCALE);
    }

    window_init(window);

    mandelbroat(pixelarray);

    draw_loop(window, 16, draw, pixelarray, check_event, NULL, NULL);

    free_object(pixelarray);
    window_quit(window);

    return EXIT_SUCCESS;
}
