#ifndef __RADIO_CONFIG_H__
#define __RADIO_CONFIG_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
  uint8_t lflen;
  uint8_t s0len;
  uint8_t s1len;
  uint8_t s1incl;
  uint8_t cilen;
  uint8_t plen;
  uint8_t crcinc;
  uint8_t termlen;
  uint8_t maxlen;
  uint8_t statlen;
  uint8_t balen;
  uint8_t endian;
  uint8_t whiteen;
} RC_PacketConfig_t;

typedef struct
{
  uint8_t len;
  uint8_t skipaddr;
  uint32_t poly;
  uint32_t init;
} RC_CrcConfig_t;

typedef struct
{
  uint8_t mode;
  uint8_t cteinlinectrlen;
  uint8_t cteinfoins1;
  uint8_t cteerrorhandling;
  uint8_t ctetimevalidrange;
  uint8_t cteinlinerxmode1us;
  uint8_t cteinlinerxmode2us;
  uint8_t s0conf;
  uint8_t s0mask;
  uint8_t numberof8us;
  uint8_t dfeinextension;
  uint8_t tswitchspacing;
  uint8_t tsamplespacingref;
  uint8_t sampletype;
  uint8_t tsamplespacing;
  uint8_t repeatpattern;
  uint8_t agcbackoffgain;
  uint16_t tswitchoffset;
  uint16_t tsampleoffset;
  uint32_t * ptr;
  uint16_t maxcnt;
} RC_DfeConfig_t;

typedef enum
{
  radioStateDisabled = 0,
  radioStateRxRu = 1,
  radioStateRxIdle = 2,
  radioStateRx = 3,
  radioStateRxDisable = 4,
  radioStateTxRu = 9,
  radioStateTxIdle = 10,
  radioStateTx = 11,
  radioStateTxDisable = 12
} RC_State_t;

void RC_taskTxEn(void);
void RC_taskRxEn(void);
void RC_taskStart(void);
void RC_taskStop(void);
void RC_taskDisable(void);
void RC_taskRssiStart(void);
void RC_taskRssiStop(void);
void RC_taskBcStart(void);
void RC_taskBcStop(void);
void RC_taskEdStart(void);
void RC_taskEdStop(void);
void RC_taskCcaStart(void);
void RC_taskCcaStop(void);

bool RC_eventIsReady(void);
bool RC_eventAddress(void);
bool RC_eventPayload(void);
bool RC_eventEnd(void);
bool RC_eventDisabled(void);
bool RC_eventDevMatch(void);
bool RC_eventDevMiss(void);
bool RC_eventRssiEnd(void);
bool RC_eventBcMatch(void);
bool RC_eventCrcOk(void);
bool RC_eventCrcError(void);
bool RC_eventFrameStart(void);
bool RC_eventEdEnd(void);
bool RC_eventEdStopped(void);
bool RC_eventCcaIdle(void);
bool RC_eventCcaBusy(void);
bool RC_eventCcaStopped(void);
bool RC_eventRateBoost(void);
bool RC_eventTxReady(void);
bool RC_eventRxReady(void);
bool RC_eventMhrMatch(void);
bool RC_eventSync(void);
bool RC_eventPhyEnd(void);
bool RC_eventCtePresent(void);

uint16_t RC_dfeAmount(void);
RC_State_t RC_state(void);

void RC_reset(void);
void RC_disableInterrupts(void);
bool RC_crcOk(void);
bool RC_dfePending(void);
void RC_setPacketPtr(uint8_t * base_address);
void RC_setFrequency(uint16_t freq_mhz);
void RC_setTxPower(int8_t power_dbm);
void RC_setMode(uint8_t mode);
void RC_configurePacket(RC_PacketConfig_t * settings);
void RC_configureAddress(uint32_t base, uint8_t prefix, uint8_t logical_address);
void RC_configureCrc(RC_CrcConfig_t * settings);
void RC_configureDfe(RC_DfeConfig_t * settings);

#endif