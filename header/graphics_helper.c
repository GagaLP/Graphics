//
// Created by Gabriel Mitterrutzner on 2019-02-17.
//

#include "graphics_helper.h"

//math
double deg_to_rad(double angle) {
    return angle * (M_PI / 180);
}

double map_d(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double mod_d(double num, double mod) {
    return num - (mod * (int)(num / mod));
}

// color
void hsv_to_rgb(float *r, float *g, float *b, float h, float s, float v) {
    int i;
    float f, p, q, t;
    if (s == 0) {
        *r = *g = *b = v;
        return;
    }
    h /= 60;
    i = (int)floorf(h);
    f = h - i;
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));
    switch (i) {
        case 0:
            *r = v * 255;
            *g = t * 255;
            *b = p * 255;
            break;
        case 1:
            *r = q * 255;
            *g = v * 255;
            *b = p * 255;
            break;
        case 2:
            *r = p * 255;
            *g = v * 255;
            *b = t * 255;
            break;
        case 3:
            *r = p * 255;
            *g = q * 255;
            *b = v * 255;
            break;
        case 4:
            *r = t * 255;
            *g = p * 255;
            *b = v * 255;
            break;
        default:
            *r = v * 255;
            *g = p * 255;
            *b = q * 255;
            break;
    }
}

void set_color_hsv(graphic_window_t *window, int color) {
    float r, g, b;
    hsv_to_rgb(&r, &g, &b, color, 1, 1);
    SDL_SetRenderDrawColor(window->screen.renderer, (uint8_t)floorf(r), (uint8_t)floorf(g), (uint8_t)floorf(b), 255);
}

void set_color_rgb(graphic_window_t *window, uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetRenderDrawColor(window->screen.renderer, r, g, b, 255);
}

void draw_circle(graphic_window_t *window, SDL_Point center, int r) {
    SDL_Renderer *renderer = window->screen.renderer;
    int xc = center.x;
    int yc = center.y;
    int x = r, y = 0;

    SDL_RenderDrawPoint(renderer, xc, yc + x);

    if (r != 0) {
        SDL_RenderDrawPoint(renderer, xc, yc - x);
        SDL_RenderDrawPoint(renderer, xc + x, yc);
        SDL_RenderDrawPoint(renderer, xc - x, yc);
    }

    int p = 1 - r;
    while (x > y) {
        y++;

        if (p <= 0) {
            p = p + 2 * y + 1;
        } else {
            x--;
            p = p + 2 * y - 2 * x + 1;
        }

        if (x < y) {
            break;
        }

        SDL_RenderDrawPoint(renderer, xc + x, yc + y);
        SDL_RenderDrawPoint(renderer, xc - x, yc + y);
        SDL_RenderDrawPoint(renderer, xc + x, yc - y);
        SDL_RenderDrawPoint(renderer, xc - x, yc - y);

        if (x != y) {
            SDL_RenderDrawPoint(renderer, xc + y, yc + x);
            SDL_RenderDrawPoint(renderer, xc - y, yc + x);
            SDL_RenderDrawPoint(renderer, xc + y, yc - x);
            SDL_RenderDrawPoint(renderer, xc - y, yc - x);
        }
    }
}

void draw_line(graphic_window_t *window, SDL_Point point_one, SDL_Point point_two) {
    SDL_RenderDrawLine(window->screen.renderer, point_one.x, point_one.y, point_two.x, point_two.y);
}

void draw_point(graphic_window_t *window, SDL_Point point) {
    SDL_RenderDrawPoint(window->screen.renderer, point.x, point.y);
}

void draw_rect(graphic_window_t *window, SDL_Rect rect, bool filled) {
    if (filled) {
        SDL_RenderFillRect(window->screen.renderer, &rect);
    } else {
        SDL_RenderDrawRect(window->screen.renderer, &rect);
    }
}

