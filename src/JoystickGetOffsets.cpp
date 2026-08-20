#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

uint16_t left_y_sum = 0;
uint16_t left_x_sum = 0;
uint16_t right_y_sum = 0;
uint16_t right_x_sum = 0;

void setup() {
  Serial.begin(115200);
  pinMode(4,INPUT);
  pinMode(3,INPUT);
  pinMode(2,INPUT);
  pinMode(1,INPUT);
  pinMode(6,INPUT_PULLUP);
}

void loop() {
    
  for (int i=0; i<10; i++) {
    left_y_sum += analogRead(4);
    left_x_sum += analogRead(3);
    right_y_sum += analogRead(2);
    right_x_sum += analogRead(1);
    delay(100); }
  
  left_y_sum /=10;
  left_x_sum /=10;
  right_y_sum /=10;
  right_x_sum /=10;

  left_y_sum -=2048;
  left_x_sum -=2048;
  right_y_sum -=2048;
  right_x_sum -=2048;

  left_y_sum *=-1;
  left_x_sum *=-1;
  right_y_sum *=-1;
  right_x_sum *= -1;

  Serial.print(left_y_sum); Serial.print(", ");
  Serial.print(left_x_sum); Serial.print(", ");
  Serial.print(right_y_sum); Serial.print(", ");
  Serial.print(right_x_sum); Serial.print(", ");
  Serial.println(" ");
}