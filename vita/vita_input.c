// Author: skogaby
// Lots of examples were followed using other emulators found on github

#include "vita_input.h"

void handle_button_press(unsigned int player, unsigned int mapping, unsigned int pressed);

/***
 * Initializes our keybinding to handle input later on.
 */
void setup_input()
{
	pad = (SceCtrlData*)malloc(sizeof(SceCtrlData));
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    if (!pad)
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
    unsigned int player;

    for (player = 0; player <= 1; player++)
    {
        sceCtrlPeekBufferPositive(player + 1, pad, 1);
        keys_down[player] = pad->buttons;
        stick_in_use[player] = false;

        // first, handle (single) physical button presses
        unsigned int i;

        for (i = MAP_BUTTON_UP; i <= MAP_BUTTON_START; i++)
        {
            handle_button_press(player, ActiveConfig.ButtonMap[i], keys_down[player] & PhysicalButtonMap[i]);
        }

        // next, handle multi-button presses (L + R or start + select)
        if ((keys_down[player] & SCE_CTRL_LTRIGGER) && (keys_down[player] & SCE_CTRL_RTRIGGER))
        {
            handle_button_press(player, ActiveConfig.ButtonMap[MAP_BUTTON_LRTRIGGERS], true);
        }

        if ((keys_down[player] & SCE_CTRL_START) && (keys_down[player] & SCE_CTRL_SELECT))
        {
            handle_button_press(player, ActiveConfig.ButtonMap[MAP_BUTTON_STARTSELECT], true);
        }

        // handle the left analog stick
        if (pad->ly < 128 - JOY_THRESHOLD) // analog up
        {
            handle_button_press(player, ActiveConfig.ButtonMap[MAP_ANALOG_UP], true);
            mouse_current_y[player] += ((pad->ly - 128) / 90) * Settings.MouseSpeed;
            stick_in_use[player] = true;
        }
        else if (pad->ly > 128 + JOY_THRESHOLD) // analog down
        {
            handle_button_press(player, ActiveConfig.ButtonMap[MAP_ANALOG_DOWN], true);
            mouse_current_y[player] += ((pad->ly - 128) / 90) * Settings.MouseSpeed;
            stick_in_use[player] = true;
        }

        if (pad->lx < 128 - JOY_THRESHOLD) // analog left
        {
            handle_button_press(player, ActiveConfig.ButtonMap[MAP_ANALOG_LEFT], true);
            mouse_current_x[player] += ((pad->lx - 128) / 90) * Settings.MouseSpeed;
            stick_in_use[player] = true;
        }
        else if (pad->lx > 128 + JOY_THRESHOLD) // analog right
        {
            handle_button_press(player, ActiveConfig.ButtonMap[MAP_ANALOG_RIGHT], true);
            mouse_current_x[player] += ((pad->lx - 128) / 90) * Settings.MouseSpeed;
            stick_in_use[player] = true;
        }

        // only handle the right analog stick if the left stick wasn't in use,
        // so they don't double each other or cancel each other out
        if (!stick_in_use[player])
        {
            if (pad->ry < 128 - JOY_THRESHOLD) // analog up
            {
                mouse_current_y[player] += ((pad->ry - 128) / 90) * Settings.MouseSpeed;
            }
            else if (pad->ry > 128 + JOY_THRESHOLD) // analog down
            {
                mouse_current_y[player] += ((pad->ry - 128) / 90) * Settings.MouseSpeed;
            }

            if (pad->rx < 128 - JOY_THRESHOLD) // analog left
            {
                mouse_current_x[player] += ((pad->rx - 128) / 90) * Settings.MouseSpeed;
            }
            else if (pad->rx > 128 + JOY_THRESHOLD) // analog right
            {
                mouse_current_x[player] += ((pad->rx - 128) / 90) * Settings.MouseSpeed;
            }
        }
    }
}

/***
 * Callback to set the current input states based on the last polled input.
 */
int16_t retro_input_state_callback(unsigned port, unsigned device, unsigned index, unsigned id)
{
    if (port > 1)
    {
        return 0;
    }

	return keymap[port][id];
}

/***
 * Handles an input mapping and whether or not it's actually being pressed
 */
void handle_button_press(unsigned int player, unsigned int mapping, unsigned int pressed)
{
    // handle it just being a normal button press
    if (mapping <= RETRO_DEVICE_ID_JOYPAD_R)
    {
        keymap[player][mapping] = pressed;
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
bool S9xReadMousePosition(int player, int* x, int* y, uint32_t* buttons)
{
    if (player > 1)
    {
        return false;
    }

    // right now, mouse controls are hard-coded to the analog sticks,
    // and a few buttons acting as L/R-click. maybe later I'll make it
    // configurable
    *x = mouse_current_x[player];
    *y = mouse_current_y[player];

    // left-click is cross, square, or L-trigger
    if ((keys_down[player] & SCE_CTRL_LTRIGGER) ||
        (keys_down[player] & SCE_CTRL_SQUARE) ||
        (keys_down[player] & SCE_CTRL_CROSS))
    {
        *buttons |= 0x1;
    }

    // right-click is circle, triangle, or R-trigger
    if ((keys_down[player] & SCE_CTRL_RTRIGGER) ||
        (keys_down[player] & SCE_CTRL_TRIANGLE) ||
        (keys_down[player] & SCE_CTRL_CIRCLE))
    {
        *buttons |= 0x2;
    }

    return true;
}