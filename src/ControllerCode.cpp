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

#define left_y_offset (157.95)
#define left_x_offset (128)
#define right_y_offset (149.5)
#define right_x_offset (130)

int16_t left_y;
int16_t left_x;
int16_t right_x;
int16_t right_y;

esp_now_peer_info_t slave;

void setup() {
  pinMode(6,INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  esp_now_init();
  uint8_t broadcastAddress[] = {0xE8, 0xF6, 0x0A, 0xC0, 0x4F, 0x20};
  memcpy(slave.peer_addr, broadcastAddress, 6);
  slave.channel = CHANNEL;
  slave.encrypt = false;
  esp_now_add_peer(&slave);
}

void loop() {
  
  left_y = analogRead(4);
  left_x = analogRead(3);

  right_y = analogRead(2);
  right_x = analogRead(1);


  left_y += left_y_offset;
  left_x += left_x_offset;
  right_y += right_y_offset;
  right_x += right_x_offset;

  
  
  left_y = constrain(left_y, 2048 , (4095 - left_y_offset));
  left_x = constrain(left_x, left_x_offset , (4095 - left_x_offset));
  right_y = constrain(right_y, right_y_offset , (4095 - right_y_offset));
  right_x = constrain(right_x, right_x_offset , (4095 - right_x_offset));

  
  left_y = map(left_y, 2048, (4095 - left_y_offset), 0, 1000);
  left_x = map(left_x, left_x_offset , (4095 - left_x_offset), -yawrate_max, yawrate_max); // deg/s


  curswitch = digitalRead(6);
  if (curswitch == LOW && lastswitch == HIGH) {
    delay(50);
    curswitch = digitalRead(6);
    if (curswitch == LOW ) {
      toggle_flight_mode = !toggle_flight_mode;
    }
  }
  lastswitch = curswitch;

  if (toggle_flight_mode) {
    // gyro flight
    right_y = map(right_y, right_y_offset , (4095 - right_y_offset), -rollrate_max, rollrate_max); // deg/s
    right_x = map(right_x, right_x_offset , (4095 - right_x_offset), -rollrate_max, rollrate_max); // deg/s
  } else {
    // accelerometer flight
    right_y = map(right_y, right_y_offset , (4095 - right_y_offset), -rollangle_max, rollangle_max); // target angle in deg
    right_x = map(right_x, right_x_offset , (4095 - right_x_offset), -rollangle_max, rollangle_max); // target angle in deg
  }

  Serial.print(left_y); Serial.print(" ,");
  Serial.print(left_x); Serial.print(" ,");
  Serial.print(right_y); Serial.print(" ,");
  Serial.print(right_x); Serial.print(" ,");
  Serial.print(toggle_flight_mode); Serial.println(" ");

  int16_t data[5] = {left_y, left_x, right_y, right_x, toggle_flight_mode};
  esp_now_send(slave.peer_addr, (uint8_t *)data, sizeof(data));
  
}