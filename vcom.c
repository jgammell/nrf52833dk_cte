
#include "nrfx_uart.h"
#include "nrf_gpio.h"
#include "led_assert.h"
#include "pca10100.h"

#define VCOM_RXBUFFER_LEN 64

static nrfx_uart_t vcom_uart = 
{
  .p_reg = NRF_UART0
};

void VCOM_init(void)
{
  nrfx_uart_config_t config = 
  {
    .pseltxd = TX_PIN_NUMBER,
    .pselrxd = RX_PIN_NUMBER,
    .pselcts = CTS_PIN_NUMBER,
    .pselrts = RTS_PIN_NUMBER,
    .p_context = NULL,
    .hwfc = NRF_UART_HWFC_DISABLED,
    .parity = NRF_UART_PARITY_EXCLUDED,
    .baudrate = NRF_UART_BAUDRATE_9600,
    .interrupt_priority = 0
  };
  nrfx_err_t error_info = nrfx_uart_init(&vcom_uart, &config, NULL);
  assert(error_info == NRF_SUCCESS);
}

void VCOM_tx(const uint8_t * data, int length)
{
  assert(!nrfx_uart_tx_in_progress(&vcom_uart));
  nrfx_err_t error_info = nrfx_uart_tx(&vcom_uart, data, length);
  assert(error_info == NRF_SUCCESS);
}

void VCOM_rx(uint8_t * output, int length)
{
  nrfx_uart_rx_enable(&vcom_uart);
  while(!nrfx_uart_rx_ready(&vcom_uart));
  nrfx_err_t error_info = nrfx_uart_rx(&vcom_uart, output, length);
  assert(error_info == NRF_SUCCESS);
}

uint8_t * VCOM_readline(uint8_t end_char)
{
  static uint8_t rx_buffer[VCOM_RXBUFFER_LEN];
  int idx = 0;
  while(1)
  {
    VCOM_rx(rx_buffer+idx, 1);
    if(rx_buffer[idx] == end_char)
      break;
    idx += 1;
    assert(idx < VCOM_RXBUFFER_LEN);
  }
  return rx_buffer;
}