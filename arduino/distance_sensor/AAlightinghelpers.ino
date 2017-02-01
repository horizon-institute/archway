void lightsToBackgroundColor() {
  fill_solid(leds, NUM_LEDS, BACKGROUND_COLOR);
}

void lightsToForgroundColor() {
  fill_solid(leds, NUM_LEDS, FOREGROUND_COLOR);
}

void setAllLeds(uint32_t color) {
  fill_solid(leds, NUM_LEDS, color);
}

void setRightLeds(uint32_t color) {
  fill_solid(leds, INDEX_OF_FIRST_LED_ON_SECOND_ROW, color);
  /*for (int x=0; x<INDEX_OF_FIRST_LED_ON_SECOND_ROW; ++x) {
    leds[x] = color;
  }*/
}

void setLeftLeds(uint32_t color) {
  fill_solid(&leds[INDEX_OF_FIRST_LED_ON_SECOND_ROW], NUM_LEDS-INDEX_OF_FIRST_LED_ON_SECOND_ROW, color);
  /*for (int x=INDEX_OF_FIRST_LED_ON_SECOND_ROW; x<NUM_LEDS; ++x) {
    leds[x] = color;
  }*/
}
