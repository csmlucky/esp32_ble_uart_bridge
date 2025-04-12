#include "ledBLINK.h"

void blue_led_init(){
    
    pinMode(BLUE_LED, OUTPUT);  //set GPIO2 in outputmode
}

void blue_led_blink(u_int16_t delay_time){
    digitalWrite(BLUE_LED,HIGH);
    delay(delay_time);
    digitalWrite(BLUE_LED,LOW);
    delay(delay_time);

}