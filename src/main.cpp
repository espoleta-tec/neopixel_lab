#include <Wire.h>
#include "Arduino.h"
#include "lightFunctions.h"


void setup() {
    Serial.begin(115200);
    if (!Wire.begin()) {
        Serial.println("Failed to init i2c interface");
    }
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
