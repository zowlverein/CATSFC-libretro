CATSFC-libretro-vita

Based on:
CATSFC version 1.36, 2013-06-16
https://github.com/libretro/CATSFC-libretro

A Super Nintendo emulator for PlayStation VITA, run through the native VITA 
hack: HENkaku

Based on:
* Snes9x 1.43, by the Snes9x team (with research by the ZSNES folks, anomie,
  zsKnight, etc.)
* NDSSFC 1.06, by the Supercard team (porting to the MIPS processor)
* BAGSFC, by BassAceGold (improving over NDSSFC)
* CATSFC, by ShadauxCat and Nebuleon (improving over BAGSFC)
* CATSFC-libretro, a libretro-compliant port of CATSFC

# Installation

Build the emulator from source and use HENkaku and molecularShell to copy the VPK
file to your VITA through FTP. Install the VPK file using molecularShell. Run
the resulting bubble on your home screen.

# Usage

Use molecularShell (or similar) to copy over ROM files to your PSVITA system. The ROMs
can be anywhere on the filesystem. Once the ROMs are on your device, run the
emulator. You can configure the controls, but by default, pressing L-trigger + R-trigger
during a game will bring you back to the menu.


# Compilation

This emulator is configured to build with the vitasdk. Also requires the following:

* vita_portlibs: https://github.com/xerpi/vita_portlibs
* vita2dlib: https://github.com/xerpi/vita2dlib
* psplib4vita: https://github.com/frangarcj/psplib4vita

** NOTE **: As of 2016/08/06, I was required to make a patch to the newest psplib4vita
in order to make the text render at the correct height. I don't know if anyone else 
has had this issue, so I haven't submitted a pull request. If you run into this issue,
rebuild psplib4vita with the following change to video.c to move all text down 16px:

int pspVideoPrint(PspFont *font, int sx, int sy, const char *string, uint32_t color)
{
  return pspVideoPrintN(font, sx, sy + 16, string, -1, color);
}