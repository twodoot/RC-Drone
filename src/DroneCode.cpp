#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>
#include <Servo.h>

#define CHANNEL 1

//structs
struct Calibration_Data {
    double a_x, a_y, a_z, g_x, g_y, g_z;

};
struct Roll_Angles {
    double roll_x, roll_y;
};

Servo ESC = Servo();

Adafruit_MPU6050 mpu;
sensors_event_t a, g, t;
Calibration_Data cal;

//other globals
double dt;
double last_time = 10000;

double last_yaw_error = 0;
double last_roll_x_error = 0;
double last_roll_y_error = 0;

//kalman filter
double sigma_gyro = 0.5; //standerd deviation of gyroscope errorin degrees/second
double sigma_accel = 0.118; // standerd deviation of accelerometer error in degrees

double kalman_roll_x_angle = 0, kalman_uncertainty_roll_x_angle = 2*2;
double kalman_roll_y_angle = 0, kalman_uncertainty_roll_y_angle = 2*2;

//constants for PIDs
const double Kp_y = 0, Ki_y = 0, Kd_y = 0; //yaw
const double Kp_r_a = 2, Ki_r_a = 0.075, Kd_r_a = 0; //angle
const double Kp_r_g = 0.5, Ki_r_g = 0, Kd_r_g = 0; //gyro

//PID Integral cumulative errors
double cumerror_yaw = 0, cumerror_roll_x_a = 0, cumerror_roll_y_a = 0, cumerror_roll_x_g = 0, cumerror_roll_y_g = 0;

//inputs
bool toggle_flight_mode;
int16_t throttle_inp;
int16_t yaw_inp;
int16_t roll_x_inp;
int16_t roll_y_inp;

// funcitons
void OnDataRecv (const uint8_t *mac_addr, const uint8_t *data, int data_len);
double PID (double lasterror, double error, double &Intg, double Kp, double Ki, double Kd);
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

    //motor arm time
    ESC.writeMicroseconds(17,1000); // MOT1
    ESC.writeMicroseconds(18,1000); //MOT2
    ESC.writeMicroseconds(9,1000); //MOT3
    ESC.writeMicroseconds(10,1000); //MOT4
    delay(5000);
}

