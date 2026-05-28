#include <Arduino.h>
#include <WiFi.h>

uint8_t addr[6];

void setup() {
    Serial.begin(9600);
    WiFi.macAddress(addr);
    
    for (int i = 0; i <6; i++) {
        if (addr[i]< 0x10) {Serial.print("0");}
        Serial.print(addr[i], HEX);
        if (i < 5) {Serial.print(":");}
    }

}

void main() {

}