//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
String echo = "";
boolean rXend = false;

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  
  while (SerialBT.available() > 0 && !rXend) {
  //read each byte of data in one by one from the buffer and append to the acho string
    char inChar = (char) SerialBT.read();
      echo += inChar;
	  //check for carriage return to signify end of transmission
      if(inChar == '\n'){
        rXend = true;
		//print to connected port via usb
        Serial.print(echo);
        delay(20);
		//echo the received transmission back to the sender on the same port
        SerialBT.print(echo);
		//ensure that the buffers are now empty
        Serial.flush();
       SerialBT.flush();
       echo = "";
      }
      
  }
  
  delay(1000);
  rXend = false;
}
