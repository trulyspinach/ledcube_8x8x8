
extern "C"
{
  #include "cube.h"
  #include "cube_graphics.h"
  #include "gameoflife.h"
}


void setup() {
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);

  randomSeed(analogRead(0));

  flash_startup_indic();

  init_cube();

  Serial.begin(115200);
  //Set default brightness for cube.
  //analogWrite(15, 210);


  Serial.println("Cube alive!");
  // noise_on();
  // noise_off();
  //
  // rain();

  rand_gen();
  //test_two();
}

void loop(){
  tick();
  //delay(200);
}

void print_coor(uint8_t x, uint8_t y, uint8_t z){
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z);
}



//########## Effects ###########




void voxel_test(){

  Serial.println("voxel test");

  fill_vram();
  uint8_t x = 0;
  uint8_t y = 0;
  uint8_t z = 0;

  bool s_reset = true;

  while(1){
    if(s_reset == false && x == 7 && y == 7 && z == 7) break;
    if(s_reset) reset_voxel(x++,y,z);
    else set_voxel(x++, y, z);
    if(x >= 8){x = 0; y++;}
    if(y >= 8){y = 0; z++;}
    if(z >= 8){z = 0; s_reset = !s_reset;}
    delay(2);

  }
}

void voxel_test_bit(){
  uint16_t remain = 0;

  Serial.println("bit test");
  reset_vram();

  while(remain < 512){
    vram_bit_set(remain++);
    //Serial.println(vram_bit_get(remain++));
    delay(2);
  }
}

void noise_on(){
  reset_vram();
  uint16_t rmn = 512;

  while(rmn > 0){
    uint16_t t_offset = random(1,rmn--);
    uint16_t t_c = 0; uint16_t index = 0;
    while(t_c != t_offset){
       if(vram_bit_get(index++)) continue;
       t_c++;
    }
    vram_bit_set(index - 1);

    //delay(2);
  }
}



void noise_off(){
  uint16_t rmn = 512;

  while(rmn > 0){
    uint16_t t_offset = random(1,rmn--);
    uint16_t t_c = 0; uint16_t index = 0;
    while(t_c != t_offset){
       if(!vram_bit_get(index++)) continue;
       t_c++;
    }
    vram_bit_reset(index - 1);

    //delay(2);
  }
}

void rain(){
  reset_vram();
  uint8_t t = 50;
  while(t-- > 0){
    for(uint8_t i = 0; i < 8; i++)
      vram[i] = 0x00;

    random_on(random(1,8),64);
    vram_shift_down();

    delay(60);
  }

}
