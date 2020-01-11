# Module 1 - Serial Communication Between Arduino and Another Computer

A robot typically requires data transfer between its computer systems. In our case, the system will consist of an Arduino microcontroller and one other computer. The Arduino and computer are physically connected by a universal serial bus (USB) cable. Data is transferred through the cable.

![Arduino Laptop USB](./images/serialdata.gif "Arduino cabled to Laptop")

[1]: https://www.ladyada.net/images/arduino/serialdata.gif



## What is Serial Communication?

Serial communication is the process of sending data one bit at a time, sequentially, over a communication channel or computer bus.

![Serial Example Transmitting One Bit Each Clock Pulse](./images/50e1ccf1ce395f962b000000.png "Serial Example Transmitting One Bit Each Clock Pulse")

[2]: https://cdn.sparkfun.com/r/700-700/assets/e/5/4/2/a/50e1ccf1ce395f962b000000.png


Serial communication between the Arduino and computer is asynchronous, meaning the devices are not connected by a common clock. It is critical that both devices are configured exactly the same in terms of
- Data bits
- Synchronization bits
- Parity bits
- Baud rate


### Baud Rate and Bit Rate

The bit rate is the number of transmitted bits per second. Baud rate is defined as the number of signal or symbol changes per second. Baud rate differs from bit rate when more than one bit per baud is transmitted. This involves transmitting symbols representing multiple bits in a transmission interval and beyond the scope of this discussion. Just be aware that bit rate and baud rate differ when th number of bits per baud is not 1.

'''
Bit rate = Baud rate x number of bit per baud

Baud rate = bit rate / number of bit per baud

'''


![Bit rate versus baud rate](./images/bitversusbaud.jpg "Bit rate versus baud rate")

[3]: https://i.ytimg.com/vi/8wm0QlbW9cQ/maxresdefault.jpg 

| Bit Rate | Baud Rate |
| --- | --- |
| Number of bits transmitted per second | Number of signal units per second |
| Related to computer efficiency | Related to data transmission |


In summary, the baud rate specifies how fast data is sent over a serial line, expressed in the number of signal units per second. We are concerned with bit rate



## Arduino IDE Serial Monitor

