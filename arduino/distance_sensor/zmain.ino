

void setup() {
  // setup serial output
  Serial.begin(9600);
  Serial.println(F("Begin setup() 01/02/2017")); Serial.flush();

  // Setup the LEDs
  FastLED.addLeds<DOTSTAR, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Set the LEDs to show setup() has started
  leds[0] = leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW-1] = leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW] = leds[NUM_LEDS-1] = 0xFF00FF;
  FastLED.show();
  
  //wait for sensors to initalise
  delay(2000);

  //start the chain of range sensors
  pinMode(sensorChainStartPin, OUTPUT);
  digitalWrite(sensorChainStartPin, HIGH);
  delay(5);
  digitalWrite(sensorChainStartPin, LOW);
  digitalWrite(sensorChainStartPin, HIGH);
  delay(5);
  digitalWrite(sensorChainStartPin, LOW);
  updateSensors();

  sensorValues[0] = 0;
  sensorValues[1] = 0;
  sensorValues[2] = 0;

  lastStateChangeMillis = millis();
  Serial.print(F("ArchHeight:"));
  Serial.println(archHeight);

  // Set the LEDs to show setup() has ended
  leds[0] = leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW-1] = leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW] = leds[NUM_LEDS-1] = 0xFF0000;
  FastLED.show();
  delay(1000);

}


int8_t lastStateLeft = -1;
int8_t lastStateRight = -1;
int maxHeight = 0;
int lastHeightSent = 0;

AttractAnimation attractAni(5,25);
MeasuringAnimation measuringAni(0.5);

EngageAnimation engageAniLeft(0, 0, INDEX_OF_FIRST_LED_ON_SECOND_ROW ,INDEX_OF_FIRST_LED_ON_SECOND_ROW, NUM_LEDS);
EngageAnimation engageAniRight(0, INDEX_OF_FIRST_LED_ON_SECOND_ROW, NUM_LEDS, 0, INDEX_OF_FIRST_LED_ON_SECOND_ROW);

ApprocheAnimation approchAniLeft(0, 0, INDEX_OF_FIRST_LED_ON_SECOND_ROW ,INDEX_OF_FIRST_LED_ON_SECOND_ROW, NUM_LEDS);
ApprocheAnimation approchAniRight(0, INDEX_OF_FIRST_LED_ON_SECOND_ROW, NUM_LEDS, 0, INDEX_OF_FIRST_LED_ON_SECOND_ROW);


uint8_t debugFrameCount = 0;
const uint8_t debugLed = INDEX_OF_FIRST_LED_ON_SECOND_ROW;
uint32_t debugColours[] = {0x0000FF, 0xFF00FF, 0xFF0000, 0xFFFF00, 0x00FF00, 0x00FFFF};
const uint8_t numDebugColours = 6;

void loop() {
    
  EVERY_N_MILLISECONDS(sensorTriggerDelay) { triggerSensors(); }
  EVERY_N_MILLISECONDS(sensorReadDelay) { updateSensors(); }
  
  //basicStateDisplay();
  stateDisplay();

  // Test for and display error states:
  if (stateLeft>5) {
    setRightLeds(0x0000FF);
    FastLED.delay(1000);
    stateLeft = 0;
    lastStateLeft = -1;
  }
  if (stateRight>5) {
    setLeftLeds(0x0000FF);
    FastLED.delay(1000);
    stateRight = 0;
    lastStateRight = -1;
  }

  lastStateLeft = stateLeft;
  lastStateRight = stateRight;

  // Un-comment this line to debug the frame rate (it will make a single LED flash a different colour on every frame):
  //leds[debugLed] = debugColours[(++debugFrameCount)%numDebugColours];
  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND);
}

