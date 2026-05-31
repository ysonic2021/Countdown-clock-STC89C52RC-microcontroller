# Countdown-clock-STC89C52RC-microcontroller

1. Power-on reset displays 0000 statically.

2. Pressing the center button on the rotary encoder for the first time displays 00:00, minutes 00 flashes seconds; rotating left or right increments the minutes (00-59).

3. Pressing the center button on the rotary encoder for the second time displays 00:XX, hours 00 flashes seconds; rotating left or right increments the hours (00-23), so the maximum timing time is 23 hours and 59 minutes.

4. Pressing the center button on the rotary encoder for the third time displays XX:XX, seconds flash, and countdown begins. The seven-color LEDs light up (self-flashing) to indicate the countdown is in progress. When the countdown ends, 00:00 is displayed, all seconds flash, the seven-color LEDs turn off, and the active buzzer sounds seconds.

5. Pressing the center button on the rotary encoder for the fourth time resets the microcontroller, displays 0000, the buzzer turns off, and the LEDs turn off.

(I don't know how to draw Proteus, and besides, there aren't many components.) The TM1637 DIO is connected to P3^4, CLK to P3^5, the rotary encoder's center key to P3^6 + GND, the left and right keys to P3^2, P3^3, and GND, the buzzer to P0^7 (P0 is open-drain; 

connecting it to other ports would result in insufficient current for bidirectional operation), and the RGB LED to P2^1. 

As for accuracy, the difference is less than 1 second in 5 minutes; I don't have the patience for further fine-tuning over longer periods.
 

# Support

Thanks [Gekunflex](https://gekunflex.com/) for providing technical support and help for this program. 
