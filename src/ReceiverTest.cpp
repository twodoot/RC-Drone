#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>
#include <ESP32Servo.h>

#define CHANNEL 0

//inputs
bool toggle_flight_mode;
int16_t throttle_inp;
int16_t yaw_inp;
int16_t roll_x_inp;
int16_t roll_y_inp;


// funcitons
void OnDataRecv (const uint8_t *mac_addr, const uint8_t *data, int data_len);


void setup() {

    Serial.begin(115200);
    
    //esp stuff
    WiFi.mode(WIFI_STA);

   if (esp_now_init() != ESP_OK) {
    Serial.println("ESPNow Init Fail");
    return;
  }
    esp_now_register_recv_cb(OnDataRecv);
    
}

void loop() {
    //String output = String(throttle_inp) + " " + String(yaw_inp) + " " + String(roll_x_inp) + " " + String(roll_y_inp) + " " + String(toggle_flight_mode);
    //Serial.print(output);
    //delay(1000);

}

void OnDataRecv (const uint8_t *mac_addr, const uint8_t *data, int data_len) {

    Serial.print("data received");

    int16_t newdata[5];
    //if (data_len == 10) {
        memcpy(newdata, data, sizeof(newdata));

        throttle_inp = newdata[0];
        yaw_inp = newdata[1];
        roll_y_inp = newdata[2];
        roll_x_inp = newdata[3];
        toggle_flight_mode = newdata[4];
    //}

    String output = String(throttle_inp) + " " + String(yaw_inp) + " " + String(roll_x_inp) + " " + String(roll_y_inp) + " " + String(toggle_flight_mode);
    Serial.println(output);
    

}
