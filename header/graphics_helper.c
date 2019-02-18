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
    i = (int) floorf(h);
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

void set_color(SDL_Renderer* renderer, int color) {
    float r, g, b;
    hsv_to_rgb(&r, &g, &b, color, 1, 1);
    SDL_SetRenderDrawColor(renderer, (uint8_t) floorf(r), (uint8_t) floorf(g), (uint8_t) floorf(b), 255);
}
