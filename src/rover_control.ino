/*
 * rover_control.ino
 *
 *  Created on: Jan 12, 2020
 *      Author: Nithish
 *
 *  Reference: https://www.instructables.com/Control-ESP8266-Over-the-Internet-from-Anywhere/
 */

#include <SoftwareSerial.h>
#include "rover.h"
#include "esp.h"

// L293D motor driver connection for motor A
#define motorA_pwm 6 // right PWM control pin (ENA)
#define motorA_in1 8 // right direction control pin (IN1)
#define motorA_in2 7 // right direction control pin (IN2)

// L293D motor driver connection for motor B
#define motorB_pwm 11 // left PWM control pin (ENB)
#define motorB_in3 10 // left direction control pin (IN3)
#define motorB_in4 9 // left direction control pin (IN4)

// Momentary switch pins
#define left_switch 4  // left bumper switch pin
#define right_switch 5 // right bumper switch pin

#define RX 2
#define TX 3

// Serial communication with ESP8266 
SoftwareSerial esp(RX,TX); 

// Configuring Robot motor A and motor B pins (Creating Robot class object)
Rover rover_object(motorA_pwm, motorA_in1, motorA_in2,
               motorB_pwm, motorB_in3, motorB_in4,
               left_switch, right_switch);


void setup() {               
  Serial.begin(9600);
  
  // Runs AT commands to configure and operate the ESP8266 module
  esp_setup(esp);
    
  // Initial rest state of the rover
  rover_object.Stop();
}

void loop() {
  if(esp.available())
  {
    if(esp.find("+IPD,"))
    {
      esp.find("?");
      String data = esp.readStringUntil(' ');
      String remote_command = msg.substring(6);
      delay(100);      
      
      if (remote_command == "forward")
        rover_object.Forward();
      if (remote_command == "reverse")
        rover_object.Backward();
      if (remote_command == "right")
        rover_object.Right();
      if (remote_command == "left")
        rover_object.Left();
      if (remote_command == "stop") 
        rover_object.Stop();
        
      int checkObstacle = rover_object.SwitchStatus();

      switch(checkObstacle) {
        case 0: {  
          rover_object.Stop();
          break;
        }
        case 1: {
          rover_object.Right();
          delay(1000);              // assuming rotating 1 second turns robot by 90 degree    
          break;
        }  
        case 2: {
          rover_object.Left();
          delay(1000);              // assuming rotating 1 second turns robot by 90 degree 
          break;
        }
        default:
          break;
      	}

    }
  }
}
