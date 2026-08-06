#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>
#include <ESP32Servo.h>

#define CHANNEL 1
#define pi 3.14159

//structs
struct Calibration_Data {
    double a_x, a_y, a_z, g_x, g_y, g_z;

};


struct Roll_Angles {

    double roll_x, roll_y;
};

Adafruit_MPU6050 mpu;
sensors_event_t a, g, t;
Calibration_Data cal;


//other globals
double dt, last_time = 5000;

double last_yaw_error = 0;
double last_roll_x_error = 0;
double last_roll_y_error = 0;

//kalman filter
double sigma_gyro = 0.5; //standerd deviation of gyroscope errorin degrees/second
double sigma_accel = 0.118; // standerd deviation of accelerometer error in degrees

double kalman_roll_x_angle = 0, kalman_uncertainty_roll_x_angle = 2*2;
double kalman_roll_y_angle = 0, kalman_uncertainty_roll_y_angle = 2*2;

//inputs
bool toggle_flight_mode;
int16_t throttle_inp;
int16_t yaw_inp;
int16_t roll_x_inp;
int16_t roll_y_inp;


// funcitons
void OnDataRecv (const uint8_t *mac_addr, const uint8_t *data, int data_len);
void KalmanRoll (double &kalman_angle, double &kalman_uncertainty, double gyro_input, double accel_angle);
Roll_Angles Accelerometer_Angle (sensors_vec_t a);
Calibration_Data Calibrate_MPU ();

void setup() {

    //mpu stuff
    Serial.begin(115200);
    mpu.begin();
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);

    //function to calibrate mpu
    cal = Calibrate_MPU();
    cal.a_z += 9.80665;   // + cuz it is upsidedown and remove g from calibration as it stands upright when claibrating

    //esp stuff
    WiFi.mode(WIFI_STA);

    esp_now_init();
    esp_now_register_recv_cb(OnDataRecv);

}

void loop() {

    //time stuff
    double now = millis();
    dt = (now - last_time)/1000;
    last_time = now;

    //getting accel and gyro data
    
    mpu.getEvent(&a, &g, &t);

    
    a.acceleration.x -= cal.a_x;
    a.acceleration.y -= cal.a_y;
    a.acceleration.z -= cal.a_z;
    g.gyro.x-= cal.g_x;
    g.gyro.y-= cal.g_y;
    g.gyro.z-= cal.g_z;
    
    //need to convert to correct units (degrees)
    
    g.gyro.z = g.gyro.z *180/3.14159;
    g.gyro.x = g.gyro.x *180/3.14159;
    g.gyro.y = g.gyro.y *180/3.14159;

    // its upside down when im working with it so i want to treat it like its right way up

    a.acceleration.z *= -1;

    Roll_Angles rollangles = Accelerometer_Angle(a.acceleration);

        //change integral errors for gyro flight to 0
        
        //kalman correceion code (test without first and then try to tune with it if needed)
        
        
        KalmanRoll(kalman_roll_x_angle, kalman_uncertainty_roll_x_angle, g.gyro.x, rollangles.roll_x);
        KalmanRoll(kalman_roll_y_angle, kalman_uncertainty_roll_y_angle, g.gyro.y, rollangles.roll_y);

        rollangles.roll_x = kalman_roll_x_angle;
        rollangles.roll_y = kalman_roll_y_angle;
        

        //roll x
/*
    Serial.print(a.acceleration.x); Serial.print(", ");
    Serial.print(a.acceleration.y); Serial.print(", ");
    Serial.print(a.acceleration.z); Serial.print(", "); Serial.print(", ");

    



    Serial.print(a.acceleration.x); Serial.print(", ");
    Serial.print(a.acceleration.y); Serial.print(", ");
    Serial.print(a.acceleration.z); Serial.print(", ");
    
    Serial.print(g.gyro.x); Serial.print(", ");
    Serial.print(g.gyro.y); Serial.print(", ");
    Serial.print(g.gyro.z); Serial.print(", ");  Serial.print(" "); Serial.print(" , ");*/
    
    /*
    Serial.print(cal.a_x); Serial.print(", ");
    Serial.print(cal.a_y); Serial.print(", ");
    Serial.print(cal.a_z); Serial.print(", ");
    Serial.print(cal.g_x); Serial.print(", ");
    Serial.print(cal.g_y); Serial.print(", ");
    Serial.print(cal.g_z); Serial.println(" ");
    */

    Serial.print(rollangles.roll_x); Serial.print(", "); Serial.print(rollangles.roll_y); Serial.println(" ");
    

}


void OnDataRecv (const uint8_t *mac_addr, const uint8_t *data, int data_len) {

    int16_t newdata[5];
    if (data_len == 10) { //nominal message size
        memcpy(newdata, data, sizeof(newdata));

        throttle_inp = newdata[0];
        yaw_inp = newdata[1];
        roll_y_inp = newdata[2];
        roll_x_inp = newdata[3];
        toggle_flight_mode = newdata[4];
    }
    

}

void KalmanRoll (double &kalman_angle, double &kalman_uncertainty, double gyro_input, double accel_angle){
    kalman_angle = kalman_angle + (dt * gyro_input);
    kalman_uncertainty = kalman_uncertainty + ((dt * dt) * (sigma_gyro * sigma_gyro));
    double gain = kalman_uncertainty/(kalman_uncertainty + (sigma_accel * sigma_accel));
    kalman_angle = kalman_angle + gain * (accel_angle - kalman_angle);
    kalman_uncertainty = (1-gain)*kalman_uncertainty;
    
}

Roll_Angles Accelerometer_Angle (sensors_vec_t a) {
    double roll_x;
    double roll_y;
    roll_x  = atan2(a.y,(sqrt((a.x*a.x)+ (a.z*a.z))))*180/3.14159;
    roll_y  = atan2(-a.x,(sqrt((a.y*a.y)+ (a.z*a.z))))*180/3.14159;

    

    Serial.print(roll_x); Serial.print(", ");
    Serial.print(roll_y); Serial.print(", "); Serial.print(", ");
    
    // in case it flips over so it doesnt think its the right way up
    /*
    
    if (a.z <0) {
        if (abs(roll_x)>abs(roll_y)) {
        if (roll_x>0){
            roll_x = 90;
        } else {
            roll_x = -90;
        }}else{

        if (roll_y>0){
            roll_y = 90;
        } else {
            roll_y = -90;
        }}
        
    }*/

    return {roll_x , roll_y};

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