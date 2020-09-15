#include "radio_config.h"
#include "led_assert.h"
#include "nrf_radio.h"

void RC_taskTxEn(void)
{
  NRF_RADIO->TASKS_TXEN = 1;
}

void RC_taskRxEn(void)
{
  NRF_RADIO->TASKS_RXEN = 1;
}

void RC_taskStart(void)
{
  NRF_RADIO->TASKS_START = 1;
}

void RC_taskStop(void)
{
  NRF_RADIO->TASKS_STOP = 1;
}

void RC_taskDisable(void)
{
  NRF_RADIO->TASKS_DISABLE = 1;
}

void RC_taskRssiStart(void)
{
  NRF_RADIO->TASKS_RSSISTART = 1;
}

void RC_taskRssiStop(void)
{
  NRF_RADIO->TASKS_RSSISTOP = 1;
}

void RC_taskBcStart(void)
{
  NRF_RADIO->TASKS_BCSTART = 1;
}

void RC_taskBcStop(void)
{
  NRF_RADIO->TASKS_BCSTOP = 1;
}

void RC_taskEdStart(void)
{
  NRF_RADIO->TASKS_EDSTART = 1;
}

void RC_taskEdStop(void)
{
  NRF_RADIO->TASKS_EDSTOP = 1;
}

void RC_taskCcaStart(void)
{
  NRF_RADIO->TASKS_CCASTART = 1;
}

void RC_taskCcaStop(void)
{
  NRF_RADIO->TASKS_CCASTOP = 1;
}

bool RC_eventIsReady(void)
{
  if(NRF_RADIO->EVENTS_READY != 0)
  {
    NRF_RADIO->EVENTS_READY = 0;
    return true;
  }
  return false;
}

bool RC_eventAddress(void)
{
  if(NRF_RADIO->EVENTS_ADDRESS != 0)
  {
    NRF_RADIO->EVENTS_ADDRESS = 0;
    return true;
  }
  return false;
}

bool RC_eventPayload(void)
{
  if(NRF_RADIO->EVENTS_PAYLOAD != 0)
  {
    NRF_RADIO->EVENTS_PAYLOAD = 0;
    return true;
  }
  return false;
}

bool RC_eventEnd(void)
{
  if(NRF_RADIO->EVENTS_END != 0)
  {
    NRF_RADIO->EVENTS_END = 0;
    return true;
  }
  return false;
}

bool RC_eventDisabled(void)
{
  if(NRF_RADIO->EVENTS_DISABLED != 0)
  {
    NRF_RADIO->EVENTS_DISABLED = 0;
    return true;
  }
  return false;
}

bool RC_eventDevMatch(void)
{
  if(NRF_RADIO->EVENTS_DEVMATCH != 0)
  {
    NRF_RADIO->EVENTS_DEVMATCH = 0;
    return true;
  }
  return false;
}

bool RC_eventDevMiss(void)
{
  if(NRF_RADIO->EVENTS_DEVMISS != 0)
  {
    NRF_RADIO->EVENTS_DEVMISS = 0;
    return true;
  }
  return false;
}

bool RC_eventRssiEnd(void)
{
  if(NRF_RADIO->EVENTS_RSSIEND != 0)
  {
    NRF_RADIO->EVENTS_RSSIEND = 0;
    return true;
  }
  return false;
}

bool RC_eventBcMatch(void)
{
  if(NRF_RADIO->EVENTS_BCMATCH != 0)
  {
    NRF_RADIO->EVENTS_BCMATCH = 0;
    return true;
  }
  return false;
}

bool RC_eventCrcOk(void)
{
  if(NRF_RADIO->EVENTS_CRCOK != 0)
  {
    NRF_RADIO->EVENTS_CRCOK = 0;
    return true;
  }
  return false;
}

bool RC_eventCrcError(void)
{
  if(NRF_RADIO->EVENTS_CRCERROR != 0)
  {
    NRF_RADIO->EVENTS_CRCERROR = 0;
    return true;
  }
  return false;
}

