// Author: skogaby
// Lots of examples were followed using other emulators found on github

#ifndef __VITA_INPUT_H__
#define __VITA_INPUT_H__

#define JOY_THRESHOLD 100

#include <stdlib.h>

#include <psp2/io/fcntl.h>
#include <psp2/ctrl.h>

#include "vita_menu.h"
#include "../libretro/libretro.h"
#include "../source/snes9x.h"

// helpers for input
SceCtrlData *pad;
uint32_t keymap[2][12];
uint32_t keys_down[2];
int mouse_current_x;
int mouse_current_y;
bool stick_in_use;
extern int ResumeEmulation;

void setup_input();
void retro_input_poll_callback();

int16_t retro_input_state_callback(unsigned port, unsigned device, unsigned index, unsigned id);

#endif