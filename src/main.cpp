#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "lightFunctions.h"


void setup() {
    Serial.begin(115200);
    initPixels();
}


void loop() {
//    loading();
//    danger();
    loadingInParallel();
}