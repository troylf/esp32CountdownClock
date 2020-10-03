extern "C" {
	#include "freertos/FreeRTOS.h"
	#include "esp_wifi.h"
	#include "esp_system.h"
	#include "esp_event.h"
	#include "nvs_flash.h"
	#include "driver/spi_master.h"
	#include "driver/gpio.h"
	#include <string.h>
	#include "spiInit.h"
}

#include "MatrixDisplay.h"
#include "MatrixChars.h"

#define LCD_HOST    SPI2_HOST
#define DMA_CHAN    LCD_HOST

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

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

extern "C" void app_main(void)
{
//    nvs_flash_init();
//    tcpip_adapter_init();
//    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
//    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
//    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
//    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
//    wifi_config_t sta_config;
//    strcpy((char *)sta_config.sta.ssid, CONFIG_ESP_WIFI_SSID);
//    strcpy((char *)sta_config.sta.password, CONFIG_ESP_WIFI_PASSWORD);
//    sta_config.sta.bssid_set = false;
//    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
//    ESP_ERROR_CHECK( esp_wifi_start() );
//    ESP_ERROR_CHECK( esp_wifi_connect() );

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

    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    int level = 0;
    int number = 0;
    while (true) {
    	display.setSegment(0, digetToMatrix(number));
    	display.sendBuffer();
    	number++;
    	if( number >= 10)
    	{
    		number=0;
    	}

        gpio_set_level(GPIO_NUM_2, level);
        level = !level;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

