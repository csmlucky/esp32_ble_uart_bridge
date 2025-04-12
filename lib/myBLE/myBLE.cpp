#include "myBLE.h"

bool deviceConnected = false;
std::string receivedCommand = "";
u_int8_t ble_RX_data[BLE_BUF_SIZE];
volatile bool ble_rxCmd_state = false;


BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pTXCharacteristic;
BLECharacteristic *pRXCharacteristic;

void myBLE_init(const char* str){
    

    // Initialize BLE
    BLEDevice::init(str);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create a Service
    pService = pServer->createService(BLEUUID(SERVICE_UUID));
    /*
    // Create a Characteristic for Sensor Data 
    pTXCharacteristic = pService->createCharacteristic(
        BLEUUID(CHARACTERISTIC_UUID_TX),
        BLECharacteristic::PROPERTY_NOTIFY
    );
    */
    /*
    // Add BLE2902 descriptor (required for iOS)
    BLE2902 *desc = new BLE2902();
    //desc->setIndications(true);  // Enable Notifications
    desc->setNotifications(true);  // Enable Notifications
    pTXCharacteristic->addDescriptor(desc);
    // Set Initial Value
    //pTXCharacteristic->setValue("Hello from Sensor Data!");
    */

    // Create a Characteristic for Sensor Command 
    pRXCharacteristic = pService->createCharacteristic(
        BLEUUID(CHARACTERISTIC_UUID_RX),
        BLECharacteristic::PROPERTY_WRITE_NR | BLECharacteristic::PROPERTY_NOTIFY
    );

    // Add BLE2902 descriptor (required for iOS)
    BLE2902 *desc = new BLE2902();
    //desc->setIndications(true);  // Enable Notifications
    desc->setNotifications(true);  // Enable Notifications
    pRXCharacteristic->addDescriptor(desc);

    pRXCharacteristic->setCallbacks(new MyRXCallbacks());
    

    // Start Service
    pService->start();

    // Start Advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    BLEDevice::startAdvertising();
    Serial.println("Waiting for a client connection...");
}

void sendBLE_TX_data(const char* str){
    //std::string sensorData = std::string("Sensor Value: ") + str;
    //std::string sensorData = str;
    /*
    for (size_t i = 0; str[i] != '\0'; i++) {  // Stop at null terminator
        sensorData += std::to_string(str[i]) + " ";
    }
    */
    
   
    pRXCharacteristic->setValue(str);
    pRXCharacteristic->notify();
    
    
    
    //pTXCharacteristic->setValue(sensorData.c_str());
    /*
    pTXCharacteristic->setValue(str);
    pTXCharacteristic->notify();
    */
    //pTXCharacteristic->indicate();
    Serial.println("BLESent: ");
    Serial.println(str);
    
    //Serial.print("Subscribed Devices: ");
    

    delay(10);

}