Pongbox
=======

This is a project that deals with the atmega-powered ping pong game sold by conrad (http://bit.ly/mqiSTQ). We'd like to create more own software that plays around with the leds or uses the board's open ressources like ADC or RS232.
WARNING: We're not responsible for any damages! You should know what you do!


### Introduction

The box consists of

* a pre-soldered pcb with an atmega8, 2 shift registers and 120 leds
* 2 potentiometers
* a battery box
* a matt plastic window (makes the leds glow diffusly)
* 4 little double-sided glue pads (for fixinng the window on the box)
* 2 nice looking knobs for the potentiometers
* some wire (~50cm) which you need for connecting potentiometers with pcb
* 2 pieces of blank wire (for the slot)


What you need:

* a soldering iron
* some solder
* 3 AA batteries
and for tuning operations:
* a 2-row-6pin-header
* isp-programmer with a 6pin-isp-cable
* rs232/ttl-converter (max232 with needed capacitors)


### First steps

First of all you should follow the instructions for soldering the wires.
After that you can decide whether you'd like to use an old 5V battery charger (from mobile phone or something like that). So you might go easy on your batteries. BUT: PLEASE DON'T USE BATTERIES AND CHARGER THE SAME TIME OR BATTERIES MIGHT EXPLODE!!!
Now you can test the original ping pong game that came with the box. Just power up the board and you will see to boards that can be slided up and down by turning the potentiometers. Play it and have a little fun....


### Tuning the game to the pongbox

Yes, the original software is available from our github and you can do whatever you want with your box!
Conrad was nice to us. They left some extra pads. There's the isp-port, 2 adc-pins, both interrupt pins, rx and tx and for those who like to speed up the system - pads for an oscillator.


Marquee
=======

Our first aim was to create a marquee just like you know it from some stores where they show some text massages as advertisment.
What is possible yet:

* Fill in text in source code and output it on the leds.
* Only small letters, fullstop, exclamation mark and question mark.

What will be possible soon:

* Capital letters, numbers. Maybe different, smaller font.
* Regulate text scrolling speed via potentiometer.
* Send text to pongbox via RS232.
* Regulate brightness.

