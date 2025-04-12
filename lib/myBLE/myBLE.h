/*
 * myBLE.h
 *
 *  Created on: Feb 28, 2025
 *      Author: Lakshmi
 */


#ifndef myBLE_H_
#define myBLE_H_

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <BLE2902.h>  // Required for notifications


// Define Service UUID and Characteristic UUID
#define SERVICE_UUID            (uint16_t)0xFFE0
#define CHARACTERISTIC_UUID_TX (uint16_t)0xFFE1
#define CHARACTERISTIC_UUID_RX (uint16_t)0xFFE1
#define BLE_BUF_SIZE    255


/*
#define SERVICE_UUID (uint16_t)0x1234
#define CHARACTERISTIC_UUID_TX (uint16_t)0xabcd
#define CHARACTERISTIC_UUID_RX (uint16_t)0x0987
*/


extern bool deviceConnected;
extern std::string receivedCommand;
extern u_int8_t ble_RX_data[BLE_BUF_SIZE];
extern volatile bool ble_rxCmd_state;

// Callback to track connection status
class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        Serial.println("connection enabled");
        deviceConnected = true;
    }
    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        Serial.println("connection disabled");
        BLEDevice::startAdvertising(); // Restart advertising
    }
};

// callback for rx characteristic
class MyRXCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        receivedCommand = pCharacteristic->getValue();
        sprintf((char *)&ble_RX_data[0], receivedCommand.c_str());
        ble_rxCmd_state = true;
        Serial.print("Received Command: ");
        Serial.println(receivedCommand.c_str());
    }
};

void myBLE_init(const char* );
void sendBLE_TX_data(const char* str);

#endif
