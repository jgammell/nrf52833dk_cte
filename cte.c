#include "radio_config.h"
#include "cte.h"
#include "led_assert.h"
#include <string.h>

typedef struct
{
  uint32_t data[128];
  uint8_t n_valid;
} _iq_data_t;
typedef struct
{
  uint8_t data[1];
  uint8_t n_valid;
} _packet_t;
static _iq_data_t iq_data = 
{
  .n_valid = 0
};
static _packet_t packet = 
{
  .n_valid = 0
};

void CTE_init(void)
{
  assert(RC_state() == radioStateDisabled);
  RC_reset();
  RC_disableInterrupts();
  RC_setPacketPtr(packet.data);
  RC_setFrequency(2402);
  RC_setTxPower(0);
  RC_setMode(3);
  RC_PacketConfig_t packet_settings = 
  {
    .lflen = 0,
    .s0len = 0,
    .s1len = 0,
    .s1incl = 0,
    .cilen = 0,
    .plen = 1,
    .crcinc = 1,
    .termlen = 0,
    .maxlen = 1,
    .statlen = 1,
    .balen = 4,
    .endian = 0,
    .whiteen = 0
  };
  RC_configurePacket(&packet_settings);
  RC_configureAddress(0x89ABCDEF, 0x67, 0);
  RC_CrcConfig_t crc_settings = 
  {
    .len = 2,
    .skipaddr = 0,
    .poly = 0x11021,
    .init = 0xFFFF
  };
  RC_configureCrc(&crc_settings);
  RC_DfeConfig_t dfe_settings = 
  {
    .mode = 3,
    .cteinlinectrlen = 0,
    .cteinfoins1 = 0,
    .cteerrorhandling = 0,
    .ctetimevalidrange = 0,
    .cteinlinerxmode1us = 1,
    .cteinlinerxmode2us = 1,
    .s0conf = 0,
    .s0mask = 0,
    .numberof8us = 0x3F,
    .dfeinextension = 1,
    .tswitchspacing = 2,
    .tsamplespacingref = 3,
    .sampletype = 0,
    .tsamplespacing = 3,
    .repeatpattern = 0,
    .agcbackoffgain = 0,
    .tswitchoffset = 0,
    .tsampleoffset = 1,
    .ptr = iq_data.data,
    .maxcnt = 128
  };
  RC_configureDfe(&dfe_settings);
}

void CTE_transmitPacket(uint8_t c)
{
  assert(RC_state() == radioStateDisabled);
  assert(!RC_eventTxReady());
  assert(!RC_eventAddress());
  assert(!RC_eventPayload());
  assert(!RC_eventEnd());
  assert(!RC_eventPhyEnd());
  assert(!RC_eventDisabled());
  packet.data[0] = c;
  RC_taskTxEn();
  assert(RC_state() == radioStateTxRu);
  while(!RC_eventTxReady());
  assert(RC_state() == radioStateTxIdle);
  RC_taskStart();
  assert(RC_state() == radioStateTx);
  while(!RC_eventAddress());
  assert(RC_state() == radioStateTx);
  while(!RC_eventPayload());
  assert(RC_state() == radioStateTx);
  while(!RC_eventEnd());
  assert(RC_state() == radioStateTx);
  while(!RC_eventPhyEnd());
  assert(RC_state() == radioStateTxIdle);
  RC_taskDisable();
  assert(RC_state() == radioStateTxDisable);
  while(!RC_eventDisabled());
  assert(RC_state() == radioStateDisabled);
}

bool CTE_receivePacket(void)
{
  assert(RC_state() == radioStateDisabled);
  assert(!RC_eventRxReady());
  assert(!RC_eventAddress());
  assert(!RC_eventPayload());
  assert(!RC_eventEnd());
  assert(!RC_eventPhyEnd());
  assert(!RC_eventDisabled());
  RC_taskRxEn();
  assert(RC_state() == radioStateRxRu);
  while(!RC_eventRxReady());
  assert(RC_state() == radioStateRxIdle);
  RC_taskStart();
  assert(RC_state() == radioStateRx);
  while(!RC_eventAddress());
  assert(RC_state() == radioStateRx);
  while(!RC_eventPayload());
  assert(RC_state() == radioStateRx);
  while(!RC_eventEnd());
  assert(RC_state() == radioStateRx);
  while(!RC_eventPhyEnd());
  assert(RC_state() == radioStateRxIdle);
  RC_taskDisable();
  assert(RC_state() == radioStateRxDisable);
  while(!RC_eventDisabled());
  assert(RC_state() == radioStateDisabled);
  if(!RC_crcOk())
    return false;
  packet.n_valid = 1;
  iq_data.n_valid = RC_dfeAmount();
  return true;
}

uint8_t CTE_getPacketData(uint8_t * dest, uint8_t n)
{
  assert(n > 0);
  assert(dest != 0);
  assert(packet.n_valid > 0);
  if(packet.n_valid < n)
    n = packet.n_valid;
  packet.n_valid -= n;
  memcpy(dest, packet.data, n);
  return n;
}

uint8_t CTE_getIqData(uint32_t * dest, uint8_t n)
{
  assert(n > 0);
  assert(dest != 0);
  assert(iq_data.n_valid > 0);
  if(iq_data.n_valid < n)
    n = iq_data.n_valid;
  iq_data.n_valid -= n;
  memcpy(dest, iq_data.data, 4*n);
  return n;
}