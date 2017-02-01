// This is the Arduino code for the Arch.
// It uses 3 ultrasound distance sensors to measure the position of a user and changes LEDs to match this state.
// The state is also sent to a computer via serial/USB.
// setup() and loop() are in zmain.ino

#include "FastLED.h"
// last tested using FastLED version 3.001.000

FASTLED_USING_NAMESPACE

#define HEIGHT_FUDGE  12
#define DATA_PIN      11
#define CLOCK_PIN     13
#define LED_TYPE      DOTSTAR
#define COLOR_ORDER   GRB
#define NUM_LEDS      298
#define INDEX_OF_FIRST_LED_ON_SECOND_ROW    149
CRGB leds[NUM_LEDS];

#define LEDsPerCM 0.254 

#define BRIGHTNESS         100
#define FRAMES_PER_SECOND  120 
//#define BACKGROUND_COLOR  CRGB(50,255,10)
//#define FOREGROUND_COLOR  CRGB(250,200,250)

#define BACKGROUND_COLOR  CRGB(170,225,220)
#define FOREGROUND_COLOR  CRGB(0,255,0)
#define FIREBALL_COLOR  CRGB(30,30,200)
//#define MEASURING_COLOR  CRGB(255,0,0)
#define MEASURING_COLOR  CRGB(170,225,220)

#define sensor0Pin  A0    
#define sensor1Pin  A1    
#define sensor2Pin  A2    

#define sensorChainStartPin 4    

#define archHeight 250

 

#define sensorSmothingWindow 5
#define medianPos 3
#define sensorReadDelay 100
#define sensorTriggerDelay 233

int rangevalue0[] = { 0, 0, 0};
int rangevalue1[] = { 0, 0, 0};
int rangevalue2[] = { 0, 0, 0};

float sensorToCmScailFactor = ((2.54*244.0)/512.0);
int sensorValues[] = {0,0,0};

long lastStateChangeMillis = 0;

uint8_t stateLeft = 0; 
uint8_t stateRight = 0;











