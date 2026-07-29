#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1
#define rollrate_max 360 // gyroscope rollrate maximum in deg/s
#define rollangle_max 45 // accelerometer rollangle maximum in deg
#define yawrate_max 360 // mximum yawrate in deg/s

bool toggle_flight_mode = false;
bool lastswitch = HIGH;
bool curswitch;

esp_now_peer_info_t slave;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  esp_now_init();

  uint8_t broadcastAddress[] = {0xE8, 0xF6, 0x0A, 0xC0, 0x46, 0x90};
  memcpy(slave.peer_addr, broadcastAddress, 6);
  
  slave.channel = CHANNEL;
  slave.encrypt = false;

  esp_now_add_peer(&slave);
}

void loop() {
  int16_t left_y = 90;
  int16_t left_x = 270;

  int16_t right_x = 280;
  int16_t right_y = 290;

  int16_t data[5] = {left_y, left_x, right_y, right_x, toggle_flight_mode};
  esp_now_send(slave.peer_addr, (uint8_t *)data, sizeof(data));

  //Serial.print("i sent the data");
  delay(1000);
}