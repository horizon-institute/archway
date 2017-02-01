
// This is the animation that plays when someone approches the arch.
// See https://raw.githubusercontent.com/horizon-institute/archway/master/arduino/images/arch_engage_animation.jpg

class EngageAnimation {

  int frameCount;
  int lightsOn; 
  int dalayFrames;
  int ledsOnMin;
  int ledsOnMax;
  int ledsOffMin;
  int ledsOffMax;
    
  public:
  EngageAnimation(float delaySeconds, int onMin, int onMax, int offMin, int offMax) {
    frameCount = 0;  
    lightsOn = 0;
    dalayFrames = delaySeconds * FRAMES_PER_SECOND;

    ledsOnMin = onMin;
    ledsOnMax = onMax;
    ledsOffMin = offMin;
    ledsOffMin = offMax;
  }

  void nextFrame() {
    //turns on all the LED on reset no animation here for now.
  }

  void reset() {
    lightsToBackgroundColor();
    for(int i = ledsOnMin; i < ledsOnMax; i++) {
          leds[i] = FOREGROUND_COLOR;
    }
    lightsOn = ledsOnMax - ledsOnMin; //150;
    frameCount = 0;
  }
};

