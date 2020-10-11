extern "C" {
	#include "freertos/FreeRTOS.h"
	#include "esp_wifi.h"
	#include "esp_system.h"
	#include "esp_event.h"
	#include "esp_log.h"
	#include "nvs_flash.h"
	#include "driver/spi_master.h"
	#include "driver/gpio.h"
	#include <string.h>
	#include "spiInit.h"
	#include "Wifi.h"
}

#include "MatrixDisplay.h"
#include "MatrixChars.h"
#include "Countdown.h"

#define LCD_HOST    SPI2_HOST
#define DMA_CHAN    LCD_HOST

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

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
  disp->setSegment(0,DisplayChars.digetToMatrix(minutes));
  disp->setSegment(1,DisplayChars.digetToMatrix(minutes/10));
  disp->setSegment(2,DisplayChars.digetToMatrix(hours));
  disp->setSegment(3,(hours>10)?DisplayChars.digetToMatrix(hours/10):DisplayChars.blank);

  displaySeconds(disp, (countdown->seconds+1)/2);

  disp->sendBuffer();

}

void initNVS(void)
{
	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	  ESP_ERROR_CHECK(nvs_flash_erase());
	  ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
}

extern "C" void app_main(void)
{
	initNVS();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    connectToWifi((char *)"", (char *)"");

	esp_err_t ret;
	spi_device_handle_t spi;
	spi_bus_config_t buscfg;
	spi_device_interface_config_t devcfg;

	InitSpi(&buscfg, &devcfg);

	//Initialize the SPI bus
	ret=spi_bus_initialize(LCD_HOST, &buscfg, DMA_CHAN);
	ESP_ERROR_CHECK(ret);
	//Attach the LCD to the SPI bus
	ret=spi_bus_add_device(LCD_HOST, &devcfg, &spi);
	ESP_ERROR_CHECK(ret);

	MatrixDisplay display = MatrixDisplay(spi, 4);
	display.setColon(1, true);

	Countdown countdown = Countdown();

	countdown.hours=2;

    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    int level = 0;

    while (true) {
    	displayClock(&display, &countdown);

        gpio_set_level(GPIO_NUM_2, level);
        level = !level;
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        countdown--;
    }
}

