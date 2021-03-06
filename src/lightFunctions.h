//
// Created by lazaroofarrill on 7/28/21.
//

#ifndef NEOPIXELTESTER_LIGHTFUNCTIONS_H
#define NEOPIXELTESTER_LIGHTFUNCTIONS_H

#include <Adafruit_NeoPixel.h>
#include "colors.h"
#include <bitset>
#include "RTClib.h"


extern Adafruit_NeoPixel pixels;

void initPixels();

void loading();

void loadingInParallel();

void danger();

void windowsLoading();

void easeIn(int laps = 5, int delayConstant = 5);

ulong increasingDelay(int index, int minDelay, float);

uint elasticLength(int index, int min = 2, int max = 5);

void elasticAnimation();

uint32_t darken(uint32_t color, float percent);

void charging();

void initClock();

void hour();

void moonPhase();

#endif //NEOPIXELTESTER_LIGHTFUNCTIONS_H