bool RC_eventFrameStart(void)
{
  if(NRF_RADIO->EVENTS_FRAMESTART != 0)
  {
    NRF_RADIO->EVENTS_FRAMESTART = 0;
    return true;
  }
  return false;
}

bool RC_eventEdEnd(void)
{
  if(NRF_RADIO->EVENTS_EDEND != 0)
  {
    NRF_RADIO->EVENTS_EDEND = 0;
    return true;
  }
  return false;
}

bool RC_eventEdStopped(void)
{
  if(NRF_RADIO->EVENTS_EDSTOPPED != 0)
  {
    NRF_RADIO->EVENTS_EDSTOPPED = 0;
    return true;
  }
  return false;
}

bool RC_eventCcaIdle(void)
{
  if(NRF_RADIO->EVENTS_CCAIDLE != 0)
  {
    NRF_RADIO->EVENTS_CCAIDLE = 0;
    return true;
  }
  return false;
}

bool RC_eventCcaBusy(void)
{
  if(NRF_RADIO->EVENTS_CCABUSY != 0)
  {
    NRF_RADIO->EVENTS_CCABUSY = 0;
    return true;
  }
  return false;
}

bool RC_eventCcaStopped(void)
{
  if(NRF_RADIO->EVENTS_CCASTOPPED != 0)
  {
    NRF_RADIO->EVENTS_CCASTOPPED = 0;
    return true;
  }
  return false;
}

bool RC_eventRateBoost(void)
{
  if(NRF_RADIO->EVENTS_RATEBOOST != 0)
  {
    NRF_RADIO->EVENTS_RATEBOOST = 0;
    return true;
  }
  return false;
}

bool RC_eventTxReady(void)
{
  if(NRF_RADIO->EVENTS_TXREADY != 0)
  {
    NRF_RADIO->EVENTS_TXREADY = 0;
    return true;
  }
  return false;
}

bool RC_eventRxReady(void)
{
  if(NRF_RADIO->EVENTS_RXREADY != 0)
  {
    NRF_RADIO->EVENTS_RXREADY = 0;
    return true;
  }
  return false;
}

bool RC_eventMhrMatch(void)
{
  if(NRF_RADIO->EVENTS_MHRMATCH != 0)
  {
    NRF_RADIO->EVENTS_MHRMATCH = 0;
    return true;
  }
  return false;
}

bool RC_eventSync(void)
{
  if(NRF_RADIO->EVENTS_SYNC != 0)
  {
    NRF_RADIO->EVENTS_SYNC = 0;
    return true;
  }
  return false;
}

bool RC_eventPhyEnd(void)
{
  if(NRF_RADIO->EVENTS_PHYEND != 0)
  {
    NRF_RADIO->EVENTS_PHYEND = 0;
    return true;
  }
  return false;
}

bool RC_eventCtePresent(void)
{
  if(NRF_RADIO->EVENTS_CTEPRESENT != 0)
  {
    NRF_RADIO->EVENTS_CTEPRESENT = 0;
    return true;
  }
  return false;
}

uint8_t RC_dfeAmount(void)
{
  return NRF_RADIO->DFEPACKET.AMOUNT;
}

RC_State_t RC_state(void)
{
  return (RC_State_t)NRF_RADIO->STATE;
}

void RC_reset(void)
{
  NRF_RADIO->POWER = 0;
  NRF_RADIO->POWER = 1;
}

void RC_disableInterrupts(void)
{
  NRF_RADIO->INTENSET = 0;
  NRF_RADIO->INTENCLR = 0xFFFFFFFF;
}

bool RC_crcOk(void)
{
  return NRF_RADIO->CRCSTATUS == 1;
}

bool RC_dfePending(void)
{
  return NRF_RADIO->DFESTATUS != 0;
}

void RC_setPacketPtr(uint8_t * base_address)
{
  assert(base_address != 0);
  NRF_RADIO->PACKETPTR = (uint32_t)base_address;
}

