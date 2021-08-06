//
// Created by lazaroofarrill on 7/28/21.
//

#include "lightFunctions.h"


#define PIXEL_PIN 4

#define NUM_PIXELS 16

Adafruit_NeoPixel pixels(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
RTC_DS1307 RTC;


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


ulong increasingDelay(int index, int minDelay, float constant = 1) {
    const int halfway = NUM_PIXELS / 2;

    int dx = abs(halfway - index);
    if (!dx) {
        dx = 1;
    }
    if (!constant) {
        constant = 1;
    }

    return ((float) constant / (float) dx) * (float) minDelay;
}


void windowsLoading() {
    pixels.clear();
    pixels.show();
    const int minDelay = 10;
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, COLOR_ORANGE_PANTONE);
        pixels.show();
        const ulong d = increasingDelay(i, minDelay, 0);
        Serial.println(d);
        delay(d);
    }
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, COLOR_BLACK);
        pixels.show();
        const ulong d = increasingDelay(i, minDelay, 0);
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
    const int minLength = 4, maxLength = 9;
    int baseDelay = 50;
    const float accelerationConstant = 3;
    const uint32_t color = COLOR_WHITE;
    const int tone = 99;

    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.clear();
        for (int j = 0; j < maxLength; j++) {
            const float brightnessPercent = (float) (j + 1) / (float) maxLength * 100 / tone;
            pixels.setPixelColor((NUM_PIXELS + i + j - maxLength) % NUM_PIXELS, darken(color, brightnessPercent));
        }
        pixels.show();
        delay(baseDelay);
    }

    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.clear();
        const int length = elasticLength(i, minLength, maxLength);
        for (int j = 0; j < length; j++) {
            const float brightnessPercent = (float) (j + 1) / (float) length * 100 / tone;
            pixels.setPixelColor((NUM_PIXELS + i + j - length) % NUM_PIXELS,
                                 darken(color, brightnessPercent));
        }
        pixels.show();
        delay(increasingDelay(i, baseDelay, accelerationConstant));
    }

}


/**
 * Lowers hex color brightness
 * @param color base color
 * @param percent Desired brightness percent
 * @return darkened color
 */
uint32_t darken(uint32_t color, float percent) {

    int r = (COLOR_RED & color) >> 16, g = (COLOR_GREEN_COLOR_WHEEL_X11_GREEN & color) >> 8, b = COLOR_BLUE & color;

    r *= percent / 100.0;
    g *= percent / 100.0;
    b *= percent / 100.0;

    uint32_t result = ((uint32_t) r << 16) | ((uint32_t) g << 8) | ((uint32_t) b);
    return result;
}


void charging() {
    pixels.clear();
    pixels.show();
    for (int i = 0; i <= NUM_PIXELS / 2; i++) {
        const int dx = abs(NUM_PIXELS / 2 - i);
        const uint32_t color = darken(COLOR_BLUE, 10);
        pixels.setPixelColor((NUM_PIXELS / 2 - dx) % NUM_PIXELS, color);
        pixels.setPixelColor((NUM_PIXELS / 2 + dx) % NUM_PIXELS, color);
        pixels.show();
        delay(300);
    }
}


void hour() {
    DateTime now = RTC.now();
    int hour = now.hour();
    int minutes = now.minute();

    Serial.print(hour);
    Serial.print(minutes);

    pixels.clear();
    pixels.setPixelColor(hour / 24 * NUM_PIXELS, COLOR_ORANGE_PANTONE);
    pixels.setPixelColor(minutes / 60 * NUM_PIXELS, COLOR_MAGENTA_PANTONE);
    pixels.show();

    delay(1000);
}


void initClock() {
    RTC.begin();
    if (!RTC.isrunning()) {
        Serial.println("RTC is NOT running!");
    }
}


void moonPhase() {
    uint32_t timestamp = RTC.now().unixtime();
}
