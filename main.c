/**
 * Copyright (c) 2014-2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup nrf_radio_test_example_main main.c
 * @{
 * @ingroup nrf_radio_test_example
 * @brief Radio Test Example application main file.
 *
 * This file contains the source code for a sample application that uses the NRF_RADIO and is controlled through the serial port.
 *
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#include "bsp.h"
#include "nrf.h"
#include "radio_cmd.h"
#include "app_uart.h"
#include "app_error.h"
#include "nordic_common.h"
#include "nrf_drv_clock.h"
#include "nrf_cli.h"
#include "nrf_cli_uart.h"

#include "nrf_radio.h"
#include "nrfx_uart.h"
#include "nrf_gpio.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#if defined(NRF21540_DRIVER_ENABLE) && (NRF21540_DRIVER_ENABLE == 1)
#include "nrf21540.h"
#endif


#include "cte.h"
#include "vcom.h"
#include "led_assert.h"

NRF_CLI_UART_DEF(m_cli_uart_transport, 0, 64, 16);
NRF_CLI_DEF(m_cli_uart,
            "uart_cli:~$ ",
            &m_cli_uart_transport.transport,
            '\r',
            CLI_EXAMPLE_LOG_QUEUE_SIZE);


/**@brief Function for starting a command line interface that works on the UART transport layer.
 */
static void cli_start(void)
{
    ret_code_t ret;

    ret = nrf_cli_start(&m_cli_uart);
    APP_ERROR_CHECK(ret);
}


/**@brief Function for configuring UART for CLI.
 */
static void cli_init(void)
{
    ret_code_t ret;

    nrf_drv_uart_config_t uart_config = NRF_DRV_UART_DEFAULT_CONFIG;

    uart_config.pseltxd = TX_PIN_NUMBER;
    uart_config.pselrxd = RX_PIN_NUMBER;
    uart_config.hwfc    = NRF_UART_HWFC_DISABLED;
    ret                 = nrf_cli_init(&m_cli_uart, &uart_config, true, true, NRF_LOG_SEVERITY_INFO);
    APP_ERROR_CHECK(ret);
}


/**@brief Function for initializing logging.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(app_timer_cnt_get);

    APP_ERROR_CHECK(err_code);
}


/** @brief Function for configuring all peripherals used in this example.
 */
static void clock_init(void)
{
    // Start 64 MHz crystal oscillator.
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART    = 1;

    // Wait for the external oscillator to start up.
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0)
    {
        // Do nothing.
    }
}


/** @brief Function for the main application entry.
 */
int main(void)
{
  bsp_board_init(BSP_INIT_LEDS);
  uint32_t error_code = nrf_drv_clock_init();
  assert(error_code == NRF_SUCCESS);
  error_code = app_timer_init();
  assert(error_code == NRF_SUCCESS);
  clock_init();
  VCOM_init();
  CTE_init();

  uint8_t cmd[16];
  while(1)
  {
    memcpy(cmd, VCOM_readline('\n'), 2);
    if(cmd[0] == (uint8_t)'t')
    {
      char ack_str[64];
      uint8_t payload = (uint8_t)cmd[1];
      sprintf(ack_str, "Transmitting 0x%x.\n", payload);
      VCOM_tx(ack_str, strlen(ack_str));
      CTE_transmitPacket(payload);
      const char success_str[] = "Done transmitting.\n";
      VCOM_tx(success_str, strlen(success_str));
    }
    else if(cmd[0] == (uint8_t)'r')
    {
      const char ack_str[] = "Beginning reception.\n";
      char success_str[64];
      const char failure_str[] = "Packet failed CRC check.\n";
      VCOM_tx(ack_str, strlen(ack_str));
      bool success = CTE_receivePacket();
      if(!success)
      {
        VCOM_tx(failure_str, strlen(failure_str));
        continue;
      }
      uint8_t payload;
      CTE_getPacketData(&payload, 1);
      sprintf(success_str, "Payload: 0x%x.\n", payload);
      VCOM_tx(success_str, strlen(success_str));
      uint32_t iq_samples[128];
      uint8_t n_iq = CTE_getIqData(iq_samples, 128);
      char iq_str[64];
      sprintf(iq_str, "Took %d IQ samples.\n", n_iq);
      VCOM_tx(iq_str, strlen(iq_str));
      for(int i=0; i<n_iq; ++i)
      {
        sprintf(iq_str, "%d;%d\n", (int16_t)(iq_samples[i]&0x0000FFFF), (int16_t)((iq_samples[i]&0xFFFF0000)>>16));
        VCOM_tx(iq_str, strlen(iq_str));
      }
    }
    else
    {
      const char failure_str[] = "Invalid input.\n";
      VCOM_tx(failure_str, strlen(failure_str));
    }
  }

  return 0;
}


/** @} */
