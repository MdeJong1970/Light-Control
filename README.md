# Light-Control
New Light Control

This is the first prototype of my own Light Control.

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


The schematic will follow.
First version of the firmware.

Usefull Links:
https://wiki.seeedstudio.com/Seeeduino-XIAO/
