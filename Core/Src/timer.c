#include "timer.h"
#include <stdio.h>

Clock_t gameClock = {0, 0, 0};

void Timer_Init(void) {
    gameClock.hour = 0;
    gameClock.minute = 0;
    gameClock.second = 0;
}

void Timer_Update(void) {
    gameClock.second++;

    if (gameClock.second >= 60) {
        gameClock.second = 0;
        gameClock.minute++;
    }

    if (gameClock.minute >= 60) {
        gameClock.minute = 0;
        gameClock.hour++;
    }

    if (gameClock.hour >= 24) {
        gameClock.hour = 0;
    }
}

void Timer_Reset(void) {
    gameClock.hour = 0;
    gameClock.minute = 0;
    gameClock.second = 0;
}
