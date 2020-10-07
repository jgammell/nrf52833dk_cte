#include "led_assert.h"
#include "radio_config.h"
#include "ppi_config.h"
#include "timer_config.h"
#include "transmit_tones.h"
#include "nrf_radio.h"
#include "nrf_timer.h"

#define TIMER_NUM 0
#define SAMPLE_PERIOD 1 // 4us
#define TRANSMIT_PERIOD 10000 // 16000 per 1ms
#define PPI_CH 0
#define ADDR_PREAMBLE 0xAB
#define ADDR 0xCDEF

typedef struct
{
  uint32_t iq_data[TT_MAX_SAMPLES];
  uint32_t time;
} _data_t;
_data_t data[40];
uint8_t tx_packet[1] = {0xA5};
uint8_t rx_packet[1];

static void _configureTransmitter(void)
{
  assert(RC_state() == radioStateDisabled);
  RC_reset();
  RC_disableInterrupts();
  RC_setPacketPtr(tx_packet);
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
    .balen = 2,
    .endian = 0,
    .whiteen = 0
  };
  RC_configurePacket(&packet_settings);
  RC_configureAddress(0xCDEF, 0xAB, 0);
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
    .cteerrorhandling = 1,
    .ctetimevalidrange = 0,
    .cteinlinerxmode1us = 1,
    .cteinlinerxmode2us = 1,
    .s0conf = 0,
    .s0mask = 0,
    .numberof8us = 0x10,
    .dfeinextension = 1,
    .tswitchspacing = 2,
    .tsamplespacingref = SAMPLE_PERIOD,
    .sampletype = 0,
    .tsamplespacing = SAMPLE_PERIOD,
    .repeatpattern = 0,
    .agcbackoffgain = 0,
    .tswitchoffset = 0,
    .tsampleoffset = 1,
    .ptr = data[0].iq_data,
    .maxcnt = TT_MAX_SAMPLES
  };
  RC_configureDfe(&dfe_settings);
  assert(RC_state() == radioStateDisabled);
  assert(!RC_eventTxReady());
  assert(!RC_eventAddress());
  assert(!RC_eventPayload());
  assert(!RC_eventEnd());
  assert(!RC_eventPhyEnd());
  assert(!RC_eventDisabled());
  RC_taskTxEn();
  assert(RC_state() == radioStateTxRu);
  TIMER_taskStop(TIMER_NUM);
  TIMER_taskClear(TIMER_NUM);
  TIMER_configureBitMode(TIMER_NUM, 32);
  TIMER_configurePrescalar(TIMER_NUM, 0);
  TIMER_writeCc(TIMER_NUM, 1, TRANSMIT_PERIOD);
  PPI_channelEnable(PPI_CH, true);
  PPI_setChannelTask(PPI_CH, (void *)&(NRF_RADIO->TASKS_START));
  PPI_setChannelEvent(PPI_CH, (void *)&(NRF_TIMER0->EVENTS_COMPARE[1]));
  while(!RC_eventTxReady());
  assert(RC_state() == radioStateTxIdle);
}

void TT_transmitTones(void)
{
  _configureTransmitter();
  TIMER_eventCompare(TIMER_NUM, 1);
  TIMER_taskStart(TIMER_NUM);
  int trial_num = 0;
  while(trial_num < 40)
  {
    assert(!TIMER_eventCompare(TIMER_NUM, 1));
    while(!TIMER_eventCompare(TIMER_NUM, 1));
    //RC_taskStart(); ///
    TIMER_writeCc(TIMER_NUM, 1, (trial_num+2)*TRANSMIT_PERIOD);
    assert(RC_state() == radioStateTx);
    while(!RC_eventAddress());
    assert(RC_state() == radioStateTx);
    while(!RC_eventPayload());
    assert(RC_state() == radioStateTx);
    while(!RC_eventEnd());
    assert(RC_state() == radioStateTx);
    while(!RC_eventPhyEnd());
    assert(RC_state() == radioStateTxIdle);
    trial_num += 1;
    /*RC_taskDisable();
    assert(RC_state() == radioStateTxDisable);
    while(!RC_eventDisabled());
    assert(RC_state() == radioStateDisabled);*/
    RC_setFrequency(2402+2*trial_num);
    /*RC_taskTxEn();
    assert(RC_state() == radioStateTxRu);
    while(!RC_eventTxReady());
    assert(RC_state() == radioStateTxIdle);*/
  }
  RC_taskDisable();
  assert(RC_state() == radioStateTxDisable);
  while(!RC_eventDisabled());
  assert(RC_state() == radioStateDisabled);
}

