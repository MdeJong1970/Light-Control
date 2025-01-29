# Light-Control
New Light Control

The board and the LEDs are powered by the servo connection.

The LEDs have a common power connection

The current software has the following functions:
- HeadLight, TailLeft & TailRight LEDs on/off, controlled with the LIGHT CRTL SERVO channel
- Blinking of the TurnLeft & TurnRight LEDs, controlled with the STEER SERVO channel
- ReverseLight LEDs switched on when driving backwards, controlled with the SPEED SERVO channel
- the TailLeft & TailRight LEDs are in sync with the TurnLeft & TurnRight

top view of the board
![top view of the board](https://github.com/MdeJong1970/Light-Control/blob/main/Pictures/LightControlTop.png)

bottom view of the board
![bottom view of the board](https://github.com/MdeJong1970/Light-Control/blob/main/Pictures/LightControlBottom.png)

The size is 30mm x 70mm.

## Used components:
- Seeed Studio XIAO SAMD21
- ULN2803A, driver 8 channels for LEDs
- 3 resistors 1K
- 3 resistors 2K
- 2x8 pin header for LEDs
- 1x9 pin header for servos


## LED connection:
- pin D0 - 5mm white HeadLight LEDs
- pin D1 - Reverse - 3mm white LEDs on tail panel
- pin D2 - Left turn signals
- pin D3 - Right turn signals
- pin D4 - Tail lamp Left
- pin D5 - Tail lamp Right
- pin D6 - Break lamp


## Servo connection:
- pin D8  - Forward/Backward channel
- pin D9  - Steering channel
- pin D10 - HeadLight channel 

## Connection of the board

Connection of the board
![Connection of the board](https://github.com/MdeJong1970/Light-Control/blob/main/Pictures/LightControlTop%20-%20Connections.png)

Connection of the LEDs
![Connection of the LEDs](https://github.com/MdeJong1970/Light-Control/blob/main/Pictures/ULN2803A%20connection.webp)

## Small holder for the board

![Small holdder for the board](https://github.com/MdeJong1970/Light-Control/blob/main/Holder/Light-Control-Holder.png)

Designed with OpenSCAD (scad file available), STL file available.

To be used with brass thread inserts M2, outer diameter 3.2 mm, max length 5mm.


The schematic will follow.
First version of the firmware.

Usefull Links:
https://wiki.seeedstudio.com/Seeeduino-XIAO/
