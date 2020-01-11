'''
    Receives serial data from Arduino.
    Assumes device path is /dev/ttyACM0. Change this to match your system's path.
    Program loops until 5 bytes have been read, then terminates.
    The byte data read is printed.
'''
import serial
import serial.tools.list_ports 

# change the path name to match your system
portName = '/dev/ttyACM0'


# List all connected serial com ports
ports = list(serial.tools.list_ports.comports())

print("Printing port list\n")

for p in ports:
    print("device: " + p.device)
    print("device path: " + p.device_path)
    print("description: " + p.description)
    print("manufactuer: " + p.manufacturer)
    print("serial number: " + p.serial_number + '\n')


''' Construct a serial object with default arguments
    baudrate 9600
    bytesize 8 bits
    parity   None
    stopbits 1
    timeout  None   (read timeout)
'''
ser = serial.Serial(portName)

'''
The else branch below will likely never be reached. If the port failed to open in the
previous statement, the program will have stopped execution and produced an error message.

The is_open check is not required, but provides an example of checking the object's open property
'''
if ser.is_open:
    print ("opened port " + ser.name + '\n')
else: # else condition will likely never be reached
    print ("serial open failed, " + portName)
    exit

# loop a few times to illustrate data received
count = 0
while count < 5:
    # don't try to read unless there are bytes in the receive buffer
    if ser.in_waiting > 0:
        ''' read_until(expected=LF,size=None)

        read until an expected sequence is found('\n' by default),
        the size is exceeded or until timeout occurs. With no timeout
        it will block until the requested number of bytes is read
        '''
        bytesRead = ser.read_until()

        # convert byte string to unicode string, remove leading and trailing whitespace
        serialStr = bytesRead.decode().strip()   # decode default is 'utf-8'

        # convert byte string to int, remove leading and trailing whitespace
        # seems to work without calling strip as we only have trailing whitespace
        val = int(bytesRead.strip())

        # print data types just once
        if count == 0:
            print("Data Types")
            print(type(bytesRead))
            print(type(serialStr))
            print(type(val))
            print('\n')

        # print data in its various forms
        print('bytesRead: ' + str(bytesRead))
        print('unicode:   ' + serialStr)
        print('val:       ' + str(val) + '\n')

        
        count += 1

ser.close()