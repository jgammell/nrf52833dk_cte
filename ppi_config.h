#ifndef __PPI_CONFIG_H__
#define __PPI_CONFIG_H__

#include <stdint.h>
#include <stdbool.h>

void PPI_channelEnable(uint8_t channel, bool en);

void PPI_setChannelTask(uint8_t channel, void * task);

void PPI_setChannelEvent(uint8_t channel, void * task);

#endif