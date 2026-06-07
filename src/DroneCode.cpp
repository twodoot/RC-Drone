#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

#define CHANNEL 1

Adafruit_MPU6050 mpu;

//other globals
double dt, last_time;

double last_yaw_error;
double last_roll_x_error;
double last_roll_y_error;

//kalman filter
double sigma_gyro = 0.5; //standerd deviation of gyroscope errorin degrees/second
double sigma_accel = 3; // standerd deviation of accelerometer error in degrees

double kalman_roll_x_angle = 0, kalman_uncertaintyroll_x_angle = 2*2;
double kalman_roll_y_angle = 0, kalman_uncertaintyroll_y_angle = 2*2;

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

//structs
struct Calibration_Data {
    double a_x, a_y, a_z, g_x, g_y, g_z;

};

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

    Calibration_Data cal = Calibrate_MPU();
    a.acceleration.x -= cal.a_x;
    a.acceleration.z -= cal.a_z;
    a.acceleration.z -= cal.a_z;
    g.gyro.x-= cal.g_x;
    g.gyro.y-= cal.g_y;
    g.gyro.z-= cal.g_z;
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
    double Intg = error * dt *Ki;
    double Deri = ((error - lasterror)/ dt ) * Kd;

    return Prop + Intg + Deri;
    
}

void KalmanRoll (double &kalman_angle, double &kalman_uncertainty, double gyro_input, double accel_angle){
    kalman_angle = kalman_angle + (dt * gyro_input);
    kalman_uncertainty = kalman_uncertainty + ((dt * dt) * (sigma_gyro * sigma_gyro));
    double gain = kalman_uncertainty/(kalman_uncertainty + (sigma_accel * sigma_accel));
    kalman_angle = kalman_angle + gain * (accel_angle - kalman_angle);
    kalman_uncertainty = (1-gain)*kalman_uncertainty;
}

void AccelerometerAngle (double a_x, double a_y, double a_z) {
    
}

Calibration_Data Calibrate_MPU () {
    sensors_event_t a, g, t;
    //takes 20 readings over 5 seconds and averages

    double a_x = 0, a_y = 0, a_z = 0 , g_x = 0, g_y = 0, g_z = 0;

    for (int i = 0; i < 20; i++) {
        mpu.getEvent(&a, &g, &t);
        a_x += a.acceleration.x;
        a_y += a.acceleration.y;
        a_z += a.acceleration.z;
        g_x += g.gyro.x;
        g_y += g.gyro.y;
        g_z += g.gyro.z;
        
        delay(250);
    }
    a_x /=20; a_y /=20; a_z /=20; g_x/=20; g_y/=20; g_z /= 20;

    return {a_x , a_y , a_z, g_x, g_y, g_z};
}