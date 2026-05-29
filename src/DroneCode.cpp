#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define CHANNEL 1

Adafruit_MPU6050 mpu;

double dt, last_time;

double last_yaw_error;

//constants for PIDs
const double Kp_y, Ki_y, Kd_y;
const double Kp_r_a, Ki_r_a, Kd_r_a;
const double Kp_r_g, Ki_r_g, Kd_r_g;

//inputs
bool toggle_flight_mode;
int16_t throttle_inp;
int16_t yaw_inp;
int16_t roll_x_inp;
int16_t roll_y_inp;

void setup() {

    //mpu stuff
    Serial.begin(115200);
    mpu.begin();
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);
    //write function to calibrate mpu


    //esp stuff
    WiFi.mode(WIFI_AP);

    esp_now_init();
    esp_now_register_recv_cb(OnDataRecv);

    last_time = 0;
    last_yaw_error = 0;

}

void loop() {

    //motor varaibles PWM
    double mot1, mot2, mot3, mot4;

    //time stuff
    double now = millis();
    dt = (now - last_time)/1000;
    last_time = now;

    //getting accel and gyro data
    sensors_event_t a, g, t;
    mpu.getEvent(&a, &g, &t);

    //need to convert to correct units
    a.acceleration.z = a.acceleration.z *180/3.14159;
    a.acceleration.y = a.acceleration.y *180/3.14159;
    a.acceleration.x = a.acceleration.x *180/3.14159;
    

    //throttle
    mot1, mot2, mot3, mot4 = throttle_inp;

    //yaw
    double yaw_error = yaw_inp - a.acceleration.z;

    mot1, mot2 -= PID(last_yaw_error, yaw_error, Kp_y, Ki_y, Kd_y);
    last_yaw_error = yaw_error;
    
    //roll

    if (toggle_flight_mode) {
        //gyroflight
    } else {
        

        

    }



    //generate 4 pwm signals : first throttle (same both modes), then roll(diff for modes), then yaw(same both modes), 3 pid loops

    //output 4 different pwm signals
}

void OnDataRecv (const uint8_t *mac_addr, const uint8_t *data, int data_len) {

    int16_t newdata[5];
    memcpy(&newdata, data, sizeof(newdata));

    throttle_inp = newdata[0];
    yaw_inp = newdata[1];
    roll_y_inp = newdata[2];
    roll_x_inp = newdata[3];
    toggle_flight_mode = newdata[4];

}

double PID (double lasterror, double error, double Kp, double Ki, double Kd) {

    double Prop = error * Kp;
    double Intg = error * dt;
    double Deri = (error - lasterror)/ dt;

    return Prop + Intg + Deri;
    
}