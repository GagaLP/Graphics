//
// Created by Gabriel Mitterrutzner on 2019-02-12.
//

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdlib.h>
#include "header/window.h"
#include "header/graphics_helper.h"

#define SCREEN_W 640
#define SCREEN_H 380
#define SCREEN_SCALE 1
#define SCREEN_NAME "Fractal tree"

#define ANGLE 15
#define LENGTH_DEVIDE 1.125
#define FRACTAL_DEPTH 10
#define LINE_LENGTH 45

int angle = ANGLE;

SDL_Point create_point(int x, int y) {
    SDL_Point new_point = {x, y};
    return new_point;
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
                default :
                    break;
            }
        }
    }
    return nothing;
}

SDL_Point get_new_vector(double cur_angle, int length, SDL_Point start_point) {
    SDL_Point new_vect;

    if (cur_angle <= 90) {
        new_vect = create_point((int) (start_point.x - length * cos(deg_to_rad(cur_angle))),
                                (int) (start_point.y - length * sin(deg_to_rad(cur_angle))));
    } else if (cur_angle <= 180) {
        new_vect = create_point((int) (start_point.x + length * -cos(deg_to_rad(cur_angle))),
                                (int) (start_point.y - length * sin(deg_to_rad(cur_angle))));
    } else if (cur_angle + 90 <= 270) {
        new_vect = create_point((int) (start_point.x + length * -cos(deg_to_rad(cur_angle))),
                                (int) (start_point.y + length * -sin(deg_to_rad(cur_angle))));
    } else {
        new_vect = create_point((int) (start_point.x - length * cos(deg_to_rad(cur_angle))),
                                (int) (start_point.y + length * -sin(deg_to_rad(cur_angle))));
    }

    return new_vect;
}

void branch(graphic_window_t* window, SDL_Point start_point, int depth, double last_angle) {
    int color = map(depth, 0, FRACTAL_DEPTH, 0, 255);
    SDL_Point new_point = create_point(start_point.x, start_point.y - LINE_LENGTH);

    if (depth == 0) {
        set_color(window->screen.renderer, color);
        SDL_RenderDrawLine(window->screen.renderer, start_point.x, start_point.y, start_point.x,
                           start_point.y - LINE_LENGTH);
        branch(window, new_point, depth + 1, last_angle);
    } else if (depth < FRACTAL_DEPTH) {
        int length = LINE_LENGTH;
        double cur_angle_plus = last_angle + angle;
        double cur_angle_minus = last_angle - angle;

        if (pow(LENGTH_DEVIDE, depth) != 0) {
            length = (LINE_LENGTH / (int) pow(LENGTH_DEVIDE, depth));
        }

        SDL_Point left_vect = get_new_vector(cur_angle_plus, length, start_point);
        SDL_Point right_vect = get_new_vector(cur_angle_minus, length, start_point);

        set_color(window->screen.renderer, color);

        SDL_RenderDrawLine(window->screen.renderer, start_point.x, start_point.y, left_vect.x, left_vect.y);
        SDL_RenderDrawLine(window->screen.renderer, start_point.x, start_point.y, right_vect.x, right_vect.y);

        branch(window, left_vect, depth + 1, cur_angle_plus);
        branch(window, right_vect, depth + 1, cur_angle_minus);
    }
}

void caller(graphic_window_t* window, void* start_point){
    branch(window, *((SDL_Point*)start_point), 0, 90);
    //angle = (angle + 1);
}

int main(void) {
    graphic_window_t* window = create_window(SCREEN_H, SCREEN_W, SCREEN_SCALE, SCREEN_NAME);
    SDL_Point start_point = create_point(SCREEN_W / 2, SCREEN_H - 10);

    window_init(window);

    draw_loop(window, 16, caller, &start_point, check_event, NULL, NULL);

    window_quit(window);

    return EXIT_SUCCESS;
}
