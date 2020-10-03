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

void MatrixDisplay::sendRow( u8 row ){
    if( row > numRows ) return;

    u16 numberOfSendingBytes = numDisplays*2;
    u8 toSend[numberOfSendingBytes];

    for(int i=0; i < numberOfSendingBytes/2; i++)
    {
    	toSend[i*2] = row;
    	toSend[(i*2)+1] = buffer[(numberOfSendingBytes/2-1)-i][row-1];
    }

	sendSpiCommand(toSend, numberOfSendingBytes);
}

void MatrixDisplay::sendSpiCommand(void* data, u32 sizeInBytes){
	esp_err_t ret;
	spi_transaction_t t;
	memset(&t, 0, sizeof(t));       //Zero out the transaction
	t.length=sizeInBytes*8;
	t.tx_buffer=data;               //The data is the cmd itself
//	t.flags
//	t.user=(void*)0;                //D/C needs to be set to 0
	ret=spi_device_polling_transmit(spi, &t);  //Transmit!
	assert(ret==ESP_OK);            //Should have had no issues.
//  shiftOut(toSend);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// public
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MatrixDisplay::MatrixDisplay(spi_device_handle_t spi, int numberOfDisplays)
  :  spi(spi), numDisplays(numberOfDisplays){

  memset(buffer, 0, maxDisplays*numRows );

  sendCommand(scanLimitReg, 0x07);
  sendCommand(decodeModeReg, 0x00);  // using an led matrix (not digits)
  sendCommand(shutdownReg, 0x01);    // not in shutdown mode
  sendCommand(dispTestReg, 0x00);    // no display test
  sendCommand(intensityReg, 0x0f & 1);

  for(int i = 0; i<numDisplays; i++){
	sendEmptyCommand();
  }

  for(int i = 0; i<numDisplays; i++){
  	sendCommand(2,0);
  }


}

void MatrixDisplay::blankScreen(){
  for(int section=0; section<maxDisplays; section++){
	for(int row=0; row<numRows; row++){
	  buffer[section][row] = 0;
	}
  }
  sendBuffer();
}

void MatrixDisplay::setColon(u8 segmentNumber, bool isOn){
  if(isOn){
	buffer[segmentNumber][2] = (buffer[segmentNumber][2]&charMask)|(0x40&symbolMask);
	buffer[segmentNumber][5] = (buffer[segmentNumber][5]&charMask)|(0x40&symbolMask);
  } else {
	buffer[segmentNumber][2] = (buffer[segmentNumber][2]&charMask)|(0x00&symbolMask);
	buffer[segmentNumber][5] = (buffer[segmentNumber][5]&charMask)|(0x00&symbolMask);
  }

}

void MatrixDisplay::setSegment(u8 segmentNumber, MatrixChar symbol){
  buffer[segmentNumber][0] = (symbol[0]&charMask)|(buffer[segmentNumber][0]&symbolMask);
  buffer[segmentNumber][1] = (symbol[1]&charMask)|(buffer[segmentNumber][1]&symbolMask);
  buffer[segmentNumber][2] = (symbol[2]&charMask)|(buffer[segmentNumber][2]&symbolMask);
  buffer[segmentNumber][3] = (symbol[3]&charMask)|(buffer[segmentNumber][3]&symbolMask);
  buffer[segmentNumber][4] = (symbol[4]&charMask)|(buffer[segmentNumber][4]&symbolMask);
  buffer[segmentNumber][5] = (symbol[5]&charMask)|(buffer[segmentNumber][5]&symbolMask);
  buffer[segmentNumber][6] = (symbol[6]&charMask)|(buffer[segmentNumber][6]&symbolMask);
}

void MatrixDisplay::setIntensity(u8 intensity){

	u16 bufferLength = numDisplays*2;
	u8 intensityArray[bufferLength];

	for(int i = bufferLength-1; i >= 1; i=i-2){
		intensityArray[i-1] = intensityReg;
		intensityArray[i] = intensity;
	}

	sendSpiCommand(&intensityArray, bufferLength);

}

void MatrixDisplay::sendEmptyCommand(void){
  sendCommand(0,0);
}

void MatrixDisplay::sendBuffer(void){
  sendRow(1);
  sendRow(2);
  sendRow(3);
  sendRow(4);
  sendRow(5);
  sendRow(6);
  sendRow(7);
  sendRow(8);
}

void MatrixDisplay::sendCommand(u8 reg, u8 value)
{
	u8 toSend[2] = {reg, value};

	sendSpiCommand(toSend, 2);
}


