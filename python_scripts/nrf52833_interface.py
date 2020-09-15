#%%
# -*- coding: utf-8 -*-

import serial
import time
from matplotlib import pyplot as plt
import numpy as np
import re

try:
    rx_ser = serial.Serial('COM4', timeout=.1)
    tx_ser = serial.Serial(r'COM5', timeout=.1)
    rx_ser.write(b'r\n')
    response = rx_ser.readline()
    print('RX: ', response.decode('ascii'))
    payload = 0xef
    tx_ser.write(b't'+payload.to_bytes(1, 'little')+b'\n')
    response = tx_ser.readline()
    print('TX: ', response.decode('ascii'))
    assert payload == int(response[15:17], 16)
    response = tx_ser.readline()
    print('TX: ', response.decode('ascii'))
    response = rx_ser.readline()
    print('RX: ', response.decode('ascii'))
    if response == b'Packet failed CRC check.\n':
        assert False
    assert payload == int(response[11:13], 16)
    response = rx_ser.readline()
    print('RX: ', response.decode('ascii'))
    num_iq = int(re.findall(r'\d+', response.decode('ascii'))[0])
    I, Q = [], []
    for n_sample in range(num_iq):
        response = rx_ser.readline()
        values = re.findall(r'[+-]?\d+', response.decode('ascii'))
        i = np.int16(values[0])
        q = np.int16(values[1])
        print('I %d, Q: %d'%(i, q))
        I.append(i)
        Q.append(q)
    I = np.array(I)
    Q = np.array(Q)
    plt.plot(range(num_iq), I, '.', color='blue')
    plt.plot(range(num_iq), Q, '.', color='red')
    plt.figure()
    plt.plot(range(num_iq), np.unwrap(np.arctan2(Q, I)))
    plt.figure()
    plt.plot(I, Q, '.')
finally:
    tx_ser.close()
    rx_ser.close()
    del tx_ser
    del rx_ser