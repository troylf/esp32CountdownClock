/*
 * MatrixChars.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: Troy
 */
#include "MatrixChars.h"

const unsigned char * digetToMatrix(int num){
  num = num % 10;
  switch(num){
    case 0:
      return DisplayChars.zero;
    case 1:
      return DisplayChars.one;
    case 2:
      return DisplayChars.two;
    case 3:
      return DisplayChars.three;
    case 4:
      return DisplayChars.four;
    case 5:
      return DisplayChars.five;
    case 6:
      return DisplayChars.six;
    case 7:
      return DisplayChars.seven;
    case 8:
      return DisplayChars.eight;
    case 9:
      return DisplayChars.nine;
    default:
      return DisplayChars.blank;
  }
}



