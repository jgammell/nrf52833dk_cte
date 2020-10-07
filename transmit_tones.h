#ifndef __TRANSMIT_TONES_H__
#define __TRANSMIT_TONES_H__


#define TT_MAX_SAMPLES 32

void TT_configureTransmitter(void);

void TT_configureReceiver(void);

void TT_awaitReception(void);

void TT_startTransmission(void);

void TT_getTrialData(int trial_num, uint32_t ** iq_data_rv, uint32_t * time_rv);

#endif