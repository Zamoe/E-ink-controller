# E-ink-controller

This project uses an e-ink display, buttons and a rotary encoder to create a dymanic smart-home controller. The board connects to WiFi and uses MQTT to connect to a HomeAssistant instance. The E-ink display shows devices being controlled and their current status and the buttons and encoder are used to control the devices. 

## Hardware 

ESP32 DevKit-v1 as the system MCU.
Display is the waveshare 2.13" E-ink Display.
Rotary Knob is the DF Robot Encoder. 
WS2812 Addressable RGB Led Strip.
8 standard buttons are connected to one GPIO pin, using an analog button array configuration. 

See the schematic file for the wiring diagram:
![alt text](schematic.png)

## Software
The code is constructed using the Arduino IDE with various libraries used for the screen, encoder and buttons. 
