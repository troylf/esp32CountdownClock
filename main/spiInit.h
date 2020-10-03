/*
 * spiInit.h
 *
 *  Created on: Sep 17, 2020
 *      Author: Troy
 */

#ifndef MAIN_SPIINIT_H_
#define MAIN_SPIINIT_H_

#include "driver/spi_master.h"

void InitSpi(spi_bus_config_t* returnBus, spi_device_interface_config_t* returnconfig);

#endif /* MAIN_SPIINIT_H_ */
