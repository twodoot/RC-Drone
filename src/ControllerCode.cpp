#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1
#define rollrate_max 360 // gyroscope rollrate maximum in deg/s
#define rollangle_max 45 // accelerometer rollangle maximum in deg
#define yawrate_max 360 // mximum yawrate in deg/s

bool toggle_flight_mode = false;
uint8_t lastswitch = HIGH;
uint8_t curswitch;

esp_now_peer_info_t slave;

void setup() {
  pinMode(D2,INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  esp_now_init();
  uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //placeholder adress
  memcpy(slave.peer_addr, broadcastAddress, 6);
  slave.channel = CHANNEL;
  slave.encrypt = false;
  esp_now_add_peer(&slave);
}

void loop() {
  uint16_t left_y = analogRead(A0);
  uint16_t left_x = analogRead(A1);

  uint16_t right_x = analogRead(A2);
  uint16_t right_y = analogRead(A3);

  left_y = constrain(left_y, 520 ,1023);
  left_y = map(left_y, 520, 1023, 0, 180);
  left_x = map(left_x, 0, 1023, -yawrate_max, yawrate_max); // deg/s


  curswitch = digitalRead(D2);
  if (curswitch == LOW && lastswitch == HIGH) {
    delay(50);
    curswitch = digitalRead(D2);
    if (curswitch == LOW ) {
      toggle_flight_mode = !toggle_flight_mode;
    }
  }
  lastswitch = curswitch;

  if (toggle_flight_mode) {
    // gyro flight
    right_y = map(right_y, 0, 1023, -rollrate_max, rollrate_max); // deg/s
    right_x = map(right_x, 0, 1023, -rollrate_max, rollrate_max); // deg/s
  } else {
    // accelerometer flight
    right_y = map(right_y, 0, 1023, -rollangle_max, rollangle_max); // target angle in deg
    right_x = map(right_x, 0, 1023, -rollangle_max, rollangle_max); // target angle in deg
  }


  uint16_t data[4] = {left_y, left_x, right_y, right_x};
  esp_now_send(slave.peer_addr, (uint8_t *)data, sizeof(data));
  
}