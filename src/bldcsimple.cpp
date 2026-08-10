#include <Arduino.h>
#include <Wire.h>
#include <ESP32Servo.h>
Servo ESC1;

void setup() {

    Serial.begin(115200);
    
    //ESC stuff
    ESC1.attach(18, 1000,2000);

}

void loop() {

    ESC1.writeMicroseconds(2000);


}