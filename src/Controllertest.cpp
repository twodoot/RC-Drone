#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1
#define rollrate_max 360 // gyroscope rollrate maximum in deg/s
#define rollangle_max 35 // accelerometer rollangle maximum in deg
#define yawrate_max 360 // mximum yawrate in deg/s

bool toggle_flight_mode = false;
bool lastswitch = HIGH;
bool curswitch;

#define left_y_offset (170)
#define left_x_offset (128)
#define right_y_offset (150)
#define right_x_offset (142)

int16_t left_y;
int16_t left_x;
int16_t right_x;
int16_t right_y;

esp_now_peer_info_t slave;

void setup() {
  pinMode(D3,INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  esp_now_init();
  uint8_t broadcastAddress[] = {0xE8, 0xF6, 0x0A, 0xC0, 0x4F, 0x20};
  memcpy(slave.peer_addr, broadcastAddress, 6);
  slave.channel = CHANNEL;
  slave.encrypt = false;
  esp_now_add_peer(&slave);
}

void loop() {
  
  left_y = analogRead(A3);
  left_x = analogRead(A2);

  right_y = analogRead(A1);
  right_x = analogRead(A0);
  

  Serial.print(left_y); Serial.print(", "); 
  Serial.print(left_x); Serial.print(", "); 
  Serial.print(right_y); Serial.print(", "); 
  Serial.print(right_x); Serial.print(", "); 
  Serial.print(digitalRead(D3)); Serial.println(" ");
}