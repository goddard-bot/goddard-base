## goddard-base
Base station for for BARN's Goddard Bot with Genuine People Personality. Relays UART to SPI.

Manages the frames transmitted to the robot.
The format is:
**B[0-9][0-9][0-9][A-Z]**
The first [0-9] takes in the R value
The second [0-9] takes in the G value
The third [0-9] takes in the B value
[A-Z] takes in a sepecific command based on what we want the robot to do, i.e:
F - Forward
R - Reverse
C - Turn Clockwise
W - Turn Counter-clockwise...
