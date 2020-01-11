'''
Description: illlustrates using serial read function to read two bytes.

The bytes read are printed in byte format and integer hexadecimal format.
'''

import serial
from time import sleep

portName = '/dev/ttyACM0'

try:
    ''' 
    Construct a serial object with default arguments
    baudrate 9600
    bytesize 8 bits
    parity   None
    stopbits 1
    timeout  None   (read timeout)
    '''
    ser = serial.Serial(portName)
    print ("opened port " + ser.name)

except serial.SerialException:
        raise IOError("Problem connecting to " + portName)

# sleep short time to ensure port is open
sleep(50/1000)

# flush input buffer, discarding all contents
ser.reset_input_buffer()

count = 0
while count < 5:
    # don't try to read unless there are at least 2 bytes waiting
    if(ser.inWaiting() > 1):
        # read will block until 2 bytes are read
        readByte = ser.read(2) 
        #convert string to hex and then hex to decimal int
        val = int(readByte.hex(), base=16)
        print('readByte: ', end = '')
        print(readByte)
        print('val:      ', end='')
        print(val)
        print('')
        count += 1

ser.close()
