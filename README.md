# Obstacle Avoidance robot
The task is to build a software for a simple remote control robot with obstacle avoidance. The hardware includes ESP8266, Arduino Uno, two momentary switches.

## To Do List
- [x] Circuit diagram of motors and sensors with UNO
- [x] Pin diagram with ESP8266
- [x] Code to control Motor driver with UNO
- [x] Autonomy node with adruino
- [x] JS to send ESP8266
- [] Documentation

## Hardware Setup

![Circuit](img/schematic.png)

System Architecture
Arduino UNO
ESP8266 setup/ connection diagram
Motor drive 
Switches


## Web Interface
A HTML Client is used to control the robot remotely. Adruino UNO is recieves the command through the network using the ESP8266 module. The HTML client uses a JS backend to transmit the directional command to a static IP corresponding to the ESP8266. To view the Robot Remote Controller, open the teleop.html file in a web browser. 

![UI](img/UI.png)

## Dependencies
Arduino 1.6.1
ESP8266 Arduino Core

