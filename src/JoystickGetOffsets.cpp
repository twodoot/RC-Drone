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
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(D3,INPUT_PULLUP);
}

void loop() {
    
  for (int i=0; i<10; i++) {
    left_y_sum += analogRead(A3);
    left_x_sum += analogRead(A2);
    right_y_sum += analogRead(A1);
    right_x_sum += analogRead(A2);
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