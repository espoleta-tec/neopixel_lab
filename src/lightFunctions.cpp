//
// Created by lazaroofarrill on 7/28/21.
//

#include <Adafruit_NeoPixel.h>
#include "lightFunctions.h"
#include "colors.h"
#include <bitset>

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
            const int max = 200;
            const int colorValue = max / 3 * j + max / 10;
            pixels.setPixelColor((i + j) % NUM_PIXELS, pixels.Color(0, colorValue, 0));
            pixels.setPixelColor((i + j + NUM_PIXELS / 2) % NUM_PIXELS,
                                 pixels.Color(0, colorValue, 0));
        }
        pixels.show();

        delay(100);
    }
}


ulong increasingDelay(int index, int minDelay) {
    const int halfway = NUM_PIXELS / 2;

    int currentBase = abs(halfway - index);
    if (!currentBase) {
        currentBase = 1;
    }

    return (float) halfway * 1.5 / (float) currentBase * (float) minDelay;
}


void windowsLoading() {
    pixels.clear();
    pixels.show();
    const int minDelay = 10;
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, COLOR_ORANGE);
        pixels.show();
        const ulong d = increasingDelay(i, minDelay);
        Serial.println(d);
        delay(d);
    }
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, COLOR_OFF);
        pixels.show();
        const ulong d = increasingDelay(i, minDelay);
        Serial.println(d);
        delay(d);
    }
    delay(500);
}


void easeIn(int laps, int delayConstant) {
    pixels.clear();
    pixels.show();
    for (int l = 0; l < laps; l++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            pixels.clear();
            for (int j = 0; j < 4; j++) {
                pixels.setPixelColor((i + j) % NUM_PIXELS, COLOR_BLUE);
            }
            pixels.show();
            delay(delayConstant * abs(laps / 2 - l));
        }
    }

    delay(10000);
}


uint elasticLength(int index, int min, int max) {
    const float halfway = NUM_PIXELS / 2;

    float steps = float(max - min) / halfway;


    const int result = min + steps * abs(halfway - index);
    pixels.Color(0, 0, 0);
    return result;
}


void elasticAnimation() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.clear();
        const int length = elasticLength(i, 4, 9);
        for (int j = 0; j < length; j++) {
            const float val = (float) (j + 1) / length * 100;
            pixels.setPixelColor((i + j) % NUM_PIXELS,
                                 darken(COLOR_BLUE, val));
        }
        pixels.show();
        delay(increasingDelay(i, 10));
    }
}


/**
 * Lowers hex color brightness
 * @param color base color
 * @param percent Desired brightness percent
 * @return darkened color
 */
uint32_t darken(uint32_t color, float percent) {

    int r = (COLOR_RED & color) >> 16, g = (COLOR_GREEN & color) >> 8, b = COLOR_BLUE & color;

    r *= percent / 100.0;
    g *= percent / 100.0;
    b *= percent / 100.0;

    uint32_t result = ((uint32_t) r << 16) | ((uint32_t) g << 8) | ((uint32_t) b);
    Serial.printf("%i\t%i\t%i\n", r, g, b);
    Serial.println(percent);
    return result;
}

