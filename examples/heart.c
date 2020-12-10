//
// Created by Gabriel Mitterrutzner on 2019-02-16.
//

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif defined(_WIN32) || defined(WIN32)
#include <SDL.h>
#include <SDL_main.h>
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "../header/graphics_helper.h"
#include "../header/window.h"

#define HEIGHT 500
#define WIDTH 500

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
        test[i].x = (int)map_d(16 * pow(sin(degree * i), 3), -16, 16, 10, WIDTH - 10);
        test[i].y = (int)map_d(13 * cos(degree * i) - 5 * cos(2 * degree * i) - 2 * cos(3 * degree * i) - cos(4 * degree * i), -17, 12, HEIGHT - 10, 10);
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
    graphic_window_t* window = create_window(WIDTH, HEIGHT, 1, "Heart");
    SDL_Point* point = get_circle_points(SIZE);

    window_init(window);

    draw_loop(window, 16, draw, point, check_event, NULL, NULL);

    free_data(point);
    window_quit(window);

    return EXIT_SUCCESS;
}
