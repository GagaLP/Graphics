//
// Created by Gabriel Mitterrutzner on 2019-02-17.
//

#ifndef GRAPHICS_GRAPHICS_HELPER_H
#define GRAPHICS_GRAPHICS_HELPER_H

#include <SDL2/SDL.h>

//math
int map(int x, int in_min, int in_max, int out_min, int out_max);
double map_d(double x, double in_min, double in_max, double out_min, double out_max);
double deg_to_rad(double angle);
double mod_d(double num, double mod);

//color
void hsv_to_rgb(float *r, float *g, float *b, float h, float s, float v);
void set_color(SDL_Renderer* renderer, int color);

#endif //GRAPHICS_GRAPHICS_HELPER_H
