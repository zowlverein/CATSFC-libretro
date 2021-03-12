// Author: skogaby
// Lots of examples were followed using other emulators found on github

#ifndef __MAIN_H__
#define __MAIN_H__

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#include <psp2/types.h>

#include "utils.h"
#include "vita_input.h"
#include "vita_audio.h"
#include "vita_video.h"
#include "vita_menu.h"
#include "../libretro/libretro.h"

int ResumeEmulation;

// utility functions for our own use
void load_rom();
void vita_cleanup();
void setup_callbacks();
void show_splash();

// our collection of callbacks to plug in to libretro
int retro_environment_callback(unsigned cmd, void *data);

// needed for loading cheats and save files
char rom_path[PATH_MAX];

#endif