// This method displays state in a much more simple way and can be used to help debug the state change.
void basicStateDisplay(){
  switch(stateLeft) {
    case 0:
      setRightLeds(0xFFFFFF);
    break;
    case 1:
      setRightLeds(0x7F007F);
    break;
    case 2:
      setRightLeds(0xFF0000);
    break;
    case 3: 
      setRightLeds(0x7F7F00);
    break;
    case 4:
      setRightLeds(0x00FF00);
    break;
    case 5:
      setRightLeds(0x007F7F);
    break;
    default: // error
      setRightLeds(0x0000FF);
    break;
  }
  switch(stateRight) {
    case 0:
      setLeftLeds(0xFFFFFF);
      leds[270] = 0xFF0000;
    break;
    case 1:
      setLeftLeds(0x7F007F);
    break;
    case 2:
      setLeftLeds(0xFF0000);
    break;
    case 3: 
      setLeftLeds(0x7F7F00);
    break;
    case 4:
      setLeftLeds(0x00FF00);
    break;
    case 5:
      setLeftLeds(0x007F7F);
    break;
    default: // error
      setLeftLeds(0x0000FF);
    break;
  }
}

void stateDisplay(){

  if(stateRight == 0) {
    switch(stateLeft) {
      case 0:
        if(lastStateLeft != 0 or lastStateRight != 0) {
          attractAni.resetAni();
          Serial.println(F("STATE WAITING"));
        }
        attractAni.nextFrame();
      break;
      case 1:
        //setRightLeds(0xFF00FF);
        
        //update LED lastStateLeftfor attract animation
        if(lastStateLeft != 1) {
          engageAniLeft.reset();
          Serial.println(F("STATELEFT ENGAGEMENT"));  
        } 
        engageAniLeft.nextFrame();
        
      break;
      case 2:
        //setRightLeds(0xFF0000);
        
        if(lastStateLeft != 2) {
          Serial.println(F("STATELEFT APPROACHING"));
          approchAniLeft.reset();  
        } 
        approchAniLeft.nextFrame();
        
      break;
      case 3: 
        //setRightLeds(0xFFFF00);
        
        if(lastStateLeft != 3 and lastStateRight != 4) {
          measuringAni.reset();
          lastHeightSent = 0;
          maxHeight = 0;
        }
        
        maxHeight = max(maxHeight,(archHeight - sensorValues[1]));
        if(lastHeightSent < maxHeight) {
          Serial.print(F("STATELEFT UNDER "));  
          Serial.println(maxHeight+HEIGHT_FUDGE);  
          lastHeightSent = maxHeight;
        }
        measuringAni.nextFrame(LEDsPerCM*maxHeight);
        
      break;
      case 4:
        //setRightLeds(0x00FF00);
        
       if(lastStateLeft != 4) {
          Serial.println(F("STATELEFT LEAVING"));
        }
        
      break;
      case 5:
        //setRightLeds(0x00FFFF);
        
        if(lastStateLeft != 5) {
          Serial.println(F("STATELEFT LEFT"));  
          //measuringAni.reset();
        }
        measuringAni.nextFrame(0);
        
      break;
      default:
      break;
    }
  }

  if(stateLeft == 0) {
    switch(stateRight) {
      case 0:
      break;
      case 1:
        //setLeftLeds(0xFF00FF);
        
        //update LED lastStateLeftfor attract animation
        if(lastStateRight != 1) {
          engageAniRight.reset();
          Serial.println(F("STATERIGHT ENGAGEMENT"));    
        } 
        engageAniRight.nextFrame();
        
      break;
      case 2:
        //setLeftLeds(0xFF0000);
        
        if(lastStateRight != 2) {
          Serial.println(F("STATERIGHT APPROACHING"));  
          approchAniRight.reset();
        }
        approchAniRight.nextFrame();
        
      break;
      case 3: 
        //setLeftLeds(0xFFFF00);
        
        if(lastStateRight != 3 and lastStateRight != 4) {
          measuringAni.reset();
          lastHeightSent = 0;
          maxHeight = 0;
        }
        
        maxHeight = max(maxHeight,(archHeight - sensorValues[1]));
        if(lastHeightSent != maxHeight) {
          Serial.print(F("STATERIGHT UNDER "));  
          Serial.println(maxHeight+HEIGHT_FUDGE);  
          lastHeightSent = maxHeight;
        }
        measuringAni.nextFrame(LEDsPerCM*maxHeight);
        
      break;
      case 4:
        //setLeftLeds(0x00FF00);
        
      if(lastStateRight != 4) {
          Serial.println(F("STATERIGHT LEAVING"));  
        }
        
      break;
      case 5:
        //setLeftLeds(0x00FFFF);
        
      if(lastStateRight != 5) {
          Serial.println(F("STATERIGHT LEFT"));  
        }
       measuringAni.nextFrame(0);
       
      break;
      default:
      break;
    }
  }
  
}

