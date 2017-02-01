
byte readingCount = 0;

void triggerSensors() {
  digitalWrite(sensorChainStartPin, HIGH);
  delay(5);
  digitalWrite(sensorChainStartPin, LOW);
}

void updateSensors() {
  //delay(sensorReadDelay);
  rangevalue0[readingCount] = analogRead(sensor0Pin);
  rangevalue1[readingCount] = analogRead(sensor1Pin);
  rangevalue2[readingCount] = analogRead(sensor2Pin);

  readingCount++; 

  if(readingCount == sensorSmothingWindow) {
    updateSensorReadings();
    readingCount = 0;
  }
}

void updateSensorReadings() {

  rangevalue0[0] = analogRead(sensor0Pin);
  rangevalue1[0] = analogRead(sensor1Pin);
  rangevalue2[0] = analogRead(sensor2Pin);

  //sensorValues[0] = analogRead(sensor0Pin)*sensorToCmScailFactor;
  //sensorValues[1] = analogRead(sensor1Pin)*sensorToCmScailFactor;
  //sensorValues[2] = analogRead(sensor2Pin)*sensorToCmScailFactor;
  
  isort(rangevalue0,sensorSmothingWindow);
  isort(rangevalue1,sensorSmothingWindow);
  isort(rangevalue2,sensorSmothingWindow);
  
  sensorValues[0] = rangevalue0[medianPos]*sensorToCmScailFactor;
  sensorValues[1] = rangevalue1[medianPos]*sensorToCmScailFactor;
  sensorValues[2] = rangevalue2[medianPos]*sensorToCmScailFactor;

  updateState();


  Serial.print(sensorValues[0]);
  Serial.print(F(" , "));
  Serial.print(sensorValues[1]);
  Serial.print(F(" , "));
  Serial.print(sensorValues[2]);
  Serial.print(F(" cm "));
  Serial.print(F(" stateLeft =  "));
  Serial.print(stateLeft, DEC);
  Serial.print(F(" stateRight =  "));
  Serial.println(stateRight, DEC);
  Serial.flush();
  
  
}

//array sort
void isort(int *a, int n){
// *a is an array pointer function
  for (int i = 1; i < n; ++i)
  {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

