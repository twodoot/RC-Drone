#include <Arduino.h>

// just a test

bool togglefunction(bool toggle_flight_mode);

#define rollrate_max 360 // gyroscope rollrate maximum in deg/s
#define rollangle_max 45 // accelerometer rollangle maximum in deg
#define yawrate_max 360 // mximum yawrate in deg/s

bool toggle_flight_mode = false;
int lastswitch = HIGH;
int curswitch;

void setup() {
  pinMode(D1,INPUT_PULLUP);
}

void loop() {
  short left_y = analogRead(A0);
  short left_x = analogRead(A1);

  short right_x = analogRead(A2);
  short right_y = analogRead(A3);

  left_y = constrain(left_y, 520 ,1023);
  left_y = map(left_y, 520, 1023, 0, 180);
  left_x = map(left_x, 0, 1023, -yawrate_max, yawrate_max); // deg/s


  curswitch = digitalRead(D2);
  if (curswitch == LOW && lastswitch == HIGH) {
    delay(50);
    curswitch = digitalRead(D2);
    if (curswitch == LOW ) {
      toggle_flight_mode = togglefunction(toggle_flight_mode);
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
}

 bool togglefunction(bool toggle_flight_mode) {
    switch (toggle_flight_mode) {
      case false:
        toggle_flight_mode = true;
        break;
      case true:
        toggle_flight_mode = false;
        break;
  }
  return toggle_flight_mode;
}