void RC_setFrequency(uint16_t freq_mhz)
{
  assert(2400<=freq_mhz && freq_mhz<=2500);
  NRF_RADIO->FREQUENCY = freq_mhz-2400;
}

void RC_setTxPower(int8_t power_dbm)
{
  assert(0<=power_dbm && power_dbm<=8 ||\
         (-40<=power_dbm && power_dbm<=0 && (power_dbm%4 == 0)));
  NRF_RADIO->TXPOWER = power_dbm;
}

void RC_setMode(uint8_t mode)
{
  assert((0<=mode && mode<=6) || mode==15);
  NRF_RADIO->MODE = mode;
}

void RC_configurePacket(RC_PacketConfig_t * settings)
{
  assert(0<=settings->lflen && settings->lflen<=0xF);
  assert(0<=settings->s0len && settings->s0len<=1);
  assert(0<=settings->s1len && settings->s1len<=0xF);
  assert(0<=settings->s1incl && settings->s1incl<=1);
  assert(0<=settings->cilen && settings->cilen<=3);
  assert(0<=settings->plen && settings->plen<=3);
  assert(0<=settings->crcinc && settings->crcinc<=1);
  assert(0<=settings->termlen && settings->termlen<=3);
  assert(2<=settings->balen && settings->balen<=4);
  assert(0<=settings->endian && settings->endian<=1);
  assert(0<=settings->whiteen && settings->whiteen<=1);
  NRF_RADIO->PCNF0 = 0;
  NRF_RADIO->PCNF0 |= (settings->lflen)<<0;
  NRF_RADIO->PCNF0 |= (settings->s0len)<<8;
  NRF_RADIO->PCNF0 |= (settings->s1len)<<16;
  NRF_RADIO->PCNF0 |= (settings->s1incl)<<20;
  NRF_RADIO->PCNF0 |= (settings->cilen)<<22;
  NRF_RADIO->PCNF0 |= (settings->plen)<<24;
  NRF_RADIO->PCNF0 |= (settings->crcinc)<<26;
  NRF_RADIO->PCNF0 |= (settings->termlen)<<29;
  NRF_RADIO->PCNF1 = 0;
  NRF_RADIO->PCNF1 |= (settings->maxlen)<<0;
  NRF_RADIO->PCNF1 |= (settings->statlen)<<8;
  NRF_RADIO->PCNF1 |= (settings->balen)<<16;
  NRF_RADIO->PCNF1 |= (settings->endian)<<24;
  NRF_RADIO->PCNF1 |= (settings->whiteen)<<25;
}

void RC_configureAddress(uint32_t base, uint8_t prefix, uint8_t logical_address)
{
  assert(0<=logical_address && logical_address<=7);
  NRF_RADIO->BASE0 = 0;
  NRF_RADIO->BASE1 = 0;
  NRF_RADIO->PREFIX0 = 0;
  NRF_RADIO->PREFIX1 = 0;
  if(logical_address == 0)
    NRF_RADIO->BASE0 = base;
  else
    NRF_RADIO->BASE1 = base;
  if(0<=logical_address && logical_address<=3)
    NRF_RADIO->PREFIX0 = prefix<<logical_address;
  else
    NRF_RADIO->PREFIX1 = prefix<<(logical_address-4);
  NRF_RADIO->TXADDRESS = logical_address;
  NRF_RADIO->RXADDRESSES = 1<<logical_address;
}

void RC_configureCrc(RC_CrcConfig_t * settings)
{
  assert(0<=settings->len && settings->len<=3);
  assert(0<=settings->skipaddr && settings->skipaddr<=2);
  assert(0<=settings->poly && settings->poly<=0xFFFFFF);
  assert(0<=settings->init && settings->init<=0xFFFFFF);
  NRF_RADIO->CRCCNF = 0;
  NRF_RADIO->CRCCNF |= (settings->len)<<0;
  NRF_RADIO->CRCCNF |= (settings->skipaddr)<<8;
  NRF_RADIO->CRCPOLY = 0;
  NRF_RADIO->CRCPOLY |= settings->poly;
  NRF_RADIO->CRCINIT = 0;
  NRF_RADIO->CRCINIT |= settings->init;
}

