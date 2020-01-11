### Arduino Source Code - lesson1.ino

The program serially transmits a count value in the range [0, 255]. 

The println function transmits numbers as characters, appending a new line character to the end.

Example: 
The value 1 is transmitted as '1' '\n'
The value 12 is transmitted as '1' '2' '\n'
The value 203 is transmitted as '2' '0' '3' '\n'

Upload the code to the Arduino.



### python source code - lesson1.py

The program opens the serial connection to the Arduino. The path "/dev/ttyACM0" is hard-coded in the program. If your path differs, change it before running the program.

Run the program by typing `python3 lesson1.py` in a terminal command line.

Study the program and its output. The bytesRead variable shows the list of bytes read and illustrates how to convert the bytes to a unicode string type and an integer type.



### python dependencies
The pyserial module must be installed. 

`sudo apt-get install python3-serial`