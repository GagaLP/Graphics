//
// Created by Gabriel Mitterrutzner on 2020-12-09.
//

#include <stdbool.h>
#include <stdlib.h>

#include "../header/game_engine_header.h"

#define SCREEN_W 500
#define SCREEN_H 500
#define SCREEN_SCALE 1
#define SCREEN_NAME "Tic Tac Toe"

int tic_tac_toe[9] = {0};

int update_fild(int position) {
    static int tic = 1;
    if (tic_tac_toe[position] == 0) {
        tic_tac_toe[position] = tic;
        tic *= -1;
    }
    return tic;
}

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
                case '1':
                    update_fild(0);
                    break;
                case '2':
                    update_fild(1);
                    break;
                case '3':
                    update_fild(2);
                    break;
                case '4':
                    update_fild(3);
                    break;
                case '5':
                    update_fild(4);
                    break;
                case '6':
                    update_fild(5);
                    break;
                case '7':
                    update_fild(6);
                    break;
                case '8':
                    update_fild(7);
                    break;
                case '9':
                    update_fild(8);
                    break;
                default:
                    break;
            }
        }
    }
    return nothing;
}

void draw_field(graphic_window_t* window, SDL_Point* test) {
    for (int i = 0; i < 8; i += 2) {
        draw_line(window, test[i], test[i + 1]);
    }

    for (int i = 0; i < 9; i++) {
        if (tic_tac_toe[i] == 1) {
            int x = i % 3;
            int y = i / 3;

            SDL_Point point_one = {SCREEN_W / 3 * (x + 1) - 10, SCREEN_H / 3 * (y + 1) - 10};
            SDL_Point point_two = {10 + SCREEN_W / 3 * x, 10 + SCREEN_H / 3 * y};

            SDL_Point point_three = {SCREEN_W / 3 * (x + 1) - 10, 10 + SCREEN_H / 3 * y};
            SDL_Point point_four = {10 + SCREEN_W / 3 * x, SCREEN_H / 3 * (y + 1) - 10};

            draw_line(window, point_one, point_two);
            draw_line(window, point_three, point_four);
        } else if (tic_tac_toe[i] == -1) {
            int half_x = SCREEN_W / 3 / 2;
            int half_y = SCREEN_H / 3 / 2;

            int x = i % 3;
            int y = i / 3;

            SDL_Point center = {half_x + SCREEN_W / 3 * x, half_y + SCREEN_H / 3 * y};

            draw_circle(window, center, half_x - 10);
        }
    }
}

SDL_Point* get_circle_points(void) {
    SDL_Point* test = malloc(sizeof(SDL_Point) * 8);

    test[0].x = SCREEN_W / 3;
    test[0].y = 10;
    test[1].x = SCREEN_W / 3;
    test[1].y = SCREEN_H - 10;
    test[2].x = SCREEN_W / 3 * 2;
    test[2].y = 10;
    test[3].x = SCREEN_W / 3 * 2;
    test[3].y = SCREEN_H - 10;
    test[4].x = 10;
    test[4].y = SCREEN_H / 3;
    test[5].x = SCREEN_W - 10;
    test[5].y = SCREEN_H / 3;
    test[6].x = 10;
    test[6].y = SCREEN_H / 3 * 2;
    test[7].x = SCREEN_W - 10;
    test[7].y = SCREEN_H / 3 * 2;

    return test;
}

void free_data(SDL_Point* points) {
    free(points);
}

bool check_winner(void) {
    bool return_val = false;
    if ((tic_tac_toe[0] == tic_tac_toe[4] && tic_tac_toe[0] == tic_tac_toe[8] && tic_tac_toe[0] != 0) ||    // check for diagonal
        (tic_tac_toe[2] == tic_tac_toe[4] && tic_tac_toe[2] == tic_tac_toe[6] && tic_tac_toe[2] != 0)) {    // check for diagonal
        return_val = true;
    } else {
        for (int i = 0; i < 3; i++) {
            if ((tic_tac_toe[i] == tic_tac_toe[i + 3] && tic_tac_toe[i] == tic_tac_toe[i + 6] && tic_tac_toe[i] != 0) ||                        // check horizontal
                (tic_tac_toe[i * 3] == tic_tac_toe[i * 3 + 1] && tic_tac_toe[i * 3] == tic_tac_toe[i * 3 + 2] && tic_tac_toe[i * 3] != 0)) {    // check for vertical
                return_val = true;
            }
        }
    }

    return return_val;
}

void reset_field(void) {
    for (int i = 0; i < 9; i++) {
        tic_tac_toe[i] = 0;
    }
}

void draw(graphic_window_t* window, void* point) {
    set_color_rgb(window, 255, 255, 255);

    if (check_winner()) {
        reset_field();
    }

    draw_field(window, point);
}

int main(void) {
    SDL_Point* point = get_circle_points();

    graphic_window_t* window = window_init(SCREEN_W, SCREEN_H, SCREEN_SCALE, SCREEN_NAME);
    draw_loop(window, 16, draw, point, check_event, NULL, NULL);
    window_quit(window);

    free_data(point);
    return EXIT_SUCCESS;
}
