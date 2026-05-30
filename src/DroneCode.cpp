#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define CHANNEL 1

Adafruit_MPU6050 mpu;

//other globals
double dt, last_time;

double last_yaw_error;
double last_roll_x_error;
double last_roll_y_error;

//constants for PIDs
const double Kp_y, Ki_y, Kd_y; //yaw
const double Kp_r_a, Ki_r_a, Kd_r_a; //angle
const double Kp_r_g, Ki_r_g, Kd_r_g; //gyro

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
    last_roll_x_error = 0;
    last_roll_y_error = 0;
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
    
    g.gyro.z = g.gyro.z *180/3.14159;
    g.gyro.x = g.gyro.x *180/3.14159;
    g.gyro.y = g.gyro.y *180/3.14159;

    //throttle
    mot1, mot2, mot3, mot4 = throttle_inp;

    //yaw
    double yaw_error = yaw_inp - g.gyro.z;
    
    double temp_yaw_PID = PID(last_yaw_error, yaw_error, Kp_y, Ki_y, Kd_y);

    if (temp_yaw_PID > 0) {
        mot1, mot3 -= temp_yaw_PID;
    } else {
        mot2, mot4 -= temp_yaw_PID;
    }
    last_yaw_error = yaw_error;

    
    
    //roll and pitch

    if (toggle_flight_mode) {
        //gyroflight

        //roll
        double roll_x_error = roll_x_inp - g.gyro.x;

        double temp_roll_x_PID = PID(last_roll_x_error, roll_x_error, Kp_r_g, Ki_r_g, Kd_r_g);

        if (temp_roll_x_PID > 0) {
            mot2, mot3 -= temp_roll_x_PID;
        } else {
            mot1, mot4 -= temp_roll_x_PID;
        }
        last_roll_x_error = roll_x_error;

        //pitch
        double roll_y_error = roll_y_inp - g.gyro.y;

        double temp_roll_y_PID = PID(last_roll_y_error, roll_y_error, Kp_r_g, Ki_r_g, Kd_r_g);

        if (temp_roll_y_PID > 0) {
            mot2, mot3 -= temp_roll_y_PID;
        } else {
            mot1, mot4 -= temp_roll_y_PID;
        }
        last_roll_y_error = roll_y_error;

    } else {
        //kalman filter

        

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