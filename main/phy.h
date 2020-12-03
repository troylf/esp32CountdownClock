#ifndef PHY_H
#define PHY_H

#include "Types.h"

void PHY_init(void);

void PHY_DisplayBus_sendCommand(void* data, u32 sizeInBytes);


#endif