void loop() {

    //motor varaibles PWM
    double mot1, mot2, mot3, mot4;

    //time stuff
    double now = millis();
    dt = (now - last_time)/1000;
    last_time = now;

    //getting accel and gyro data
    
    mpu.getEvent(&a, &g, &t);

    a.acceleration.x -= cal.a_x;
    a.acceleration.z -= cal.a_y;
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

    // so its correct for drone

    double temp_swap = a.acceleration.x;
    a.acceleration.x = a.acceleration.y;
    a.acceleration.y = temp_swap;
    a.acceleration.x *= -1;
    a.acceleration.y *= -1;

    temp_swap = g.gyro.x;
    g.gyro.x = g.gyro.y;
    g.gyro.y = temp_swap;
    g.gyro.x *= -1;
    g.gyro.y *= -1;

    Serial.print("gyro (x,y): "); Serial.print(g.gyro.x); Serial.print(", ");
    Serial.print(g.gyro.y); Serial.print("  ");

    


    //throttle
    mot1 = throttle_inp;
    mot2 = throttle_inp;
    mot3 = throttle_inp;
    mot4 = throttle_inp;

    //yaw
    double yaw_error = yaw_inp - g.gyro.z;
    
    double temp_yaw_PID = PID(last_yaw_error, yaw_error, cumerror_yaw, Kp_y, Ki_y, Kd_y);


    //mot 1 front left cc, mot 2 front right c, mot 3 back left c, mot4 back right cc


    mot2 -= temp_yaw_PID; mot3 -= temp_yaw_PID;  // clock mot
    mot1 += temp_yaw_PID; mot4 += temp_yaw_PID; // cclock mot 

    last_yaw_error = yaw_error;

    
    //roll and pitch

    if (!toggle_flight_mode) {
        //gyroflight

        //change integral errors for angle flight to 0
        cumerror_roll_x_a = 0;
        cumerror_roll_y_a = 0;


        //roll x 
        double roll_x_error = roll_x_inp - g.gyro.x;

        double temp_roll_x_PID = PID(last_roll_x_error, roll_x_error, cumerror_roll_x_g ,Kp_r_g, Ki_r_g, Kd_r_g);

        mot2 -= temp_roll_x_PID; mot4 -= temp_roll_x_PID;  // mots on right 
        mot1 += temp_roll_x_PID; mot3 += temp_roll_x_PID; // mots on left

        last_roll_x_error = roll_x_error;

        //roll y
        double roll_y_error = roll_y_inp - g.gyro.y;

        double temp_roll_y_PID = PID(last_roll_y_error, roll_y_error, cumerror_roll_y_g ,Kp_r_g, Ki_r_g, Kd_r_g);

        mot1 -= temp_roll_y_PID; mot2 -= temp_roll_y_PID;  // mots front
        mot3 += temp_roll_y_PID; mot4 += temp_roll_y_PID; // mots rear

        last_roll_y_error = roll_y_error;

    } else {

        Roll_Angles rollangles = Accelerometer_Angle(a.acceleration);

        //change integral errors for gyro flight to 0
        cumerror_roll_x_g = 0;
        cumerror_roll_y_g = 0;
        
        //kalman correceion code (test without first and then try to tune with it if needed)
        
        
        KalmanRoll(kalman_roll_x_angle, kalman_uncertainty_roll_x_angle, g.gyro.x, rollangles.roll_x);
        KalmanRoll(kalman_roll_y_angle, kalman_uncertainty_roll_y_angle, g.gyro.y, rollangles.roll_y);

        rollangles.roll_x = kalman_roll_x_angle;
        rollangles.roll_y = kalman_roll_y_angle;
        

        //roll x

        double roll_x_error = roll_x_inp - rollangles.roll_x;

        double temp_roll_x_PID = PID(last_roll_x_error, roll_x_error, cumerror_roll_x_a ,Kp_r_a, Ki_r_a, Kd_r_a);

        mot2 -= temp_roll_x_PID; mot4 -= temp_roll_x_PID;  // mots on right 
        mot1 += temp_roll_x_PID; mot3 += temp_roll_x_PID; // mots on left

        last_roll_x_error = roll_x_error;

        //roll y

        double roll_y_error = roll_y_inp - rollangles.roll_y;

        double temp_roll_y_PID = PID(last_roll_y_error, roll_y_error, cumerror_roll_y_a, Kp_r_a, Ki_r_a, Kd_r_a);

        mot1 -= temp_roll_y_PID; mot2 -= temp_roll_y_PID;  // mots front
        mot3 += temp_roll_y_PID; mot4 += temp_roll_y_PID; // mots rear

        last_roll_y_error = roll_y_error;


        //kalman debug prints
        Serial.print("kalman roll angles (x,y): ");

        Serial.print(rollangles.roll_x); Serial.print(", "); Serial.print(rollangles.roll_y); Serial.print("  ");
    }

    // turn to pwm signals

    mot1 +=1000;
    mot2 +=1000;
    mot3 +=1000;
    mot4 +=1000;


    if (mot1 <1050) {
        mot1 = 1000;
    }
    if (mot2 <1050) {
        mot2 = 1000;
    }
    if (mot3 <1050) {
        mot3 = 1000;
    }
    if (mot4 <1050) {
        mot4 = 1000;
    }

    if (a.acceleration.z <0) {
        mot1 = 1000;
    }
    if (a.acceleration.z <0) {
        mot2 = 1000;
    }
    if (a.acceleration.z <0) {
        mot3 = 1000;
    }
    if (a.acceleration.z <0) {
        mot4 = 1000;
    }


    mot1 = constrain(mot1 , 1000, 2000);
    mot2 = constrain(mot2 , 1000, 2000);
    mot3 = constrain(mot3 , 1000, 2000);
    mot4 = constrain(mot4 , 1000, 2000);



    //debug prints
    Serial.print("mots 1-4: ");

    Serial.print(mot1); Serial.print(", ");
    Serial.print(mot2); Serial.print(", ");
    Serial.print(mot3); Serial.print(", ");
    Serial.print(mot4); Serial.print(", ");
    
    Serial.println(" ");


    //output 4 different pwm signals
    ESC.writeMicroseconds(17,mot1); // MOT1
    ESC.writeMicroseconds(18,mot2); //MOT2
    ESC.writeMicroseconds(9,mot3); //MOT3
    ESC.writeMicroseconds(10,mot4); //MOT4
    
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

double PID (double lasterror, double error, double &Intg, double Kp, double Ki, double Kd) {

    double Prop = error * Kp;
    Intg += error * dt *Ki;
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