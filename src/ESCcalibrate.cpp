#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>
#include <Servo.h>

#define CHANNEL 1

//inputs
bool toggle_flight_mode;
int16_t throttle_inp;
int16_t yaw_inp;
int16_t roll_x_inp;
int16_t roll_y_inp;

Servo ESC = Servo();

// funcitons
void OnDataRecv (const uint8_t *mac_addr, const uint8_t *data, int data_len);


void setup() {

    Serial.begin(115200);
    
    WiFi.mode(WIFI_STA);

    esp_now_init();
    esp_now_register_recv_cb(OnDataRecv);
    

    //pinMode(18, OUTPUT);
   // pinMode(17, OUTPUT);
    //pinMode(10, OUTPUT);
    //pinMode(9, OUTPUT);




    //ESC stuff
    

    
    
}

void loop() {
    
    Serial.print("worked");

    String output = String(throttle_inp) + " " + String(yaw_inp) + " " + String(roll_y_inp) + " " + String(roll_x_inp) + " " + String(toggle_flight_mode);
    Serial.println(output); 
    
    
    ESC.writeMicroseconds(17,throttle_inp); // MOT1
    ESC.writeMicroseconds(18,yaw_inp); //MOT2
    ESC.writeMicroseconds(9,roll_y_inp); //MOT3
    ESC.writeMicroseconds(10,roll_x_inp); //MOT4
    

}

void OnDataRecv (const uint8_t *mac_addr, const uint8_t *data, int data_len) {

    //Serial.print("data received");

    int16_t newdata[5];
    if (data_len == 10) {
        memcpy(newdata, data, sizeof(newdata));
        


        throttle_inp = newdata[0];
        yaw_inp = newdata[1];
        roll_y_inp = newdata[2];
        roll_x_inp = newdata[3];
        toggle_flight_mode = newdata[4];

        throttle_inp = constrain(throttle_inp, 0, 1000);
        throttle_inp = map(throttle_inp, 0, 1000 , 1000, 2000);

        yaw_inp = constrain(yaw_inp, 0,360);
        yaw_inp = map(yaw_inp, 0,360, 1000, 2000);

        roll_y_inp = constrain(roll_y_inp, 0,35);
        roll_y_inp = map(roll_y_inp, 0,35, 1000, 2000);

        roll_x_inp = constrain(roll_x_inp, 0,35);
        roll_x_inp = map(roll_x_inp, 0,35, 1000, 2000);
    }
}
