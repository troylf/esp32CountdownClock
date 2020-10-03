/*
 * spiInit.c
 *
 *  Created on: Sep 17, 2020
 *      Author: Troy
 */

#include "spiInit.h"
#include <string.h>

void InitSpi(spi_bus_config_t* returnBus, spi_device_interface_config_t* returnConfig)
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

	memcpy(returnBus, &buscfg, sizeof(buscfg));
	memcpy(returnConfig, &devcfg, sizeof(devcfg));

}


