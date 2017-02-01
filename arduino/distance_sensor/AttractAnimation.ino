//////////////////////////
//    AttractAnimation
//////////////////////////

// This is the animation that plays when no one is interacting with the arch.
// See https://raw.githubusercontent.com/horizon-institute/archway/master/arduino/images/arch_attract_animation.mp4

class AttractAnimation {
  int minLEDs;
  int maxLEDs;
  int state0min;
  int state0max;
  int frameCount;
  int tmpLightsOn;
  int tmpLightsState;

  uint16_t fireBall1 = 0; 
  uint16_t fireBall2 = 0;
  
  public:
  AttractAnimation(int minLeds, int maxLeds) {
    minLEDs = state0min = minLeds;
    maxLEDs = state0max = maxLeds;
    frameCount = 0;
    tmpLightsOn = 0;
    tmpLightsState = 0;
  }

  void nextFrame() {
      if(tmpLightsOn == state0max) {
        tmpLightsState = 0;
        state0min =  random(minLEDs,maxLEDs/2);
      } else if(tmpLightsOn == state0min) {
        tmpLightsState = 1;
        state0max = random(maxLEDs/2,maxLEDs);
      }

      if(tmpLightsOn == (maxLEDs-3) && fireBall1 <= 10) {
        fireBall1 = INDEX_OF_FIRST_LED_ON_SECOND_ROW - 1 - tmpLightsOn;
        fireBall2 = NUM_LEDS - 1 - tmpLightsOn;  
      }

      if(fireBall1 > (tmpLightsOn-2)) {
        if(frameCount % 2 == 0) {
          if (fireBall1-4 <= 0) { fireBall1 = 4; }
          leds[fireBall1+1] = BACKGROUND_COLOR;
          leds[fireBall1+2] = BACKGROUND_COLOR;
          leds[fireBall1+3] = BACKGROUND_COLOR;
          leds[fireBall1+4] = BACKGROUND_COLOR;
          leds[fireBall1+5] = BACKGROUND_COLOR;
          leds[fireBall1] = FIREBALL_COLOR;
          leds[fireBall1-1] = FIREBALL_COLOR;
          leds[fireBall1-2] = FIREBALL_COLOR;
          leds[fireBall1-3] = FIREBALL_COLOR;
          leds[fireBall1-4] = FIREBALL_COLOR;
          fireBall1--;


          if (fireBall2+5 >= NUM_LEDS) { fireBall2 = NUM_LEDS-6; }
          leds[fireBall2+1] = BACKGROUND_COLOR;
          leds[fireBall2+2] = BACKGROUND_COLOR;
          leds[fireBall2+3] = BACKGROUND_COLOR;
          leds[fireBall2+4] = BACKGROUND_COLOR;
          leds[fireBall2+5] = BACKGROUND_COLOR;
          leds[fireBall2] = FIREBALL_COLOR;
          leds[fireBall2-1] = FIREBALL_COLOR;
          leds[fireBall2-2] = FIREBALL_COLOR;
          leds[fireBall2-3] = FIREBALL_COLOR;
          leds[fireBall2-4] = FIREBALL_COLOR;
          fireBall2--;
          
        }
      } else {
        fireBall1 = 0;
        fireBall2 = 0;
      }
      
      if(frameCount % 6 == 0) {
        if(tmpLightsState == 0) {
            leds[tmpLightsOn] = BACKGROUND_COLOR;
            leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW-1-tmpLightsOn] = BACKGROUND_COLOR;

            leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW+tmpLightsOn] = BACKGROUND_COLOR;
            leds[NUM_LEDS-1-tmpLightsOn] = BACKGROUND_COLOR;
          tmpLightsOn--;
        } else {
          for(int i = 0; i < tmpLightsOn; i++) {
            leds[i] = FOREGROUND_COLOR;
            leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW-1-i] = FOREGROUND_COLOR;
            
            leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW+i] = FOREGROUND_COLOR;
            leds[NUM_LEDS-1-i] = FOREGROUND_COLOR;
          }
          tmpLightsOn++;
        }
      }
 
      frameCount++;
  }

  void resetAni() {
    tmpLightsOn = state0min;
    tmpLightsState = 0;
    lightsToBackgroundColor();
    for(int i=0; i<=state0min;i++) {
      leds[i] = FOREGROUND_COLOR;
      leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW-1-i] = FOREGROUND_COLOR;
      
      leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW+i] = FOREGROUND_COLOR;
      leds[NUM_LEDS-1-i] = FOREGROUND_COLOR;
    }
    frameCount = 0;
  }

};
// END AttractAnimation
