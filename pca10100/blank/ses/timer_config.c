#include "timer_config.h"
#include "led_assert.h"
#include "nrf_timer.h"

static NRF_TIMER_Type * _timerAddr(uint8_t timer_num)
{
  assert(0<=timer_num && timer_num<=4);
  return timer_num==0?  NRF_TIMER0 :
         timer_num==1?  NRF_TIMER1 :
         timer_num==2?  NRF_TIMER2 :
         timer_num==3?  NRF_TIMER3 :
       /*timer_num==4?*/NRF_TIMER4;
}

void TIMER_taskStart(uint8_t timer_num)
{
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  timer->TASKS_START = 1;
}

void TIMER_taskStop(uint8_t timer_num)
{
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  timer->TASKS_STOP = 1;
}

void TIMER_taskClear(uint8_t timer_num)
{
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  timer->TASKS_CLEAR = 1;
}

void TIMER_taskCapture(uint8_t timer_num, uint8_t cc_num)
{
  assert(0<=cc_num && cc_num<=5);
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  timer->TASKS_CAPTURE[cc_num];
}

bool TIMER_eventCompare(uint8_t timer_num, uint8_t cc_num)
{
  assert(0<=cc_num && cc_num<=5);
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  if(timer->EVENTS_COMPARE[cc_num] != 0)
  {
    timer->EVENTS_COMPARE[cc_num] = 0;
    return true;
  }
  return false;
}

void TIMER_shortConfigureCompareClear(uint8_t timer_num, uint8_t cc_num, bool en)
{
  assert(0<=cc_num && cc_num<=5);
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  if(en)
    timer->SHORTS |= 1<<cc_num;
  else
    timer->SHORTS &= ~(1<<cc_num);
}

void TIMER_shortConfigureCompareStop(uint8_t timer_num, uint8_t cc_num, bool en)
{
  assert(0<=cc_num && cc_num<=5);
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  if(en)
    timer->SHORTS |= 1<<(cc_num+8);
  else
    timer->SHORTS &= ~(1<<(cc_num+8));
}

void TIMER_intenConfigureCompare(uint8_t timer_num, uint8_t cc_num, bool en)
{
  assert(0<=cc_num && cc_num<=5);
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  if(en)
    timer->INTENSET = 1<<(cc_num+16);
  else
    timer->INTENCLR = 1<<(cc_num+16);
}

void TIMER_configureBitMode(uint8_t timer_num, uint8_t num_bits)
{
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  assert(num_bits==8 || num_bits==16 || num_bits==24 || num_bits==32);
  timer->BITMODE = num_bits==8?   1 :
                   num_bits==16?  0 :
                   num_bits==24?  2 :
                 /*num_bits==32?*/3;
}

void TIMER_configurePrescalar(uint8_t timer_num, uint8_t prescale)
{
  assert(0<=prescale && prescale<=9);
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  timer->PRESCALER = prescale;
}

void TIMER_writeCc(uint8_t timer_num, uint8_t cc_num, uint32_t value)
{
  assert(0<=cc_num && cc_num<=5);
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  timer->CC[cc_num] = value;
}

uint32_t TIMER_readCc(uint8_t timer_num, uint8_t cc_num)
{
  assert(0<=cc_num && cc_num<=5);
  NRF_TIMER_Type * timer = _timerAddr(timer_num);
  return timer->CC[cc_num];
}