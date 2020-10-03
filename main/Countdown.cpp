/*
 * Countdown.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: Troy
 */
#include "Countdown.h"

Countdown::Countdown(){
	hours = 0;
	minutes = 0;
	seconds = 0;
}

Countdown* Countdown::operator--(int){
  decrementByOneSec();
  return this;
}

void Countdown::decrementByOneSec(){
  if( hours==0 && minutes==0 && seconds==0 ) return;

  if( seconds==0 ){
	seconds = 59;
	decrementByOneMin();
  } else {
	seconds--;
  }

}

void Countdown::decrementByOneMin(){
  if( hours==0 && minutes==0 ) return;

  if( minutes == 0 ){
	minutes = 59;
	decrementByOneHour();
  } else {
	minutes--;
  }

}

void Countdown::decrementByOneHour(){
  if( hours==0 ) return;

  hours--;
}