unsigned long secondsSinceLastStateChange() {
    unsigned long currentMillis = millis();
    return (currentMillis - lastStateChangeMillis)/1000.0;
}

//state bounderies
void updateState() {

    int8_t newState = -1;
    if(stateRight == 0) {
      newState = caculateStateLeft();
      if(newState != stateLeft) {
        //Serial.print(F("Updating stateLeft ")); Serial.println(stateLeft); Serial.println(F("->")); Serial.println(newState); Serial.flush();
        stateLeft = newState;
        lastStateChangeMillis =  millis();
      } 
    } 
    if (stateLeft == 0) {
      newState = caculateStateRight();
      if(newState != stateRight) {
        //Serial.print(F("Updating stateRight ")); Serial.println(stateRight); Serial.println(F("->")); Serial.println(newState); Serial.flush();
        stateRight = newState;
        lastStateChangeMillis =  millis();
      } 
    }
  
}

int8_t caculateStateLeft() {

    int8_t stateLeftTmp = stateLeft;
  
    if(secondsSinceLastStateChange() > 4 && stateLeft == 4 && sensorValues[2] > 250) {
      stateLeftTmp = 5; //left
    } else if(secondsSinceLastStateChange() > 2 && stateLeft == 3 && sensorValues[1] >= (archHeight - 70) ) {
      stateLeftTmp = 4; //leaving
    } else if(sensorValues[1] < (archHeight - 70)) {
      stateLeftTmp = 3; //measuring
    } else  if (stateLeft == 1 && sensorValues[0] <= 130) {
      stateLeftTmp = 2; //interacting
    } else if (stateLeft == 0 && sensorValues[0] > 140 && sensorValues[0] <= 280) {
      stateLeftTmp = 1; //approching
    } else if (sensorValues[0] > 305 && stateLeft != 1 && stateLeft != 2 && stateLeft != 3 && stateLeft != 4) {
      stateLeftTmp = 0; //
    } else if ((stateLeft == 1 or stateLeft == 2) and secondsSinceLastStateChange() > 15) {
      stateLeftTmp = 0; //
    }

    return stateLeftTmp;
}

int8_t caculateStateRight() {

    int8_t stateRightTmp = stateRight;
     
    if(secondsSinceLastStateChange() > 4 && stateRight == 4 && sensorValues[0] > 250) {
      stateRightTmp = 5; //left
    } else if(secondsSinceLastStateChange() > 2 && stateRight == 3 && sensorValues[1] >= (archHeight - 70) ) {
      stateRightTmp = 4; //leaving
    } else if(sensorValues[1] < (archHeight - 70)) {
      stateRightTmp = 3; //measuring
    } else  if (stateRight == 1 && sensorValues[2] <= 130) {
      stateRightTmp = 2; //interacting
    } else if (stateRight == 0 && sensorValues[2] > 140 && sensorValues[2] <= 270) {
      stateRightTmp = 1; //approching
    } else if (sensorValues[2] > 310 && stateRight != 1 && stateRight != 2 && stateRight != 3 && stateRight != 4) {
      stateRightTmp = 0; //
    } else if ((stateRight == 1 or stateRight == 2) and secondsSinceLastStateChange() > 15) {
      stateRightTmp = 0; //
    }

    return stateRightTmp;
}





