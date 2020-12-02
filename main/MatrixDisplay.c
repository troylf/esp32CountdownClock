/*
 * MatrixDisplay.cpp
 *
 *  Created on: Sep 23, 2020
 *      Author: Troy
 */

#include "MatrixDisplay.h"
#include <string.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Private
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static const u8 charMask = 0x1F;
static const u8 symbolMask = 0xE0;

void MatrixDisp_sendSpiCommand(MatrixDisplay* disp, void* data, u32 sizeInBytes){
	esp_err_t ret;
	spi_transaction_t t;
	memset(&t, 0, sizeof(t));       //Zero out the transaction
	t.length=sizeInBytes*8;
	t.tx_buffer=data;               //The data is the cmd itself
//	t.flags
//	t.user=(void*)0;                //D/C needs to be set to 0
	ret=spi_device_polling_transmit(disp->spi, &t);  //Transmit!
	assert(ret==ESP_OK);            //Should have had no issues.
//  shiftOut(toSend);
}

void MatrixDisp_sendRow(MatrixDisplay* disp, u8 row ){
    if( row > MatrixDisp_numRows ) return;

    u16 numberOfSendingBytes = disp->numDisplays*2;
    u8 toSend[numberOfSendingBytes];

    for(int i=0; i < numberOfSendingBytes/2; i++)
    {
    	toSend[i*2] = row;
    	toSend[(i*2)+1] = disp->buffer[(numberOfSendingBytes/2-1)-i][row-1];
    }

	MatrixDisp_sendSpiCommand(disp, toSend, numberOfSendingBytes);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// public
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MatrixDisp_init(MatrixDisplay* disp, spi_device_handle_t spi, int numberOfDisplays){
  
  *(spi_device_handle_t*)&(disp->spi) = spi;
  *(int*)&(disp->numDisplays) = numberOfDisplays;

  memset(disp->buffer, 0, MatrixDisp_maxDisplays*MatrixDisp_numRows );

  MatrixDisp_sendCommand(disp, MDCommand_scanLimitReg, 0x07);
  MatrixDisp_sendCommand(disp, MDCommand_decodeModeReg, 0x00);  // using an led matrix (not digits)
  MatrixDisp_sendCommand(disp, MDCommand_shutdownReg, 0x01);    // not in shutdown mode
  MatrixDisp_sendCommand(disp, MDCommand_dispTestReg, 0x00);    // no display test
  MatrixDisp_sendCommand(disp, MDCommand_intensityReg, 0x0f & 1);

  for(int i = 0; i<disp->numDisplays; i++){
	  MatrixDisp_sendEmptyCommand(disp);
  }

  for(int i = 0; i<disp->numDisplays; i++){
  	MatrixDisp_sendCommand(disp,2,0);
  }

}

void MatrixDisp_blankScreen(MatrixDisplay* disp){
  for(int section=0; section < MatrixDisp_maxDisplays; section++){
  	for(int row=0; row < MatrixDisp_numRows; row++){
  	  disp->buffer[section][row] = 0;
  	}
  }
  MatrixDisp_sendBuffer(disp);
}

void MatrixDisp_setColon(MatrixDisplay* disp, u8 segmentNumber, bool isOn){
  if(isOn){
  	disp->buffer[segmentNumber][2] = (disp->buffer[segmentNumber][2]&charMask)|(0x40&symbolMask);
  	disp->buffer[segmentNumber][5] = (disp->buffer[segmentNumber][5]&charMask)|(0x40&symbolMask);
  } else {
  	disp->buffer[segmentNumber][2] = (disp->buffer[segmentNumber][2]&charMask)|(0x00&symbolMask);
  	disp->buffer[segmentNumber][5] = (disp->buffer[segmentNumber][5]&charMask)|(0x00&symbolMask);
  }

}

void MatrixDisp_setSegment(MatrixDisplay* disp, u8 segmentNumber, MatrixChar symbol){
  disp->buffer[segmentNumber][0] = (symbol[0]&charMask)|(disp->buffer[segmentNumber][0]&symbolMask);
  disp->buffer[segmentNumber][1] = (symbol[1]&charMask)|(disp->buffer[segmentNumber][1]&symbolMask);
  disp->buffer[segmentNumber][2] = (symbol[2]&charMask)|(disp->buffer[segmentNumber][2]&symbolMask);
  disp->buffer[segmentNumber][3] = (symbol[3]&charMask)|(disp->buffer[segmentNumber][3]&symbolMask);
  disp->buffer[segmentNumber][4] = (symbol[4]&charMask)|(disp->buffer[segmentNumber][4]&symbolMask);
  disp->buffer[segmentNumber][5] = (symbol[5]&charMask)|(disp->buffer[segmentNumber][5]&symbolMask);
  disp->buffer[segmentNumber][6] = (symbol[6]&charMask)|(disp->buffer[segmentNumber][6]&symbolMask);
}

void MatrixDisp_setIntensity(MatrixDisplay* disp, u8 intensity){

	u16 bufferLength = disp->numDisplays*2;
	u8 intensityArray[bufferLength];

	for(int i = bufferLength-1; i >= 1; i=i-2){
		intensityArray[i-1] = MDCommand_intensityReg;
		intensityArray[i] = intensity;
	}

	MatrixDisp_sendSpiCommand(disp, &intensityArray, bufferLength);

}

void MatrixDisp_sendEmptyCommand(MatrixDisplay* disp){
  MatrixDisp_sendCommand(disp, 0,0);
}

void MatrixDisp_sendBuffer(MatrixDisplay* disp){
  MatrixDisp_sendRow(disp, 1);
  MatrixDisp_sendRow(disp, 2);
  MatrixDisp_sendRow(disp, 3);
  MatrixDisp_sendRow(disp, 4);
  MatrixDisp_sendRow(disp, 5);
  MatrixDisp_sendRow(disp, 6);
  MatrixDisp_sendRow(disp, 7);
  MatrixDisp_sendRow(disp, 8);
}

void MatrixDisp_sendCommand(MatrixDisplay* disp, u8 reg, u8 value)
{
	u8 toSend[2] = {reg, value};

	MatrixDisp_sendSpiCommand(disp, toSend, 2);
}


