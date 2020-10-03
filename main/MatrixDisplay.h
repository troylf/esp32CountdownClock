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
extern "C" {
	#include "driver/spi_master.h"
}

class MatrixDisplay{
  private:
    static const int maxDisplays = 8;
    static const u8 charMask = 0x1F;
    static const u8 symbolMask = 0xE0;
    const spi_device_handle_t spi;

    enum command {
      decodeModeReg = 0x09,
      intensityReg = 0x0a,
      scanLimitReg = 0x0b,
      shutdownReg = 0x0c,
      dispTestReg = 0x0f
    };

    void sendRow( u8 row );
    void sendSpiCommand(void* data, u32 sizeInBytes);

  public:
    const int numDisplays;
    static const u8 numRows = 8;
    u8 buffer[maxDisplays][numRows];

    MatrixDisplay(spi_device_handle_t spi, int numberOfDisplays);
    void blankScreen();
    void setColon(u8 segmentNumber, bool isOn);
    void setSegment(u8 segmentNumber, const MatrixChar symbol);
    void setIntensity(u8 intensity);
    void sendEmptyCommand();
    void sendBuffer();
    void sendCommand(u8 reg, u8 value);
};



#endif /* MAIN_MATRIXDISPLAY_H_ */
