#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "lightFunctions.h"


void setup() {
    Serial.begin(115200);
    initPixels();
    initClock();
}


void loop() {
//    loading();
//    danger();
//    loadingInParallel();
//    windowsLoading();
//    easeIn(10, 5);
//    elasticAnimation();
//    charging();
    hour();
}