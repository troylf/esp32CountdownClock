/*
 * Countdown.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: Troy
 */

#ifndef MAIN_COUNTDOWN_CPP_
#define MAIN_COUNTDOWN_CPP_

#include "Types.h"

class Countdown{
  public:
    u16 hours;
    u16 minutes;
    u16 seconds;

    Countdown();
	Countdown* operator--(int);
	void decrementByOneSec();
	void decrementByOneMin();
    void decrementByOneHour();
};

#endif /* MAIN_COUNTDOWN_CPP_ */
