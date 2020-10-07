#include "ppi_config.h"
#include "led_assert.h"
#include "nrf_ppi.h"

void PPI_channelEnable(uint8_t channel, bool en)
{
  assert(0<=channel && channel<=31);
  if(en)
    //NRF_PPI->CHENSET = 1<<channel;
    NRF_PPI->CHEN |= 1<<channel;
  else
    NRF_PPI->CHEN &= ~(1<<channel);
    //NRF_PPI->CHENCLR = 1<<channel;
}

void PPI_setChannelTask(uint8_t channel, void * task)
{
  assert(0<=channel && channel<=19);
  NRF_PPI->CH[channel].TEP = (uint32_t)task;
}

void PPI_setChannelEvent(uint8_t channel, void * event)
{
  assert(0<=channel && channel<=19);
  NRF_PPI->CH[channel].EEP = (uint32_t)event;
}