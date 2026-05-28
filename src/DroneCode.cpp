#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1

bool toggle_flight_mode;
uint16_t throttle_inp;
uint16_t yaw_inp;
uint16_t roll_x_inp;
uint16_t roll_y_inp;

void setup() {
  WiFi.mode(WIFI_AP);

  esp_now_init();
  esp_now_register_recv_cb(OnDataRecv);


}

void loop() {

    if (toggle_flight_mode) {
        //gyroflight
    } else {
        //accelerometer flight

        //make a PID funciton

    }



    //generate 4 pwm signals : first throttle (same both modes), then roll(diff for modes), then yaw(same both modes), 3 pid loops

    //output 4 different pwm signals
}

void OnDataRecv (const uint8_t *mac_addr, const uint8_t *data, int data_len) {

    uint16_t newdata[5];
    memcpy(&newdata, data, sizeof(newdata));

    throttle_inp = newdata[0];
    yaw_inp = newdata[1];
    roll_y_inp = newdata[2];
    roll_x_inp = newdata[3];
    toggle_flight_mode = newdata[4];

}