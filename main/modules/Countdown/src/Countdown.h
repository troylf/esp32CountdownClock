/*
 * Countdown.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: Troy
 */

#ifndef MAIN_COUNTDOWN_CPP_
#define MAIN_COUNTDOWN_CPP_

#include "Types.h"

typedef struct{
    u16 hours;
    u16 minutes;
    u16 seconds;
} Countdown;


void Countdown_init(Countdown* clock);
void Countdown_decrementByOneSec(Countdown* clock);
void Countdown_decrementByOneMin(Countdown* clock);
void Countdown_decrementByOneHour(Countdown* clock);

#endif /* MAIN_COUNTDOWN_CPP_ */
