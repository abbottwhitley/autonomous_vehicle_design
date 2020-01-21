'''
    Prints list of connected serial com ports
    Assumes device path is /dev/ttyACM0. Change this to match your system's path.
    Program loops until 5 bytes have been read, then terminates.
    The byte data read is printed.
'''
import serial
import serial.tools.list_ports 


# list all connected serial com ports
ports = list(serial.tools.list_ports.comports())

print("\nPrinting connected serial port list\n")

for p in ports:
    print("device: " + p.device)
    print("device path: " + p.device_path)
    print("description: " + p.description)
    print("manufactuer: " + p.manufacturer)
    print("serial number: " + p.serial_number + '\n')

