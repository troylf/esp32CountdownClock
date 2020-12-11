/*
 * MatrixChars.h
 *
 *  Created on: Sep 24, 2020
 *      Author: Troy
 */

#ifndef MAIN_MATRIXCHARS_H_
#define MAIN_MATRIXCHARS_H_

#define MATRIXCHAR_LENGTH 7
typedef const unsigned char MatrixChar[MATRIXCHAR_LENGTH];

typedef struct {
	MatrixChar heart;
	MatrixChar one;
	MatrixChar two;
	MatrixChar three;
	MatrixChar four;
	MatrixChar five;
	MatrixChar six;
	MatrixChar seven;
	MatrixChar eight;
	MatrixChar nine;
	MatrixChar zero;
	MatrixChar blank;
} DisplayCharsType;

static const DisplayCharsType DisplayChars = 
{
	.heart =
	{
	  0x66,
	  0xFF,
	  0xFF,
	  0xFF,
	  0x7E,
	  0x3C,
	  0x18
	},

	.one =
	{
	  0x04,
	  0x0C,
	  0x14,
	  0x04,
	  0x04,
	  0x04,
	  0x1F
	},

	.two =
	{
	  0x0E,
	  0x11,
	  0x01,
	  0x02,
	  0x04,
	  0x08,
	  0x1F
	},

	.three =
	{
	  0x0E,
	  0x11,
	  0x01,
	  0x0E,
	  0x01,
	  0x11,
	  0x0E
	},

	.four =
	{
	  0x02,
	  0x06,
	  0x0A,
	  0x12,
	  0x1F,
	  0x02,
	  0x02
	},

	.five =
	{
	  0x1F,
	  0x10,
	  0x1E,
	  0x01,
	  0x01,
	  0x11,
	  0x0E
	},

	.six =
	{
	  0x0E,
	  0x11,
	  0x10,
	  0x1E,
	  0x11,
	  0x11,
	  0x0E
	},

	.seven =
	{
	  0x1F,
	  0x01,
	  0x02,
	  0x04,
	  0x08,
	  0x08,
	  0x08
	},

	.eight =
	{
	  0x0E,
	  0x11,
	  0x11,
	  0x0E,
	  0x11,
	  0x11,
	  0x0E
	},

	.nine =
	{
	  0x0E,
	  0x11,
	  0x11,
	  0b00001111,
	  0x01,
	  0b00010001,
	  0b00001110
	},

	.zero =
	{
	  0x0E,
	  0x11,
	  0x13,
	  0x15,
	  0x19,
	  0x11,
	  0b00001110
	},

	.blank =
	{
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0
	}
};

const unsigned char * digetToMatrix(int num);

#endif /* MAIN_MATRIXCHARS_H_ */
