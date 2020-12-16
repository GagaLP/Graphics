//
// Created by Gabriel Mitterrutzner on 2019-02-16.
//

#include <stdbool.h>
#include <stdlib.h>

#include "../header/game_engine_header.h"

#define SCREEN_W 500
#define SCREEN_H 500
#define SCREEN_SCALE 1
#define SCREEN_NAME "Heart"

#define SIZE 100

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

void draw_heart(graphic_window_t* window, SDL_Point* test, int size, int max) {
    if ((size / max) % 2) {
        for (int j = size % max + 1; j < max; ++j) {
            draw_line(window, test[j], test[(j + 1) % max]);
        }
    } else {
        for (int j = 0; j < size % max + 1; ++j) {
            draw_line(window, test[j], test[(j + 1) % max]);
        }
    }
}

SDL_Point* get_circle_points(int size) {
    SDL_Point* test = malloc(sizeof(SDL_Point) * size);
    double degree = (M_PI * 2) / (double)size;
    for (int i = 0; i < size; ++i) {
        test[i].x = (int)map_d(16 * pow(sin(degree * i), 3), -16, 16, 10, SCREEN_W - 10);
        test[i].y = (int)map_d(13 * cos(degree * i) - 5 * cos(2 * degree * i) - 2 * cos(3 * degree * i) - cos(4 * degree * i), -17, 12, SCREEN_H - 10, 10);
    }
    return test;
}

void free_data(SDL_Point* point) {
    free(point);
}

void draw(graphic_window_t* window, void* point) {
    static int num = 0;
    set_color_hsv(window, num % 330);
    draw_heart(window, (SDL_Point*)point, num, SIZE);
    num++;
}

int main(int argc, char* argv[]) {
    SDL_Point* point = get_circle_points(SIZE);

    graphic_window_t* window = window_init(SCREEN_W, SCREEN_H, SCREEN_SCALE, SCREEN_NAME);
    draw_loop(window, 16, draw, point, check_event, NULL, NULL);
    window_quit(window);

    free_data(point);
    return EXIT_SUCCESS;
}
