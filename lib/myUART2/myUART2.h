/*
 * myUART2.h
 *
 *  Created on: Mar 1, 2025
 *      Author: Lakshmi
 */

 #ifndef myUART2_H_
 #define myUART2_H_

#include <Arduino.h>
#include <driver/uart.h>


//#define UART_NUM        UART_NUM_2  // Use UART2
#define TX_PIN          17
#define RX_PIN          16
#define UART2_BUF_SIZE  255        // max Buffer size
#define UART2_BAUD_RATE       9600

//extern uint8_t uart2_RX_Buff[UART2_BUF_SIZE];
//extern u_int8_t uart2_TX_Buff[UART2_BUF_SIZE];
extern char uart2_TX_Buff[UART2_BUF_SIZE];
extern char uart2_RX_Buff[UART2_BUF_SIZE];
extern char uart2_RXsensorData[UART2_BUF_SIZE];
extern volatile bool uart2_rx_data_available;
extern volatile uint8_t uart2_txIndex;
extern volatile uint8_t uart2_rxIndex;
extern volatile uint8_t uart2_txActive;
extern volatile bool uart2_txReady;

void myUART2_init(void);
void send_uart2_TX_data (const char*);
//void IRAM_ATTR onTxInterrupt();
//void IRAM_ATTR onUartRx(void* arg);
//void IRAM_ATTR onUartTx(void* arg);
//void IRAM_ATTR uart_isr_handler(void *arg);
void uart2_rx_polling(void);


 #endif