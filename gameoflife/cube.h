#ifndef _CUBE_h
#define _CUBE_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

//########## Cube refresh routine. ##########
extern uint8_t *vram;
extern uint8_t vram_addr_map[8];

void swap_vram(uint8_t ram);

//########## Low level graphic. #########

void set_voxel(uint8_t x, uint8_t y, uint8_t z);
void reset_voxel(uint8_t x, uint8_t y, uint8_t z);
uint8_t get_voxel(uint8_t x, uint8_t y, uint8_t z);

void g_set_voxel(uint8_t* ram, uint8_t x, uint8_t y, uint8_t z);
void g_reset_voxel(uint8_t* ram, uint8_t x, uint8_t y, uint8_t z);
uint8_t g_get_voxel(uint8_t* ram, uint8_t x, uint8_t y, uint8_t z);

void reset_vram();

void fill_vram();

void vram_bit_set(uint16_t index);

void vram_bit_reset(uint16_t index);

uint8_t vram_bit_get(uint16_t index);

void vram_shift_down();

//########## Hardware init. #########
void flash_startup_indic();

void init_cube();

#endif
