#ifndef __TIMER_CONFIG_H__
#define __TIMER_CONFIG_H__

#include <stdint.h>
#include <stdbool.h>

void TIMER_taskStart(uint8_t timer_num);
void TIMER_taskStop(uint8_t timer_num);
void TIMER_taskClear(uint8_t timer_num);
void TIMER_taskCapture(uint8_t timer_num, uint8_t cc_num);

bool TIMER_eventCompare(uint8_t timer_num, uint8_t cc_num);

void TIMER_shortConfigureCompareClear(uint8_t timer_num, uint8_t cc_num, bool en);
void TIMER_shortConfigureCompareStop(uint8_t timer_num, uint8_t cc_num, bool en);
void TIMER_intenConfigureCompare(uint8_t timer_num, uint8_t cc_num, bool en);
void TIMER_configureBitMode(uint8_t timer_num, uint8_t num_bits);
void TIMER_configurePrescalar(uint8_t timer_num, uint8_t prescale);

void TIMER_writeCc(uint8_t timer_num, uint8_t cc_num, uint32_t value);
uint32_t TIMER_readCc(uint8_t timer_num, uint8_t cc_num);

#endif