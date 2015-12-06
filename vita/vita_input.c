// Author: skogaby
// Lots of examples were followed using other emulators found on github

#include "vita_input.h"

void handle_button_press(unsigned int mapping, unsigned int pressed);

/***
 * Initializes our keybinding to handle input later on.
 */
void setup_input()
{
	pad = (SceCtrlData*)malloc(sizeof(SceCtrlData));
	keymap = (uint32_t*)malloc(sizeof(uint32_t) * 12);
    mouse_current_x = 0;
    mouse_current_y = 0;

	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    if (!pad || !keymap)
    {
        printf("Unable to allocate memory for input data. Bailing.");
        sceKernelExitProcess(0);
    }
}

/***
 * Callback for polling for new input.
 */
void retro_input_poll_callback()
{
	sceCtrlPeekBufferPositive(0, pad, 1);
    keys_down = pad->buttons;
    stick_in_use = false;

    // first, handle (single) physical button presses
    unsigned int i;

    for (i = MAP_BUTTON_UP; i <= MAP_BUTTON_START; i++)
    {
        handle_button_press(ActiveConfig.ButtonMap[i], keys_down & PhysicalButtonMap[i]);
    }

    // next, handle multi-button presses (L + R or start + select)
    if ((keys_down & SCE_CTRL_LTRIGGER) && (keys_down & SCE_CTRL_RTRIGGER))
    {
        handle_button_press(ActiveConfig.ButtonMap[MAP_BUTTON_LRTRIGGERS], true);
    }

    if ((keys_down & SCE_CTRL_START) && (keys_down & SCE_CTRL_SELECT))
    {
        handle_button_press(ActiveConfig.ButtonMap[MAP_BUTTON_STARTSELECT], true);
    }

    // handle the left analog stick
    if (pad->ly < 128 - JOY_THRESHOLD) // analog up
    {
        handle_button_press(ActiveConfig.ButtonMap[MAP_ANALOG_UP], true);
        mouse_current_y += ((pad->ly - 128) / 90) * Settings.MouseSpeed;
        stick_in_use = true;
    }
    else if (pad->ly > 128 + JOY_THRESHOLD) // analog down
    {
        handle_button_press(ActiveConfig.ButtonMap[MAP_ANALOG_DOWN], true);
        mouse_current_y += ((pad->ly - 128) / 90) * Settings.MouseSpeed;
        stick_in_use = true;
    }

    if (pad->lx < 128 - JOY_THRESHOLD) // analog left
    {
        handle_button_press(ActiveConfig.ButtonMap[MAP_ANALOG_LEFT], true);
        mouse_current_x += ((pad->lx - 128) / 90) * Settings.MouseSpeed;
        stick_in_use = true;
    }
    else if (pad->lx > 128 + JOY_THRESHOLD) // analog right
    {
        handle_button_press(ActiveConfig.ButtonMap[MAP_ANALOG_RIGHT], true);
        mouse_current_x += ((pad->lx - 128) / 90) * Settings.MouseSpeed;
        stick_in_use = true;
    }

    // only handle the right analog stick if the left stick wasn't in use,
    // so they don't double each other or cancel each other out
    if (!stick_in_use)
    {
        if (pad->ry < 128 - JOY_THRESHOLD) // analog up
        {
            mouse_current_y += ((pad->ry - 128) / 90) * Settings.MouseSpeed;
        }
        else if (pad->ry > 128 + JOY_THRESHOLD) // analog down
        {
            mouse_current_y += ((pad->ry - 128) / 90) * Settings.MouseSpeed;
        }

        if (pad->rx < 128 - JOY_THRESHOLD) // analog left
        {
            mouse_current_x += ((pad->rx - 128) / 90) * Settings.MouseSpeed;
        }
        else if (pad->rx > 128 + JOY_THRESHOLD) // analog right
        {
            mouse_current_x += ((pad->rx - 128) / 90) * Settings.MouseSpeed;
        }
    }
}

/***
 * Callback to set the current input states based on the last polled input.
 */
int16_t retro_input_state_callback(unsigned port, unsigned device, unsigned index, unsigned id)
{
    if (port != 0)
    {
        return 0;
    }

	return keymap[id];
}

/***
 * Handles an input mapping and whether or not it's actually being pressed
 */
void handle_button_press(unsigned int mapping, unsigned int pressed)
{
    // handle it just being a normal button press
    if (mapping <= RETRO_DEVICE_ID_JOYPAD_R)
    {
        keymap[mapping] = pressed;
    }
    // user wants to go back to the menu
    else if (pressed && (mapping == SPC_MENU))
    {
        ResumeEmulation = 0;
    }
}

/***
 * Emulate the SNES mouse. I think this is only used in Mario Paint, but goddamnit,
 * I love Mario Paint.
 */
bool S9xReadMousePosition(int which1, int* x, int* y, uint32_t* buttons)
{
    if (which1 != 0)
    {
        return false;
    }

    // right now, mouse controls are hard-coded to the analog sticks,
    // and a few buttons acting as L/R-click. maybe later I'll make it
    // configurable
    *x = mouse_current_x;
    *y = mouse_current_y;

    // left-click is cross, square, or L-trigger
    if ((keys_down & SCE_CTRL_LTRIGGER) ||
        (keys_down & SCE_CTRL_SQUARE) ||
        (keys_down & SCE_CTRL_CROSS))
    {
        *buttons |= 0x1;
    }

    // right-click is circle, triangle, or R-trigger
    if ((keys_down & SCE_CTRL_RTRIGGER) ||
        (keys_down & SCE_CTRL_TRIANGLE) ||
        (keys_down & SCE_CTRL_CIRCLE))
    {
        *buttons |= 0x2;
    }

    return true;
}