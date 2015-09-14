CATSFC-libretro-vita

Based on:
CATSFC version 1.36, 2013-06-16
https://github.com/libretro/CATSFC-libretro

A Super Nintendo emulator for PlayStation VITA, run through the native VITA 
hack: Rejuvenate

Based on:
* Snes9x 1.43, by the Snes9x team (with research by the ZSNES folks, anomie,
  zsKnight, etc.)
* NDSSFC 1.06, by the Supercard team (porting to the MIPS processor)
* BAGSFC, by BassAceGold (improving over NDSSFC)
* CATSFC, by ShadauxCat and Nebuleon (improving over BAGSFC)
* CATSFC-libretro, a libretro-compliant port of CATSFC

# Installation

Run the emulator using the Rejuvenate for PSM Unity hack. This emulator will 
likely not run under non-Unity Rejuvenate, but I haven't tested personally.

# Usage

Use FTPVita (or similar) to copy over ROM files to your PSVITA system. The ROMs
can be anywhere on the filesystem. Once the ROMs are on your device, run the
emulator. You can configure the controls, but by default, pressing L-trigger + R-trigger
during a game will bring you back to the menu.


# Compilation

This emulator is configured to build with the vitasdk. Also requires the following:

* vita_portlibs: https://github.com/xerpi/vita_portlibs
* vita2dlib: https://github.com/xerpi/vita2dlib
* psplib4vita: https://github.com/frangarcj/psplib4vita
