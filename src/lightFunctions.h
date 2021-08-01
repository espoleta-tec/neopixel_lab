//
// Created by lazaroofarrill on 7/28/21.
//

#ifndef NEOPIXELTESTER_LIGHTFUNCTIONS_H
#define NEOPIXELTESTER_LIGHTFUNCTIONS_H

extern Adafruit_NeoPixel pixels;

void initPixels();

void loading();

void loadingInParallel();

void danger();

void windowsLoading();

void easeIn(int laps = 5, int delayConstant = 5);

ulong increasingDelay(int index, int minDelay, float constant);

uint elasticLength(int index, int min = 2, int max = 5);

void elasticAnimation();

uint32_t darken(uint32_t color, float percent);

#endif //NEOPIXELTESTER_LIGHTFUNCTIONS_H
