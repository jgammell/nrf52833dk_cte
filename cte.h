#ifndef __CTE_H__
#define __CTE_H__

#include <stdint.h>
#include <stdbool.h>

void CTE_init(void);

void CTE_transmitPacket(uint8_t c);

bool CTE_receivePacket(void);

uint8_t CTE_getPacketData(uint8_t * dest, uint8_t n);

uint8_t CTE_getIqData(uint32_t * dest, uint8_t n);

#endif