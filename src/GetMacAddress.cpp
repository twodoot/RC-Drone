#include <Arduino.h>
#include <WiFi.h>

uint8_t addr[6];

void setup() {
    Serial.begin(9600);
    while(!Serial){delay(10);}
    WiFi.macAddress(addr);
    delay(1000);
    for (int i = 0; i <6; i++) {
        Serial.print("0x");
        if (addr[i]< 0x10) {Serial.print("0");}
        Serial.print(addr[i], HEX);
        if (i < 5) {Serial.print(", ");}
    }

}

void loop() {
    
}