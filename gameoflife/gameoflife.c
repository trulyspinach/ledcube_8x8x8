#include <arduino.h>
#include "cube.h"
#include "cube_graphics.h"
#include "gameoflife.h"

uint8_t matrix[64] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void draw(){
  for(uint8_t i = 0; i < 64; i++)
    vram[i] = matrix[i]; //Simply copy matrix to vram.
}

void rand_gen(){
  reset_vram();
  for(uint8_t i = 0; i < 64; i++)
    matrix[i] = 0x00;

  random_on(90, 512);
}

void test_two(){
  reset_vram();
  vram[1] = 0x8;
  vram[2] = 0x1c;
  vram[3] = 0x8;
  //vram[3] = 0x3;
}

uint8_t count_surrounding(uint8_t p_x, uint8_t p_y, uint8_t p_z){
  uint8_t c = 0;
  for(int8_t x = -1; x <= 1; x++)
    for(int8_t y = -1; y <= 1; y++)
      for(int8_t z = -1; z <= 1; z++){
        if(x == 0 && y == 0 && z == 0) continue;

        //There's no need for bound check since get_voxel will warp the coord.
        c += g_get_voxel(vram, p_x + x, p_y + y, p_z + z);
      }
  return c;
}

void tick(){

  for(uint16_t i = 0; i < 512; i++){
    uint8_t x = i % 8;
    uint8_t y = (i % 64) / 8;
    uint8_t z = i / 64;

    uint8_t c = count_surrounding(x,y,z);

    //New Rules !!
    if(g_get_voxel(vram, x, y, z)){
      if(c >= RULE_EL && c <= RULE_EU)
        g_set_voxel(matrix, x, y, z);
      else
        g_reset_voxel(matrix, x, y, z);

    } else {
      if(c >= RULE_FL && c <= RULE_FU)
        g_set_voxel(matrix, x, y, z);
      else
        g_reset_voxel(matrix, x, y, z);
    }

  }

  //delay(50);
  draw();
}
