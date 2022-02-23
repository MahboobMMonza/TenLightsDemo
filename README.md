# Ten Lights Demo Project

## Description

This project is a demo of a simple Arduino project that generates
a some light patterns and allows the user to scroll between the
different patterns. A diagram of the hardware setup is shown in 
[LED_Patterns.png](LED_Patterns.png), while the code is available inside
[TenLights.ino](TenLights/TenLights.ino). This project was completed by me during
Grade 12, and is an example of a fun and safe activity that children
can do to learn about programming and hardware integration with Arduino.

This project can be reconstructed on TinkerCAD to show a virtual
simulation of the product. Instructions on how to do so are
found in [TinkerCAD Reproduction](#tinkercad-reproduction).

## Hardware Specifications

- Arduino Uno R3 (1)
- 100 Ohm resistors (10)
- 10 kOhm resistors (2)
- Single-colour LEDs (40, various colours acceptable)
  - 10, 20, and 30 LEDs are also acceptable
- Pushbuttons (2)
- Wires (28)
  - Amount can vary depending on number of LEDs used
- Circuit breadboard (1)

## Software Specifications

- Programming language: C++
- Arduino IDE version: 1.8.x
  - Compatible with future releases

## TinkerCAD Reproduction

The project can be reproduced on TinkerCAD to show a virtual 
simulation of the final design. Instructions on how to do so with
10 LEDs are below:

1. Login to TinkerCAD
2. Select *Circuits* in the menu on the left of the screen and
select *Create new Circuit*
3. In the right menu sidebar, select *Starters - Arduino* from the
drop-down menu above search bar
4. Select the *Breadboard* starter kit
5. Select *Components - Basic* for the remaining pieces
   1. Take only 10 LEDs instead of the listed 40
6. Place all components in a manner similar to that shown in the 
[hardware setup](LED_Patterns.png).
   1. Place LEDs starting from **row g, column 1** going to the right
   2. Resistors for LED should align vertically with the **Cathode**
      (short) terminal of the LED
   3. Place the top-left pin on **row f, column 24** for the first
   pushbutton, and **row f, column 27** for the second pushbutton
7. To change a resistor's resistance, select the resistor and change
the value specified in the *Resistance* tab on the window that appears
   1. The value should be 10 for 10 kOhms
   2. The value should be 0.1 for 100 Ohms
8. Wire the components as shown in the diagram
   1. The power and ground wires from the Arduino and the ones jumping
   from the bottom end to the top do not need to be wired
   2. Note how the configuration changes from pin 10
      1. Pin 10 goes to the leftmost LED, followed by pin 11 to the
      second leftmost, until pin 13 goes to the fourth LED from the left
   3. Ground and power wires do not need to connect in a straight line,
   just ensure that they are connected to the correct columns for the
   terminals
9. Select *Code* (located on the top-right beside *Start Simulation*) and
select *Text* on the drop-down menu
   1. Selecting the *Code* button again hides the editor
10. Copy the [code](TenLights/TenLights.ino) and paste it into the
text area after clearing any initial text
11. Run the simulation by selecting *Start Simulation* and experiment
with different button presses
    1. To press multiple pushbuttons at once, hold `Shift` while
    selecting which pushbuttons to press
    2. To stop pressing the buttons, hold `Ctrl` (`⌘` on Mac) and
    de-select all pressed buttons
12. LED colours can be modified by selecting the LED and choosing
a colour from the *Color* tab on the window that appears