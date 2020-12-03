#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include <string.h>
#include "Countdown.h"
#include "MatrixDisplay.h"
#include "phy.h"

#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/spi_master.h"

void displaySeconds(MatrixDisplay* disp, int numDots){
  for(int i=0; i < disp->numDisplays; i++){
    disp->buffer[i][7] = 0;
  }

  int dotCount=numDots;
  for(int i=1; i < disp->numDisplays*8; i++){
    if( dotCount>0 ){
      disp->buffer[i/8][7] |= 0x01<<(i%8);
      dotCount--;
    }
  }
}

void displayClock(MatrixDisplay* disp, Countdown* countdown){
  int minutes = countdown->minutes;
  int hours = countdown->hours;
  MatrixDisp_setSegment(disp, 0,digetToMatrix(minutes));
  MatrixDisp_setSegment(disp, 1,digetToMatrix(minutes/10));
  MatrixDisp_setSegment(disp, 2,digetToMatrix(hours));
  MatrixDisp_setSegment(disp, 3,(hours>10)?digetToMatrix(hours/10):DisplayChars.blank);

  displaySeconds(disp, (countdown->seconds+1)/2);

  MatrixDisp_sendBuffer(disp);

}

void app_main(void)
{
	PHY_init();

	MatrixDisplay display;
	MatrixDisp_init(&display, 4);
	MatrixDisp_setColon(&display, 1, true);

	Countdown countdown;
	Countdown_init(&countdown);

	countdown.hours=2;

    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    int level = 0;

    while (true) {
    	displayClock(&display, &countdown);

        gpio_set_level(GPIO_NUM_2, level);
        level = !level;
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        Countdown_decrementByOneSec(&countdown);
    }
}

