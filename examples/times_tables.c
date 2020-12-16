//
// Created by Gabriel Mitterrutzner on 2019-02-15.
//

#include <stdbool.h>
#include <stdlib.h>

#include "../header/game_engine_header.h"

#define SCREEN_W 500
#define SCREEN_H 500
#define SCREEN_SCALE 1
#define SCREEN_NAME "Times Table"

#define SIZE 1000

void* check_event(graphic_window_t* window, void* nothing) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            window_set_running(window, SDL_FALSE);
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case 'q':
                    window_set_running(window, SDL_FALSE);
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
        draw_line(window, test[j], test[(int)(j * times) % size]);
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
    set_color_hsv(window, (int)map_d(mod_d(num, 3), 0, 2.5, 255, 0));
    draw_times_table(window, point, SIZE, num);
    if (num < 100) {
        num = (num + 0.01);
    } else {
        num = mod_d(num, 100);
    }
}

int main(int argc, char* argv[]) {
    SDL_Point* point = get_circle_points(SIZE);

    graphic_window_t* window = window_init(SCREEN_W, SCREEN_H, SCREEN_SCALE, SCREEN_NAME);
    draw_loop(window, 16, draw, point, check_event, NULL, NULL);
    window_quit(window);

    free_data(point);
    return EXIT_SUCCESS;
}
