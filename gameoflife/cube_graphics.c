#include <arduino.h>
#include "cube_graphics.h"
#include <stdlib.h>

long cg_random(long howsmall, long howbig)
{
  if (howsmall >= howbig) {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return (random() % diff) + howsmall;
}

void random_on(uint16_t num, uint16_t range){

  uint16_t rmn = range;
  uint16_t count = 0;
  while(rmn > 0 && count < num){
    uint16_t t_offset = cg_random(1,rmn--);
    uint16_t t_c = 0; uint16_t index = 0;
    while(t_c != t_offset){
       if(vram_bit_get(index++)) continue;
       t_c++;
    }
    vram_bit_set(index - 1);
    count++;
  }
}
