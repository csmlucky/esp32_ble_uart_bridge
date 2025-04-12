#include "myUART2.h"


//uint8_t uart2_RX_Buff[UART2_BUF_SIZE];
//uint8_t uart2_TX_Buff[UART2_BUF_SIZE];
char uart2_TX_Buff[UART2_BUF_SIZE];
char uart2_RX_Buff[UART2_BUF_SIZE];
char uart2_RXsensorData[UART2_BUF_SIZE];
volatile bool uart2_rx_data_available = false;
volatile uint8_t uart2_txIndex = 0;
volatile uint8_t uart2_rxIndex = 0;
volatile uint8_t uart2_txActive = 0;
volatile bool uart2_txReady = false;
const char end_char = '\r'; //end char for uart tx


//HardwareSerial mySerial(2); 
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
//QueueHandle_t uart2_rxQueue;


void myUART2_init(void){
    // Initialize UART2
   // mySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

    
    // Configure UART2 interrupt
  uart_config_t uart_config = {
    .baud_rate = 9600,               // Baud rate
    .data_bits = UART_DATA_8_BITS,   // 8 data bits
    .parity = UART_PARITY_DISABLE,   // No parity
    .stop_bits = UART_STOP_BITS_1,   // 1 stop bit
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE // No hardware flow control
  };
  uart_param_config(UART_NUM_2, &uart_config);
  uart_set_pin(UART_NUM_2, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

  // Install the UART driver
  uart_driver_install(UART_NUM_2, UART2_BUF_SIZE, UART2_BUF_SIZE, 0, NULL, 0);

  // Set RX FIFO threshold to 1 byte (fires interrupt for every received byte)
    //uart_set_rx_full_threshold(UART_NUM_2, 1);
    // Set RX timeout to ensure interrupt fires even for single-byte messages
    //uart_set_rx_timeout(UART_NUM_2, 2);

  
  // Register UART interrupt handler
  //uart_isr_register(UART_NUM_2, onUartRx, NULL, ESP_INTR_FLAG_IRAM, NULL);
  //uart_isr_register(UART_NUM_2, uart_isr_handler, NULL, ESP_INTR_FLAG_IRAM, NULL);
  // Enable RX interrupt for UART2
  //uart_enable_rx_intr(UART_NUM_2);

    // Enable UART RX interrupt
  //esp_intr_alloc(ETS_UART2_INTR_SOURCE, ESP_INTR_FLAG_IRAM, onUartRx, NULL, NULL);

  


    Serial.println("UART2 with RX interrupt attached.");


    
}




  void send_uart2_TX_data (const char* txData){
    
    size_t len = strnlen(txData, UART2_BUF_SIZE - 1);
    uart_write_bytes(UART_NUM_2, txData, len);
    //uart_write_bytes(UART_NUM_2, &end_char, 1);  // adding \r
    
    Serial.print("UARTSent: ");
    Serial.println(txData);
  }



    
    
/*
// UART RX Interrupt Handler
void IRAM_ATTR uart_isr_handler(void *arg) {
    char data;
    Serial.print("RX interrupt triggered");
    while (uart_read_bytes(UART_NUM_2, &data, 1, 10 / portTICK_PERIOD_MS) > 0) {  
        if (data == '\r') {  
            uart2_RX_Buff[uart2_rxIndex] = '\0';  // Null-terminate string
            uart2_rx_data_available = true;  
            uart2_rxIndex = 0;  // Reset buffer index
            Serial.println((char*)uart2_RX_Buff);
            return;  // Stop reading further
        } 
        else if (uart2_rxIndex  < UART2_BUF_SIZE - 1) {
            uart2_RX_Buff[uart2_rxIndex ++] = data;  // Store character
        }
    }
}
*/
void uart2_rx_polling(void){
  //uart_flush(UART_NUM_2);  // Flush buffer before reading new data 
  char  data;
  
  while (uart_read_bytes(UART_NUM_2, &data, 1, 10 / portTICK_PERIOD_MS) > 0) {  
    if (data == '\r') {  
        uart2_RX_Buff[uart2_rxIndex ++] = '\r';  // add carriage return
        uart2_RX_Buff[uart2_rxIndex ++] = '\n';  // add carriage return
        uart2_RX_Buff[uart2_rxIndex] = '\0';  // Null-terminate string
        uart2_rx_data_available = true;  
        uart2_rxIndex = 0;  // Reset buffer index
        // Get the actual length of received data
        size_t rx_length = strlen(uart2_RX_Buff);
        // Ensure we do not exceed UART2_BUF_SIZE - 1
        if (rx_length >= UART2_BUF_SIZE) {
          rx_length = UART2_BUF_SIZE - 1;  // Prevent overflow
        }
        memset(uart2_RXsensorData, 0, UART2_BUF_SIZE);
        strncpy(uart2_RXsensorData, uart2_RX_Buff, rx_length);
        // Ensure null termination
        uart2_RXsensorData[rx_length] = '\0';
        Serial.println(uart2_RX_Buff);
        Serial.println(uart2_RXsensorData);
        return;// Stop reading further
    } 
    else if (uart2_rxIndex  < UART2_BUF_SIZE - 1) {
        uart2_RX_Buff[uart2_rxIndex ++] = data;  // Store character
    }
}
  
}