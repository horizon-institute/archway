
// Everything here is commented out so has the effect of just leaving the LEDs that way they were.

class ApprocheAnimation {

  int frameCount;
  int lightsOn; 
  int dalayFrames;
  int ledsOnMin;
  int ledsOnMax;
  int ledsOffMin;
  int ledsOffMax;
    
  public:
  ApprocheAnimation(float delaySeconds, int onMin, int onMax, int offMin, int offMax) {
    frameCount = 0;  
    lightsOn = 0;
    dalayFrames = delaySeconds * FRAMES_PER_SECOND;

    ledsOnMin = onMin;
    ledsOnMax = onMax;
    ledsOffMin = offMin;
    ledsOffMin = offMax;
  }

  void nextFrame() {

      //if(lightsOn > 0 && frameCount >= dalayFrames) {
      //  leds[lightsOn+ledsOnMin] = BACKGROUND_COLOR;
      //  lightsOn--;
      //  leds[lightsOn+ledsOnMin] = BACKGROUND_COLOR;
      //  lightsOn--;
      //}
      //frameCount++;
  }

  void reset() {
    //lightsToBackgroundColor();
    //for(int i = ledsOnMin; i <= ledsOnMax; i++) {
    //      leds[i] = FOREGROUND_COLOR;
    //}
    //lightsOn = 150;
    //frameCount = 0;

    
    //lightsToBackgroundColor();
    //for(int i = 0; i <= 300; i++) {
    //      leds[i] = FOREGROUND_COLOR;
    //}
    //lightsOn = 300;
    //frameCount = 0;
  }
};

