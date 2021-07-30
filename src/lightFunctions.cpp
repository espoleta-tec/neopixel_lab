//
// Created by lazaroofarrill on 7/28/21.
//

#include <Adafruit_NeoPixel.h>
#include "lightFunctions.h"
#include "colors.h"

#define PIXEL_PIN 4

#define NUM_PIXELS 16

Adafruit_NeoPixel pixels(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);


void loading() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.clear();
        for (int j = 0; j < 3; j++) {
            pixels.setPixelColor((i + j) % NUM_PIXELS, pixels.Color(0, 0, 100));
        }
        pixels.show();

        delay(100);
    }
}


void danger() {
    const int danger_interval = 500;
    pixels.clear();
    pixels.show();
    delay(danger_interval);
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, COLOR_RED);
    }
    pixels.show();
    delay(danger_interval);
}


void initPixels() {
    pixels.begin();

}


void loadingInParallel() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.clear();
        for (int j = 0; j < 3; j++) {
            const int colorValue = (j + 1) * 255 / 3;
            pixels.setPixelColor((i + j) % NUM_PIXELS, pixels.Color(0, 0, colorValue));
            pixels.setPixelColor((i + j + NUM_PIXELS / 2) % NUM_PIXELS, pixels.Color(0, 0, colorValue));
        }
        pixels.show();

        delay(500);
    }
}

