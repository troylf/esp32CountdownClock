#include "phy.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/spi_master.h"
#include <string.h>

#define LCD_HOST    SPI2_HOST
#define DMA_CHAN    LCD_HOST

static spi_device_handle_t displayBus;

// Private
static void InitSpi()
{
	spi_bus_config_t buscfg={
		.miso_io_num=-1,
		.mosi_io_num=13,
		.sclk_io_num=14,
		.quadwp_io_num=-1,
		.quadhd_io_num=-1,
		.max_transfer_sz=16*8,
	};
	spi_device_interface_config_t devcfg={
		.command_bits = 0,
		.address_bits = 0,
		.clock_speed_hz=5*1000*1000,       //Clock out at 10 MHz
		.mode=0,                            //SPI mode 0
		.spics_io_num = 12,             	//CS pin
		.queue_size=7,                      //We want to be able to queue 7 transactions at a time
	};

	esp_err_t ret;

	//Initialize the SPI bus
	ret=spi_bus_initialize(LCD_HOST, &buscfg, DMA_CHAN);
	ESP_ERROR_CHECK(ret);
	//Attach the LCD to the SPI bus
	ret=spi_bus_add_device(LCD_HOST, &devcfg, &displayBus);
	ESP_ERROR_CHECK(ret);

}

static void initNVS(void)
{
	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	  ESP_ERROR_CHECK(nvs_flash_erase());
	  ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
}

// Public
void PHY_init(void)
{

	initNVS();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

	InitSpi();
}

void PHY_DisplayBus_sendCommand(void* data, u32 sizeInBytes){
	esp_err_t ret;
	spi_transaction_t t;
	memset(&t, 0, sizeof(t));       //Zero out the transaction
	t.length=sizeInBytes*8;
	t.tx_buffer=data;              
  
	ret=spi_device_polling_transmit(displayBus, &t);  //Transmit!
	assert(ret==ESP_OK);           
}