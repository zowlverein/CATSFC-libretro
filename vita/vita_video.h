// Author: skogaby
// Lots of examples were followed using other emulators found on github

#ifndef __VITA_VIDEO_H__
#define __VITA_VIDEO_H__

#define SCREEN_W 960
#define SCREEN_H 544

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <psp2/display.h>
#include <psp2/gxm.h>

#include <vita2d.h>
#include "../libretro/libretro.h"

// helpers for rendering
unsigned long curr_frame;
clock_t last_render_time;
int scale_x, scale_y;
int pos_x, pos_y;
unsigned short h, w;
vita2d_texture *tex;
void *tex_data;

bool retro_video_refresh_callback(const void *data, unsigned width, unsigned height, size_t pitch);
void show_fps();

#endif