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

void esp_setup(esp_object) {
  esp_object.begin(115200);

  execute("AT+RST\r\n", 5000); // Reset the ESP8266
  
  // Set station mode Operation
  // 1 = Station Mode (STA) Can connect to an AP such as the Wi-Fi network from your house. This allows any device connected to that network to communicate with the module.
  // 2 = Access Point (AP) In AP the Wi-Fi module acts as a Wi-Fi network, or access point (hence the name), allowing other devices to connect to it.
  // 3 = Both
  execute("AT+CWMODE=1\r\n", 5000);

  //Enter your WiFi network's SSID and Password.  Wi-Fi details needs to be inserted in place of 'SSID' and 'PASSWORD'
  execute("AT+CWJAP=\"SSID\",\"PASSWORD\"\r\n", 5000);

  /* The following statement is to assign Static IP Address to ESP8266. 
     The syntax is AT+CIPSTA=<ip>,<gateway>,<netmask>. 
     This will assign a Static IP Address of 192.168.1.98 (in my case) 
     Static IP Address you will be assigning should not be in conflict with any other device in your network 
  */ 

  // Assign Static IP Address
  execute("AT+CIPSTA=\"192.168.1.98\",\"192.168.1.1\",\"255.255.255.0\"\r\n", 3000);
  
  // Checking if IP Address of the ESP8266 was assigned  
  execute("AT+CIFSR\r\n", 5000);
  
  // TCP/UDP connections. Enable or disable multiple connections. 0 = Single, 1 = Multiple
  execute("AT+CIPMUX=1\r\n", 5000);
  
  // Craete or delete server. 0 = delete, 1 = create, port number = 333 (default)
  // A TCP server can only be created when multiple connections are activated (AT+CIPMUX=1). 
  execute("AT+CIPSERVER=1,80\r\n", 5000);
  
}

// Function to send command to ESP8266 through SoftwareSerial communication
String execute(String command, const int timeout)
{
  String response = "";
  esp_serial.print(command);
  long int time = millis();
  
  while ( (time + timeout) > millis()){
    while (esp_serial.available()){
      char c = esp_serial.read();
      response += c;
    }
  } 
  return response;
}   

#endif   /* INCLUDE_ESP_H_ */
