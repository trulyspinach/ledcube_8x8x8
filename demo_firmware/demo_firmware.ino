
#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdbool.h>

uint8_t vram[64] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

uint8_t vram_addr_map[8] = {
  0x01, 0x02, 0x04, 0x08, 0x80, 0x40, 0x20, 0x10
};

uint8_t cur_layer = 0;

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
  delayMicroseconds(520);
  PORTB = 0;

  if(++cur_layer >= 8) cur_layer = 0;
}

void setup_refresh_task(){
  TCCR1A = 0x0;
  TCCR1B = 0x03 | _BV(WGM12);
  OCR1A = 0xff;
  TIMSK |= _BV(OCIE1A);

  sei();
}

void set_voxel(uint8_t x, uint8_t y, uint8_t z){
  uint8_t addr = (z % 8) * 8 + (y % 8);
  vram[addr] |= (1 << (x % 8));
}

void reset_voxel(uint8_t x, uint8_t y, uint8_t z){
  uint8_t addr = (z % 8) * 8 + (y % 8);
  vram[addr] &= ~(1 << (x % 8));
}

uint8_t get_voxel(uint8_t x, uint8_t y, uint8_t z){
  uint8_t addr = (z % 8) * 8 + (y % 8);
  return (vram[addr] >> (x % 8)) & 0x01;
}

uint8_t LED_PIN = 15;

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
}
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);

  for(uint8_t i = 0; i < 3; i++){
    digitalWrite(LED_PIN, HIGH);
    delay(20);
    digitalWrite(LED_PIN, LOW);
    delay(20);
  }

  init_cube();

  setup_refresh_task();

  test_voxel();
}


void loop() {


}

void fill_vram(){
  for(uint8_t i; i < 64; i++)
    vram[i] = 0xff;
}

void test_voxel(){
  fill_vram();

  uint8_t x = 0;
  uint8_t y = 0; 
  uint8_t z = 0; 

  bool s_reset = true;

  while(1){
    if(s_reset) reset_voxel(x++,y,z);
    else set_voxel(x++,y,z);
    
    if(x >= 8){x = 0; y++;}
    if(y >= 8){y = 0; z++;}
    if(z >= 8){z = 0; s_reset = !s_reset;}

    delay(10);
  }
}

