#ifndef __RADIO_H__
#define __RADIO_H__

#include "nrf_radio.h"

#define RADIO_MODE NRF_RADIO_MODE_BLE_1MBIT
#define RADIO_TXPOWER NRF_RADIO_TXPOWER_0DBM
#define RADIO_FREQMHZ 2402
#define RADIO_PACKET_ADRSBASELEN 4 // bytes
#define RADIO_PACKET_ADRSBASE 0xABCDEFAB
#define RADIO_PACKET_ADRSPREF 0xCD
#define RADIO_PACKET_S0LEN   0 // bytes
#define RADIO_PACKET_LENLEN  0 // bits
#define RADIO_PACKET_S1LEN   0 // bits
#define RADIO_PACKET_PLSLEN  1 // bytes
#define RADIO_DFE_MODE 3 // AoA is 3; AoD is 2
#define RADIO_DFE_LEN8US 10
#define RADIO_DFE_INEXTENSION 1
#define RADIO_DFE_TSWITCHSPACING 2 // 2us
#define RADIO_DFE_TSAMPLEREF 1 // 250ns
#define RADIO_DFE_SAMPLETYPE 0 // IQ
#define RADIO_DFE_TSAMPLE 1 // 250ns
#define RADIO_DFE_REPEATPATTERN 0 // do not repeat
#define RADIO_DFE_MAXCNT 128
#define RADIO_DFE_SAMPLEOFFSET 1
#define RADIO_DFE_SWITCHOFFSET 0
#define RADIO_DFE_GUARDPERIODUS 4
#define RADIO_DFE_REFPERIODUS 8


void RADIO_init(void);

void RADIO_transmit_packet(const uint8_t * input, int input_len);

int RADIO_receive_packet(uint8_t * output, int output_len, uint32_t * iq_output);


#endif // __RADIO_H__