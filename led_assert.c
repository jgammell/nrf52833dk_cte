#include "led_assert.h"
#include "bsp.h"

void assert(bool condition)
{
  if(condition == false)
  {
    bsp_board_led_on(BSP_BOARD_LED_0);
    while(1);
  }
}