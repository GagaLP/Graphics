//
// Created by Gabriel Mitterrutzner on 2020-12-10.
//

#include <stdbool.h>
#include <stdlib.h>

#include "../header/game_engine_header.h"

#define SCREEN_W 500
#define SCREEN_H 500
#define SCREEN_SCALE 1
#define SCREEN_NAME "Test Text"

text_fields_t* texts;

Uint64 now = 0;
Uint64 last = 0;
double delta_time = 0;

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

// just some tests
void draw(graphic_window_t* window, void* point) {
    static int times = 0;
    static bool delete = true;
    static int x = 0;
    static int y = 0;

    set_color_rgb(window, 255, 255, 255);

    print_text_window(window, texts);
    
    char buffer_value[50];
    last = now;
    now = SDL_GetPerformanceCounter();

    delta_time = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

    sprintf(buffer_value, "%.2lf", 1000.0 / delta_time);
    change_text_at(window, texts, buffer_value, delete ? 2 : 1);

    if (times > 100 && delete) {
        delete_text_at(texts, 0);
        delete = false;
    }

    move_text_at(texts, delete ? 3 : 2, x, y);

    static int i = 10;
    const int speed = 5;

    i = i > 0 && i + x < 500 ? +speed : -speed;
    i = i < 0 && i + x > 0 ? -speed : +speed;

    x += i;
    y += i;

    times++;
}


int main(void) {
    graphic_window_t* window = window_init(SCREEN_W, SCREEN_H, SCREEN_SCALE, SCREEN_NAME);
    texts = create_text("/System/Library/Fonts/Supplemental/Chalkduster.ttf", 24);
    add_text(window, texts, "hello manuel", (SDL_Color) {255, 255, 255}, 10, 10);
    add_text(window, texts, "FPS: ", (SDL_Color) {255, 255, 255}, 10, 40);
    add_text(window, texts, "0.00", (SDL_Color) {255, 255, 255}, 85, 40);
    add_text(window, texts, "DVD", (SDL_Color) {255, 255, 255}, 0, 0);

    now = SDL_GetPerformanceCounter();
    draw_loop(window, 15, draw, NULL, check_event, NULL, NULL);

    free_texture(texts);
    window_quit(window);
    return EXIT_SUCCESS;
}
