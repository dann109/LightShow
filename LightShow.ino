// Simple NeoPixel test.  Lights just a few pixels at a time so a
// long strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip -- look for the data
// direction arrows printed on the strip.
 
#include <Adafruit_NeoPixel.h>
 
#define PIN    6
#define N_LEDS 170 // 5 meter reel @ 30 LEDs/m
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int Red = 0xFF0000;
int Green = 0x00FF00;
int Blue = 0x0000FF;

int count = 0;

void setup() {
  strip.begin();
}
 
void loop() {
if (count%2 == 0) chaseforward(Green); // Green
if (count%3 == 0) chasebackward(Blue); // Blue
if (count%5 == 0) repel(Green);
if (count%7 == 0) collide(Blue);
if (count%11 == 0) chase_rainbow();
if (count%13 == 0) collide(Blue);
if (count%17 == 0) circle();
if (count%19 == 0) GBRotate();
if (count%23 == 0) Glow();
count++;
if (count > 999999999) count = 0;
}

static void circle(void) {
  for (int k=0; k<3; k++) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , Green); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      
      strip.setPixelColor((i+42)%170  , Blue); // Draw new pixel
      strip.setPixelColor((i+42-4)%170, 0); // Erase pixel a few steps back

      strip.setPixelColor((i+85)%170  , Green); // Draw new pixel
      strip.setPixelColor((i+85-4)%170, 0); // Erase pixel a few steps back

      strip.setPixelColor((i+127)%170  , Blue); // Draw new pixel
      strip.setPixelColor((i+127-4)%170, 0); // Erase pixel a few steps back
      
      strip.show();
  }

  for(uint16_t i=strip.numPixels()+4; i>0; i--) {
      strip.setPixelColor(i  , Green); // Draw new pixel
      strip.setPixelColor(i+4, 0); // Erase pixel a few steps back
      
      strip.setPixelColor((i+42)%170  , Blue); // Draw new pixel
      strip.setPixelColor((i+42+4)%170, 0); // Erase pixel a few steps back

      strip.setPixelColor((i+85)%170  , Green); // Draw new pixel
      strip.setPixelColor((i+85+4)%170, 0); // Erase pixel a few steps back

      strip.setPixelColor((i+127)%170  , Blue); // Draw new pixel
      strip.setPixelColor((i+127+4)%170, 0); // Erase pixel a few steps back
      
      strip.show();
  }
  }
}

static void chaseforward(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back

      strip.setPixelColor((i+85)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+85-4)%170, 0); // Erase pixel a few steps back
      
      strip.show();
  }
}

static void chasebackward(uint32_t c) {
  for(uint16_t i=strip.numPixels()+4; i>0; i--) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i+4, 0); // Erase pixel a few steps back

      strip.setPixelColor((i+85)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+85+4)%170, 0); // Erase pixel a few steps back
      
      strip.show();
  }
}

static void collide(uint32_t c) {
  for(uint16_t i=0; i<(strip.numPixels()+4)/2; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back

      strip.setPixelColor(strip.numPixels()+4 - i  , c); // Draw new pixel
      strip.setPixelColor(strip.numPixels()+4 - i + 4, 0); // Erase pixel a few steps back
      strip.show();
  }
}

static void repel(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {

      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back

      strip.setPixelColor(strip.numPixels()+4 - i  , c); // Draw new pixel
      strip.setPixelColor(strip.numPixels()+4 - i + 4, 0); // Erase pixel a few steps back
      
      
//      if (i<80) delay(i/2);
//      if (i>95) delay(95/2 - i/2);

      if (i< 80 || i> 95) strip.show();
      
  }
}

static void chase_rainbow(void) {
  for(int k=0;k<3;k++){
  for(uint16_t j=0; j<3; j++) {
  for(uint16_t i=0; i<57; i++) {
      strip.setPixelColor(i*3+j   , 0xFF0000); // Draw new pixel
      strip.setPixelColor(i*3+1+j , 0x00FF00); // Draw new pixel
      strip.setPixelColor(i*3+2+j , 0x0000FF); // Draw new pixel
    }
     strip.show();
     delay(120);
  }
  }

  for(int k=0;k<6;k++){
  for(uint16_t j=0; j<3; j++) {
  for(uint16_t i=0; i<42; i++) {
      strip.setPixelColor(i*4+j, 0x00FF00); // Draw new pixel
      strip.setPixelColor(i*4+1+j, 0x00FF00); // Draw new pixel
      strip.setPixelColor(i*4+2+j , 0x0000FF); // Draw new pixel
      strip.setPixelColor(i*4+3+j , 0x0000FF); // Draw new pixel
    }
     strip.show();
     delay(60);
  }
  }

  for(int k=0;k<6;k++){
  for(uint16_t j=0; j<3; j++) {
  for(uint16_t i=0; i<28; i++) {
      strip.setPixelColor(i*6+j , 0x00FF00); // Draw new pixel
      strip.setPixelColor(i*6+1+j , 0x00FF00); // Draw new pixel
      strip.setPixelColor(i*6+2+j , 0x00FF00); // Draw new pixel
      strip.setPixelColor(i*6+3+j , 0x0000FF); // Draw new pixel
      strip.setPixelColor(i*6+4+j , 0x0000FF); // Draw new pixel
      strip.setPixelColor(i*6+5+j , 0x0000FF); // Draw new pixel
    }
     strip.show();
     delay(60);
  }
  }
}

static void GBRotate(void) {

    for(uint16_t i=0; i<strip.numPixels()+4; i++) { // 1/2
      strip.setPixelColor(i  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+85)%170  , 0x00FF00); // Draw new pixel
      strip.show();
    }

    for(uint16_t i=0; i<strip.numPixels()+4; i++) { // 1/4
      strip.setPixelColor(i  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/4*2)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/4*3)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/4*4)%170  , 0x00FF00); // Draw new pixel
      strip.show();
    }

    for(uint16_t i=0; i<strip.numPixels()+4; i++) { // 1/8
      strip.setPixelColor(i  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/8*1)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/8*2)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/8*3)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/8*4)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/8*5)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/8*6)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/8*7)%170  , 0x00FF00); // Draw new pixel
      strip.show();
    }

    for(uint16_t i=0; i<strip.numPixels()+4; i++) { // 1/16
      strip.setPixelColor(i  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/16*1)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/16*2)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/16*3)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/16*4)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/16*5)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/16*6)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/16*7)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/16*8)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/16*9)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/16*10)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/16*11)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/16*12)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/16*13)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/16*14)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/16*15)%170  , 0x00FF00); // Draw new pixel
      strip.show();
    }

    for(uint16_t i=0; i<strip.numPixels()+4; i++) { // 1/16
      strip.setPixelColor(i  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*1)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*2)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*3)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*4)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*5)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*6)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*7)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*8)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*9)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*10)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*11)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*12)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*13)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*14)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*15)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*16)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*17)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*18)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*19)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*20)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*21)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*22)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*23)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*24)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*25)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*26)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*27)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*28)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*29)%170  , 0x00FF00); // Draw new pixel
      strip.setPixelColor((i+170/32*30)%170  , 0x0000FF); // Draw new pixel
      strip.setPixelColor((i+170/32*31)%170  , 0x00FF00); // Draw new pixel
      strip.show();
    }

  
}

static void Glow(void) {
  for(int k=10; k<25000; k*=1.1) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , k); // Draw new pixel
  }
  strip.show();
  }

}
