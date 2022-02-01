#include <Arduino.h>
#include <Adafruit_GFX.h> // graphics library
#include <MCUFRIEND_kbv.h> // screen control library
MCUFRIEND_kbv tft; // define tft object
/**
  * Bestimmung der Netzfrequenz
  * Copyright 2015 by Ralf Th. Pietsch <ratopi@abwesend.de>
  * LICENSE: MIT
  */
// Define some colours for use in screens
#define  BLACK   0x0000
#define  BLUE    0x001F
#define  GREEN   0x07E0
#define  YELLOW  0xFFE0
#define  WHITE   0xFFFF
#define  CHERRY   0xF020

// Netzfreqzenz
#define PROBE_COUNT 500
#define MICROS 1000000.
#define KORREKTUR 1.0
#define SecSamples 100
#define ANTENA_PORT A5

int Vmin;
int Vmax;
int Vval;
int Vmid;
int val;
int i, j;
float freq, freqmin, freqmax;
long start;
long end;
uint16_t last_cursor;

//#############################################################################
//  Function declarations
//#############################################################################

void period();
int analogReadPlus() ;

//#############################################################################
//  Arduino code
//#############################################################################

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(0);
  initTft();
  Serial.begin(9600);
  //analogReference(INTERNAL);
  for ( i = 0; i < 10000; i++ )
  {
      Vval = analogReadPlus();
      Vmin = min( Vmin, Vval);
      Vmax = max( Vmax, Vval);
  }
  Vmid = ( Vmax - Vmin ) / 2;

  blinkThree();  
  period();

  Serial.println( "starting..." );
  writeTft("starting");
}

void loop()
{
  Vmin = 1024;
  Vmax = 0;

  period();

  start = micros();
   
  for ( i = 0; i < PROBE_COUNT; i++ )
  {
    period();
  }
  end = micros();
  freq = (PROBE_COUNT * (MICROS * KORREKTUR / double(end - start)));
  Serial.println("Frequency: " + String(freq, 3));
  writeTft(String(freq, 3));
}

void period() 
{
  while (analogReadPlus() == 0);
  for (j = 0; j < SecSamples; j++) {
    analogReadPlus();
  }
  while (analogReadPlus() > 0);
}

int analogReadPlus() 
{
  Vval = analogRead(ANTENA_PORT);
  return Vval;
}


void initTft() 
{
  last_cursor = 10;
  tft.setCursor(10, last_cursor);
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
}

void writeTft(String s) 
{
  tft.setCursor(10, last_cursor);
  last_cursor += 20;
  if (last_cursor >= 320) {
    initTft();
    last_cursor += 20;
  }
  tft.print(s);
}

void blinkThree() 
{
  for(i = 0; i<3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}
