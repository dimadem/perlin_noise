#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>

#define WIDTH 800
#define HEIGHT 600

float perlin2d(float nx, float ny, float freq, int depth);

#endif