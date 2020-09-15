
#ifndef __VCOM_H__
#define __VCOM_H__

void VCOM_init(void);
void VCOM_tx(const uint8_t *, int);
void VCOM_rx(uint8_t *, int);
uint8_t * VCOM_readline(uint8_t);

#endif // __VCOM_H__