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

# Installing

Run the emulator using the Rejuvenate for PSM Unity hack. This emulator will 
likely not run under non-Unity Rejuvenate, due to RAM limitations

# Compiling

This emulator is configured to build with the PSP2SDK. Might possibly be 
migrating to vita-toolchain in the future. Also requires the following:

vita_portlibs: https://github.com/xerpi/vita_portlibs
vita2dlib: https://github.com/xerpi/vita2dlib
