/*
 * esp.h
 *
 *  Created on: Jan 12, 2020
 *      Author: Nithish
 *
 *  References: http://fab.cba.mit.edu/classes/863.14/tutorials/Programming/serialwifi.html

 */

#ifndef INCLUDE_ESP_H_
#define INCLUDE_ESP_H_

#include <SoftwareSerial.h>

void esp_setup(SoftwareSerial esp_object) {
  esp_object.begin(115200);

  execute("AT+RST\r\n", 5000, esp_object); // Reset the ESP8266
  
  // Set station mode Operation
  // 1 = Station Mode (STA) Can connect to an AP such as the Wi-Fi network from your house. This allows any device connected to that network to communicate with the module.
  // 2 = Access Point (AP) In AP the Wi-Fi module acts as a Wi-Fi network, or access point (hence the name), allowing other devices to connect to it.
  // 3 = Both
  execute("AT+CWMODE=1\r\n", 5000, esp_object);

  //Enter your WiFi network's SSID and Password.  Wi-Fi details needs to be inserted in place of 'SSID' and 'PASSWORD'
  execute("AT+CWJAP=\"SSID\",\"PASSWORD\"\r\n", 5000, esp_object);

  // Assign Static IP Address
  execute("AT+CIPSTA=\"172.158.1.21\",\"172.168.1.1\",\"255.255.255.0\"\r\n", 3000, esp_object);
  
  // Checking if IP Address of the ESP8266 was assigned  
  execute("AT+CIFSR\r\n", 5000, esp_object);
  
  // TCP/UDP connections. Enable or disable multiple connections. 0 = Single, 1 = Multiple
  execute("AT+CIPMUX=1\r\n", 5000, esp_object);
  
  // Create or delete server. 0 = delete, 1 = create, port number = 333 (default)
  // A TCP server can only be created when multiple connections are activated (AT+CIPMUX=1). 
  execute("AT+CIPSERVER=1,126\r\n", 5000, esp_object);
  
}

// Function to send command to ESP8266 through SoftwareSerial communication
String execute(String command, const int timeout, SoftwareSerial esp_object)
{
  String response = "";
  esp_object.print(command);
  long int time = millis();
  
  while ( (time + timeout) > millis()){
    while (esp_object.available()){
      char c = esp_object.read();
      response += c;
    }
  } 
  return response;
}   

#endif   /* INCLUDE_ESP_H_ */