static void _configureReceiver(void)
{
  assert(RC_state() == radioStateDisabled);
  RC_reset();
  RC_disableInterrupts();
  RC_setPacketPtr(rx_packet);
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
    .balen = 2,
    .endian = 0,
    .whiteen = 0
  };
  RC_configurePacket(&packet_settings);
  RC_configureAddress(0xCDEF, 0xAB, 0);
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
    .cteerrorhandling = 1,
    .ctetimevalidrange = 0,
    .cteinlinerxmode1us = 1,
    .cteinlinerxmode2us = 1,
    .s0conf = 0,
    .s0mask = 0,
    .numberof8us = 0x10,
    .dfeinextension = 1,
    .tswitchspacing = 2,
    .tsamplespacingref = SAMPLE_PERIOD,
    .sampletype = 0,
    .tsamplespacing = SAMPLE_PERIOD,
    .repeatpattern = 0,
    .agcbackoffgain = 0,
    .tswitchoffset = 0,
    .tsampleoffset = 1,
    .ptr = data[0].iq_data,
    .maxcnt = TT_MAX_SAMPLES
  };
  RC_configureDfe(&dfe_settings);
  assert(RC_state() == radioStateDisabled);
  assert(!RC_eventRxReady());
  assert(!RC_eventAddress());
  assert(!RC_eventPayload());
  assert(!RC_eventEnd());
  assert(!RC_eventPhyEnd());
  assert(!RC_eventDisabled());
  RC_taskRxEn();
  assert(RC_state() == radioStateRxRu);
  TIMER_taskStop(TIMER_NUM);
  TIMER_taskClear(TIMER_NUM);
  TIMER_configureBitMode(TIMER_NUM, 32);
  TIMER_configurePrescalar(TIMER_NUM, 0);
  PPI_channelEnable(PPI_CH, true);
  PPI_setChannelTask(PPI_CH, (void *)&(NRF_TIMER0->TASKS_CAPTURE[0]));
  PPI_setChannelEvent(PPI_CH, (void *)&(NRF_RADIO->EVENTS_END));
  while(!RC_eventRxReady());
  assert(RC_state() == radioStateRxIdle);
}

void TT_receiveTones(void)
{
  _configureReceiver();
  TIMER_taskStart(TIMER_NUM);
  int trial_num = 0;
  while(trial_num < 40)
  {
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
    data[trial_num].time = TIMER_readCc(TIMER_NUM, 0);
    trial_num += 1;
    assert(rx_packet[0] == tx_packet[0]);
    rx_packet[0] = ~tx_packet[0];
    /*RC_taskDisable();
    assert(RC_state() == radioStateRxDisable);
    while(!RC_eventDisabled());
    assert(RC_state() == radioStateDisabled);*/
    NRF_RADIO->DFEPACKET.PTR = (uint32_t)(data[trial_num].iq_data);
    RC_setFrequency(2402+2*trial_num);
    /*RC_taskRxEn();
    assert(RC_state() == radioStateRxRu);
    while(!RC_eventRxReady());
    assert(RC_state() == radioStateRxIdle);*/
  }
  RC_taskDisable();
  assert(RC_state() == radioStateRxDisable);
  while(!RC_eventDisabled());
  assert(RC_state() == radioStateDisabled);
}

void TT_getTrialData(int trial_num, uint32_t ** iq_data_rv, uint32_t * time_rv)
{
  *iq_data_rv = data[trial_num].iq_data;
  *time_rv = data[trial_num].time;
}
