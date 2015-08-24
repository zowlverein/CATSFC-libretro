TARGET = CATSFC-libretro-vita

CORE_DIR := source
VITA_DIR := vita
LIBRETRO_DIR := libretro

SOURCES_C := \
	$(CORE_DIR)/apu.c $(CORE_DIR)/c4.c $(CORE_DIR)/c4emu.c $(CORE_DIR)/cheats2.c $(CORE_DIR)/cheats.c \
	$(CORE_DIR)/clip.c $(CORE_DIR)/cpu.c $(CORE_DIR)/cpuexec.c $(CORE_DIR)/cpuops.c $(CORE_DIR)/data.c\
	$(CORE_DIR)/dma.c $(CORE_DIR)/dsp1.c $(CORE_DIR)/fxdbg.c $(CORE_DIR)/fxemu.c $(CORE_DIR)/fxinst.c \
	$(CORE_DIR)/gfx.c $(CORE_DIR)/globals.c $(CORE_DIR)/memmap.c $(CORE_DIR)/obc1.c $(CORE_DIR)/ppu.c \
	$(CORE_DIR)/sa1.c $(CORE_DIR)/sa1cpu.c $(CORE_DIR)/sdd1.c $(CORE_DIR)/sdd1emu.c $(CORE_DIR)/seta010.c \
	$(CORE_DIR)/seta011.c $(CORE_DIR)/seta018.c $(CORE_DIR)/seta.c $(CORE_DIR)/soundux.c $(CORE_DIR)/spc700.c \
	$(CORE_DIR)/spc7110.c $(CORE_DIR)/srtc.c $(CORE_DIR)/tile.c $(CORE_DIR)/apu_blargg.c
SOURCES_C += $(LIBRETRO_DIR)/libretro.c
SOURCES_C += $(VITA_DIR)/font_data.c $(VITA_DIR)/font.c $(VITA_DIR)/file_chooser.c $(VITA_DIR)/utils.c \
    $(VITA_DIR)/vita_input.c $(VITA_DIR)/vita_audio.c $(VITA_DIR)/vita_video.c $(VITA_DIR)/main.c
    
OBJS := $(SOURCES_C:.c=.o)

LIBS = -lSceDisplay_stub -lSceGxm_stub -lSceCtrl_stub -lSceTouch_stub -lSceAudio_stub -lc_stub -lm_stub -lvita2d

PREFIX   = $(DEVKITARM)/bin/arm-none-eabi
CC       = $(PREFIX)-gcc
CFLAGS   = -Wall -O3 -specs=psp2.specs -DVITA
CFLAGS  += -w -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -ftree-vectorize \
		   -mfloat-abi=hard -ffast-math -fsingle-precision-constant -ftree-vectorizer-verbose=2 -fopt-info-vec-optimized -funroll-loops \
           -mword-relocations -fno-rtti -Wno-deprecated -Wno-comment -Wno-sequence-point
CFLAGS  += -DHAVE_STRINGS_H -DHAVE_STDINT_H -DHAVE_INTTYPES_H -DRIGHTSHIFT_IS_SAR -DINLINE=inline -DFRONTEND_SUPPORTS_RGB565
CFLAGS  += -DSPC700_C -DEXECUTE_SUPERFX_PER_LINE -DSDD1_DECOMP \
           -DVAR_CYCLES -DCPU_SHUTDOWN -DSPC700_SHUTDOWN \
           -DNO_INLINE_SET_GET -DNOASM -DHAVE_MKSTEMP '-DACCEPT_SIZE_T=size_t' -DWANT_CHEATS
CFLAGS  += -D__LIBRETRO__
ASFLAGS  = $(CFLAGS)


INCFLAGS := -I$(CORE_DIR) -I$(VITA_DIR) -I$(LIBRETRO_DIR)

all: $(TARGET)_fixup.elf

%_fixup.elf: %.elf
	psp2-fixup -q -S $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf $(TARGET)_fixup.elf $(TARGET).elf $(OBJS)

copy: $(TARGET)_fixup.elf
	@cp $(TARGET)_fixup.elf ~/shared/vitasample.elf
	@echo "Copied!"