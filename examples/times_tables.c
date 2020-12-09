//
// Created by Gabriel Mitterrutzner on 2019-02-15.
//

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#include "header/graphics_helper.h"
#include "header/window.h"

#define SCREEN_W 500
#define SCREEN_H 500
#define SCREEN_SCALE 1
#define SCREEN_NAME "Times Table"

#define SIZE 1000

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

void draw_times_table(graphic_window_t* window, SDL_Point* test, int size, double times) {
    for (int j = 0; j < size; ++j) {
        SDL_RenderDrawLine(window->screen.renderer, test[j].x, test[j].y, test[(int)(j * times) % size].x, test[(int)(j * times) % size].y);
    }
}

SDL_Point* get_circle_points(int size) {
    SDL_Point* test = malloc(sizeof(SDL_Point) * size);
    double degree = (M_PI * 2) / (double)size;
    for (int i = 0; i < size; ++i) {
        test[i].x = (int)map_d(cos(degree * i), -1, 1, 10, SCREEN_W * SCREEN_SCALE - 10);
        test[i].y = (int)map_d(sin(degree * i), -1, 1, 10, SCREEN_H * SCREEN_SCALE - 10);
    }
    return test;
}

void free_data(SDL_Point* points) {
    free(points);
}

void draw(graphic_window_t* window, void* point) {
    static double num = 0;
    set_color_hsv(window->screen.renderer, (int)map_d(mod_d(num, 3), 0, 2.5, 255, 0));
    draw_times_table(window, point, SIZE, num);
    if (num < 100) {
        num = (num + 0.01);
    } else {
        num = mod_d(num, 100);
    }
}

int main(void) {
    graphic_window_t* window = create_window(SCREEN_W, SCREEN_H, SCREEN_SCALE, "Heart");
    window_init(window);

    SDL_Point* point = get_circle_points(SIZE);

    draw_loop(window, 16, draw, point, check_event, NULL, NULL);

    free_data(point);
    window_quit(window);

    return EXIT_SUCCESS;
}