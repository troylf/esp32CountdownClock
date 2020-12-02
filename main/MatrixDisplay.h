/*
 * MatrixDisplay.h
 *
 *  Created on: Sep 23, 2020
 *      Author: Troy
 */

#ifndef MAIN_MATRIXDISPLAY_H_
#define MAIN_MATRIXDISPLAY_H_

#include "Types.h"
#include "MatrixChars.h"
#include "driver/spi_master.h"

#define MatrixDisp_maxDisplays 8
#define MatrixDisp_numRows     8

typedef struct MatrixDisplay{
  const spi_device_handle_t spi;
  const int numDisplays;
  u8 buffer[MatrixDisp_maxDisplays][MatrixDisp_numRows];
} MatrixDisplay;

enum MatrixDisp_command {
  MDCommand_decodeModeReg = 0x09,
  MDCommand_intensityReg = 0x0a,
  MDCommand_scanLimitReg = 0x0b,
  MDCommand_shutdownReg = 0x0c,
  MDCommand_dispTestReg = 0x0f
};

void MatrixDisp_init(MatrixDisplay* disp, spi_device_handle_t spi, int numberOfDisplays);
void MatrixDisp_blankScreen(MatrixDisplay* disp);
void MatrixDisp_setColon(MatrixDisplay* disp, u8 segmentNumber, bool isOn);
void MatrixDisp_setSegment(MatrixDisplay* disp, u8 segmentNumber, const MatrixChar symbol);
void MatrixDisp_setIntensity(MatrixDisplay* disp, u8 intensity);
void MatrixDisp_sendEmptyCommand(MatrixDisplay* disp);
void MatrixDisp_sendBuffer(MatrixDisplay* disp);
void MatrixDisp_sendCommand(MatrixDisplay* disp, u8 reg, u8 value);


#endif /* MAIN_MATRIXDISPLAY_H_ */
