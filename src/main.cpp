#include <Arduino.h>
#include "ledBLINK.h"
#include "myBLE.h"
#include "myUART2.h"

//std::string sensorData = "";


void setup() {
  // put your setup code here, to run once:
 // blue_led_init();
 
  Serial.begin(115200);     //Start serial communication for debugging
  myBLE_init("ESP32-TEST");
  myUART2_init();
  Serial.println ("welcome");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //uart2_rx_polling();
  //send_uart2_TX_data("W\r");
  //delay(1000);
  
  
  //while(!uart2_rx_data_available){}
  if (deviceConnected) {
    //Serial.println("connection enabled");
    if(ble_rxCmd_state){
      ble_rxCmd_state = false;
      send_uart2_TX_data(receivedCommand.c_str());
    }
    uart2_rx_polling();
    if(uart2_rx_data_available){
        uart2_rx_data_available = false;
        Serial.println("before ble sent:");
        Serial.println(uart2_RXsensorData);
        sendBLE_TX_data (uart2_RXsensorData);
    }
    
  }
  

  
}