void RC_configureDfe(RC_DfeConfig_t * settings)
{
  assert((settings->mode==0 ) || (2<=settings->mode<=3));
  assert(0<=settings->cteinlinectrlen && settings->cteinlinectrlen<=1);
  assert(0<=settings->cteinfoins1 && settings->cteinfoins1<=1);
  assert(0<=settings->cteerrorhandling && settings->cteerrorhandling<=1);
  assert(0<=settings->ctetimevalidrange && settings->ctetimevalidrange<=2);
  assert(1<=settings->cteinlinerxmode1us && settings->cteinlinerxmode1us<=6);
  assert(1<=settings->cteinlinerxmode2us && settings->cteinlinerxmode2us<=6);
  assert(0<=settings->numberof8us && settings->numberof8us<=0x3F);
  assert(0<=settings->dfeinextension && settings->dfeinextension<=1);
  assert(1<=settings->tswitchspacing && settings->tswitchspacing<=3);
  assert(1<=settings->tsamplespacingref && settings->tsamplespacingref<=6);
  assert(0<=settings->sampletype && settings->sampletype<=1);
  assert(1<=settings->tsamplespacing && settings->tsamplespacing<=6);
  assert(0<=settings->repeatpattern && settings->repeatpattern<=0xF);
  assert(0<=settings->agcbackoffgain && settings->agcbackoffgain<=0xF);
  assert(0<=settings->tswitchoffset && settings->tswitchoffset<=0x1FFF);
  assert(0<=settings->tsampleoffset && settings->tsampleoffset<=0xFFF);
  assert(settings->ptr != 0);
  assert(0<=settings->maxcnt && settings->maxcnt<=0x3FFF);
  NRF_RADIO->DFEMODE = 0;
  NRF_RADIO->DFEMODE |= (settings->mode)<<0;
  NRF_RADIO->CTEINLINECONF = 0;
  NRF_RADIO->CTEINLINECONF |= (settings->cteinlinectrlen)<<0;
  NRF_RADIO->CTEINLINECONF |= (settings->cteinfoins1)<<3;
  NRF_RADIO->CTEINLINECONF |= (settings->cteerrorhandling)<<4;
  NRF_RADIO->CTEINLINECONF |= (settings->ctetimevalidrange)<<6;
  NRF_RADIO->CTEINLINECONF |= (settings->cteinlinerxmode1us)<<10;
  NRF_RADIO->CTEINLINECONF |= (settings->cteinlinerxmode2us)<<13;
  NRF_RADIO->CTEINLINECONF |= (settings->s0conf)<<16;
  NRF_RADIO->CTEINLINECONF |= (settings->s0mask)<<24;
  NRF_RADIO->DFECTRL1 = 0;
  NRF_RADIO->DFECTRL1 |= (settings->numberof8us)<<0;
  NRF_RADIO->DFECTRL1 |= (settings->dfeinextension)<<7;
  NRF_RADIO->DFECTRL1 |= (settings->tswitchspacing)<<8;
  NRF_RADIO->DFECTRL1 |= (settings->tsamplespacingref)<<12;
  NRF_RADIO->DFECTRL1 |= (settings->sampletype)<<15;
  NRF_RADIO->DFECTRL1 |= (settings->tsamplespacing)<<16;
  NRF_RADIO->DFECTRL1 |= (settings->repeatpattern)<<20;
  NRF_RADIO->DFECTRL1 |= (settings->agcbackoffgain)<<24;
  NRF_RADIO->DFECTRL2 = 0;
  NRF_RADIO->DFECTRL2 |= (settings->tswitchoffset)<<0;
  NRF_RADIO->DFECTRL2 |= (settings->tsampleoffset)<<16;
  NRF_RADIO->DFEPACKET.PTR = (uint32_t)settings->ptr;
  NRF_RADIO->DFEPACKET.MAXCNT = settings->maxcnt;
}