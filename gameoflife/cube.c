#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "cube.h"

uint8_t default_vram[64] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

uint8_t* vram;

uint8_t vram_addr_map[8] = {
  0x01, 0x02, 0x04, 0x08, 0x80, 0x40, 0x20, 0x10
};

//########## Cube refresh routine. ##########

void init_vram(){
  vram = default_vram;
}

void swap_vram(uint8_t ram){
  vram = ram;
}

void setup_refresh_task(){
  TCCR1A = 0x0;
  TCCR1B = 0x3 | _BV(WGM12);
  OCR1A = 0xff;
  TIMSK |= _BV(OCIE1A);

  sei();
}

uint8_t cur_layer = 0;
//Timer interrupt routine to switch layers at constant time interval.
ISR(TIMER1_COMPA_vect){
  PORTC = 0x00;
  for(uint8_t i = 0; i < 8; i++){
    PORTA = vram[cur_layer * 8 + i];
    delayMicroseconds(1);
    PORTC = vram_addr_map[i];
    delayMicroseconds(1);
    PORTC = 0x00;
  }

  PORTB = 1 << cur_layer;
  delayMicroseconds(70);
  PORTB = 0;

  cur_layer++;
  if(cur_layer >= 8) cur_layer = 0;

}

//########## Cube refresh routine. ##########

//########## Low level graphic. #########

void g_set_voxel(uint8_t* ram, uint8_t x, uint8_t y, uint8_t z){
  uint8_t addr = (z % 8) * 8 + (y % 8);
  ram[addr] |= 1 << (x % 8);
}

void g_reset_voxel(uint8_t* ram, uint8_t x, uint8_t y, uint8_t z){
  uint8_t addr = (z % 8) * 8 + (y % 8);
  ram[addr] &= ~(1 << (x % 8));
}

uint8_t g_get_voxel(uint8_t* ram, uint8_t x, uint8_t y, uint8_t z){
  uint8_t addr = (z % 8) * 8 + (y % 8);
  return (ram[addr] >> x) & 0x01;
}

void set_voxel(uint8_t x, uint8_t y, uint8_t z){
  g_set_voxel(vram, x, y, z);
}

void reset_voxel(uint8_t x, uint8_t y, uint8_t z){
  g_reset_voxel(vram, x, y, z);
}

uint8_t get_voxel(uint8_t x, uint8_t y, uint8_t z){
  uint8_t res = g_get_voxel(vram, x, y, z);
  return res;
}

void reset_vram(){
  for(uint8_t i = 0; i < 64; i++)
    vram[i] = 0x00;
}

void fill_vram(){
  for(uint8_t i = 0; i < 64; i++)
    vram[i] = 0xff;
}

void vram_bit_set(uint16_t index){
  set_voxel(index % 8, (index % 64) / 8, index / 64);
}

void vram_bit_reset(uint16_t index){
  reset_voxel(index % 8, (index % 64) / 8, index / 64);
}

uint8_t vram_bit_get(uint16_t index){
  return get_voxel(index % 8, (index % 64) / 8, index / 64);
}

void vram_shift_down(){
  uint8_t carry[8];
  for(uint8_t i = 0; i < 8; i++) carry[i] = vram[8*7 + i];

  for(uint8_t i = 0; i < 8; i++){
    for(uint8_t j = 0; j < 8; j++){
      uint8_t cache = vram[i * 8 + j];
      vram[i * 8 + j] = carry[j];
      carry[j] = cache;
    }
  }
}

//########## Low level graphic. #########

bool ledOn = 0;

void flash_startup_indic(){
  for(int i = 0; i < 5;i++){
    digitalWrite(14, HIGH);
    delay(35);
    digitalWrite(14, LOW);
    delay(35);
  }
  digitalWrite(14, HIGH);
}

void init_cube(){
  DDRA = 0xff; DDRB = 0xff; DDRC = 0xff;

  PORTA = 0xff;
  PORTB = 0x00; //Turn all layers display off.

  PORTC = 0x00;
  PORTC = 0xff;

  //Write to all vram chip.
  PORTC = 0x00;
  delayMicroseconds(1);
  PORTC = 0xff;

  //Reset clock bus
  PORTC = 0x00;

  init_vram();
  setup_refresh_task();
}
