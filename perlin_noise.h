#pragma once
#ifndef perlman_noise_h_
#define perlman_noise_h_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void getNoise(int *image, int width, int height, int max_color, int iterations, int seed);

#endif // !perlman_noise_h_
