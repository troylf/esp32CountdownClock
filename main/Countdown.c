/*
 * Countdown.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: Troy
 */
#include "Countdown.h"

void Countdown_init(Countdown* clock){
	clock->hours = 0;
	clock->minutes = 0;
	clock->seconds = 0;
}

void Countdown_decrementByOneHour(Countdown* clock){
  if( clock->hours==0 ) return;

  clock->hours--;
}

void Countdown_decrementByOneMin(Countdown* clock){
  if( clock->hours==0 && clock->minutes==0 ) return;

  if( clock->minutes == 0 ){
	  clock->minutes = 59;
	  Countdown_decrementByOneHour(clock);
  } else {
	  clock->minutes--;
  }

}

void Countdown_decrementByOneSec(Countdown* clock){
  if( 
    clock->hours==0 && 
    clock->minutes==0 && 
    clock->seconds==0 
    ) return;

  if( clock->seconds==0 ){
	  clock->seconds = 59;
	  Countdown_decrementByOneMin(clock);
  } else {
    clock->seconds--;
  }

}



