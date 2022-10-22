#include <Arduino_GFX_Library.h>
 
#define TFT_SCK    18
#define TFT_MOSI   23
#define TFT_MISO   19
#define TFT_CS     5
#define TFT_DC     21
 
Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 display = Arduino_ILI9341(&bus);

static int RedniBrojSenzora = 7; // The first sensor is #0(zerro)
 
int PinTrigArray[10] = {32, 33, 14, 27, 13, 1, 4,  2}; // declare Trig & Echo GPIO
int PinEchoArray[10] = {34, 39, 36, 35, 22, 3, 0, 15};
 
long tArray[10]; // declare time var
int sArray[10]; // declare distance var
   
int xArc = 255;
int yArc = 170;
int r1Arc = 60;
int r2Arc = 50;

void crtajPrugu() {
  display.fillArc(xArc, yArc, r1Arc, r2Arc, 0, 360, GREEN);
  //display.fillArc(xArc, yArc, r1Arc - 3, r2Arc + 3, 0, 360, BLACK);
 
  //if ((sArray[0] < 25) && (sArray[7] < 25)) display.fillArc(xArc, yArc, r1Arc, r2Arc,  90, 180, RED);
  //if ((sArray[1] < 25) && (sArray[2] < 25)) display.fillArc(xArc, yArc, r1Arc, r2Arc,   0,  90, RED);
  //if ((sArray[3] < 25) && (sArray[4] < 25)) display.fillArc(xArc, yArc, r1Arc, r2Arc, 270, 360, RED);
  //if ((sArray[5] < 25) && (sArray[6] < 25)) display.fillArc(xArc, yArc, r1Arc, r2Arc, 180,  90, RED);
  if (sArray[0] < 25) display.fillArc(xArc, yArc, r1Arc, r2Arc,  90, 130, RED);
  if (sArray[1] < 25) display.fillArc(xArc, yArc, r1Arc, r2Arc,  50,  90, RED);
  if (sArray[2] < 25) display.fillArc(xArc, yArc, r1Arc, r2Arc,   0,  40, RED);
  if (sArray[3] < 25) display.fillArc(xArc, yArc, r1Arc, r2Arc, 320, 360, RED);
  if (sArray[4] < 25) display.fillArc(xArc, yArc, r1Arc, r2Arc, 270, 310, RED);
  if (sArray[5] < 25) display.fillArc(xArc, yArc, r1Arc, r2Arc, 230, 270, RED);
  if (sArray[6] < 25) display.fillArc(xArc, yArc, r1Arc, r2Arc, 180, 220, RED);
  if (sArray[7] < 25) display.fillArc(xArc, yArc, r1Arc, r2Arc, 140, 180, RED);
}
 
void setup() {
  for (int n = 0; n <= RedniBrojSenzora; n++) {
    pinMode(PinTrigArray[n], OUTPUT); // declare Trig as output
    pinMode(PinEchoArray[n], INPUT); // declare Echo as input
  }
  display.begin();
  display.fillScreen(0);
  display.setRotation(3);
  display.setTextColor(YELLOW, BLACK);
  display.setTextSize(5);
  display.println("VIDI X");
  display.setTextSize(3);
  display.println("    microcomputer");
  display.setTextColor(GREEN, BLACK);
  display.setTextSize(2);
}
 
void loop() {
  for (int n = 0; n <= RedniBrojSenzora; n++) {
    // set Trig LOW 2 microseconds – clearing Trig pin
    digitalWrite(PinTrigArray[n], LOW);
    delayMicroseconds(2); // generate 10 microseconds ultrasound
    digitalWrite(PinTrigArray[n], HIGH);
    delayMicroseconds(10);
    digitalWrite(PinTrigArray[n], LOW);
    tArray[n] = pulseIn(PinEchoArray[n], HIGH); // measure ultrasound travel time
    sArray[n] = tArray[n] * 0.034 / 2; // calculate travel to distance
 
    if (sArray[n] < 1000) {
      display.setCursor(0, 80 + n * 15);
      display.print("Sen.");
      display.print(n);
      display.print(" = ");
      if (sArray[n] < 25) display.setTextColor(RED, BLACK);
      display.print(sArray[n]);
      if (sArray[n] < 25) display.setTextColor(GREEN, BLACK);
      display.println(" cm  ");
    }
  }
 
crtajPrugu();
}
