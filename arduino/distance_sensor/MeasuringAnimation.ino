
// This is the animation that plays when someone stands under the arch.
// See https://raw.githubusercontent.com/horizon-institute/archway/master/arduino/images/arch_measure_animation1.mp4 and https://raw.githubusercontent.com/horizon-institute/archway/master/arduino/images/arch_measure_animation2.mp4

class MeasuringAnimation {
  int currentNumLedsOn;
  float numberOFrames;
  int frameCount;
  public:
  MeasuringAnimation(float totalTime) {
    currentNumLedsOn = 0;
    numberOFrames = totalTime*FRAMES_PER_SECOND;
    frameCount = 0;
  }
  
  void nextFrame (int targetNumLeds) {
    frameCount++;
    //if(frameCount < 60) {
    //  return;
    //}
    if(currentNumLedsOn < targetNumLeds) {
      //turn on some leds
      float ledsPerFrame = (targetNumLeds-currentNumLedsOn)/numberOFrames;
      if(ledsPerFrame > 0 && ledsPerFrame < 1) {
        ledsPerFrame = 1.00;
      }
      int stopAtLED = currentNumLedsOn+ledsPerFrame;
      for(int i = currentNumLedsOn; i <= stopAtLED; i++) {
        leds[i] = MEASURING_COLOR;
        leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW-1-i] = MEASURING_COLOR;
        leds[i+INDEX_OF_FIRST_LED_ON_SECOND_ROW] = MEASURING_COLOR;
        leds[NUM_LEDS-1-i] = MEASURING_COLOR;
        currentNumLedsOn = i;
      }
    } else if (currentNumLedsOn > targetNumLeds)  {
      //turn off some leds
      float ledsPerFrame = (currentNumLedsOn-targetNumLeds)/numberOFrames;
      if(ledsPerFrame > 0 && ledsPerFrame < 1) {
        ledsPerFrame = 1.00;
      }
      int stopAtLED = currentNumLedsOn-ledsPerFrame;
      for(int i = currentNumLedsOn; i >= stopAtLED; i--) {
        leds[i] = FOREGROUND_COLOR;
        leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW-1-i] = FOREGROUND_COLOR;
        leds[i+INDEX_OF_FIRST_LED_ON_SECOND_ROW] = FOREGROUND_COLOR;
        leds[NUM_LEDS-1-i] = FOREGROUND_COLOR;
        currentNumLedsOn = i;
      }
    }
  
  }

  void reset() {
    lightsToForgroundColor();
    currentNumLedsOn = 0;
    frameCount = 0;
  }
};

