#include "timer.h"
#include <stdio.h>

void Timer_Init(Clock_t* gameClock) {
    gameClock->hour = 0;
    gameClock->minute = 0;
    gameClock->second = 0;
}

void Timer_Update(Clock_t* gameClock) {
    gameClock->second++;

    if (gameClock->second >= 60) {
        gameClock->second = 0;
        gameClock->minute++;
    }

    if (gameClock->minute >= 60) {
        gameClock->minute = 0;
        gameClock->hour++;
    }

    if (gameClock->hour >= 24) {
        gameClock->hour = 0;
    }
}

void Timer_Reset(Clock_t* gameClock) {
    gameClock->hour = 0;
    gameClock->minute = 0;
    gameClock->second = 0;
}
