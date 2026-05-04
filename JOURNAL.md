---
title: "RC-Drone"
author: "Twodoor"
description: "A project to make an RC Drone with a custom flight computer programmed on an arduino nano (ESP32)"
created_at: "5/3/2026"
---

# 26th April: Made V1 of CAD model for Drone
I made this model with the idea of making a compartment for putting in two LIPO batteries with the other electronics on top. This however has resulted in quite a boxy and unaerodynamic shape.
To improve upon it I will try to look at other designs to take inspiration from them

![image](https://github.com/twodoot/RC-Drone/blob/main/Images/Drone_V1_image.png)

**Total time spent: 4h**


# 29th April: Made V1 of wiring diagram for Drone
I drew up the wiring diagrams for the drone. I'm planning to use an MPU-6050 for the IMU (Gyro and accelerometer module). I will be using one way speed controllers (ESC) as they are both cheaper and easier to use and have a step down voltage loop which I can use to power the arduino, and I will be using specifically an arduino nano ESP32 because I can use the ESP-now porotocol to communicate wirelessly instead of needing a seperate communications module.


![image](https://github.com/twodoot/RC-Drone/blob/main/Images/Drone_Wiring_V1.jpeg)

**Total time spent: 2h**

# 30th April: Improved wiring diagram for drone and made one for controller
I fixed the SDA pin not being connected, changed the circuit to be powerd by only one battery becuase it is less likely to fail that way and will weigh less. I also made a first version of the cirucit for the controller, which will be powerd by a 9volt battery (the drone will be powerd by one 4S LIPO battery).

![image](https://github.com/twodoot/RC-Drone/blob/main/Images/Drone_Wiring_V2.jpeg)
![image](https://github.com/twodoot/RC-Drone/blob/main/Images/Controller_Wiring_V1.jpeg)

**Total time spent: 1h**


# 3rd May: Made V2 of drone model and fixed voltage level on drone logic pin
I took some inspiration from FPV drones where I saw lots of them have thir batteries strapped down on top of drone, and I also thought to put the ESCs on the struts of the drone to save space on the main body, and designed the main body to accomodate one battery with indented slots for the straps. The arduino will be mounted in centre on the base and the IMU will be mounted on the ceiling of the section direcctly above it. I'm planning to mount the ESCs under the struts with zipties. I added some of the bolts and standoffs in this version as well as cutting out the holes for the bolts (1.15x enlarged from prior experience) but will finalise it later.
I also realised that the ESP version of the arduino nano can only handle 3.3 volts through its logic pins and luckily the MPU-6050 functions on 3.3 volts so I rewired it to have it be powerd by the 3.3 volt pin on the nano. I will fix this issue on the controller wiring later.
As a sidenote I will have the main frame of the drone (and controller casing) 3D printed

![image](https://github.com/twodoot/RC-Drone/blob/main/Images/Drone_Wiring_V3.png)
![image](https://github.com/twodoot/RC-Drone/blob/main/Images/Drone_V2_image.png)

**Total time spent: 5h**

# 4th May: Fixed the wiring diagram voltage for the controller and Work on Drone CAD, started working on code for drone controller
The KY-023 joystick breakout board im planning to use is compatibele with 3.3 volts so the fix was simple
I also worked on the drone CAD model by adding standoffs and bolts and thinging in general about how the electronics and other components will be mounted together on the drone, and i organised the compnents on the CAD model into subfolders for better readability.
![image](https://github.com/twodoot/RC-Drone/blob/main/Images/Controller_Wiring_V2.png)
![image](https://github.com/twodoot/RC-Drone/blob/main/Images/Drone_V2_V2.png)
 
 
I also started working on the code for the drone controller, I wrote the stuff to take inputs from my joysticks and convert them to the data I will send to the drone, with debounce protection on the switch.
 ```cpp
 #define rollrate_max 360; // gyroscope rollrate maximum in deg/s
#define rollangle_max 45; // accelerometer rollangle maximum in deg
#define yawrate_max 360; // mximum yawrate in deg/s

void setup() {
  pinMode(D1,INPUT_PULLUP);

  lastswitch = HIGH;
  toggle_flight_mode = false;
}

void loop() {
  short left_y = analogueread(A0);
  short left_x = analogueread(A1);

  short right_x = analogueread(A2);
  short right_y = analogueread(A3);

  left_y = constrain(left_y, 520,1023);
  left_y = map(left_y, 520, 1023, 0, 180);
  left_x = map(left_x, 0, 1023, -yawrate_max, yawrate_max); // deg/s


  curswitch = digitalread(D2);
  if (curswitch == LOW && lastswich == HIGH) {
    delay(50);
    curswitch = digitalread(D2);
    if (curswitch == LOW ) {
      toggle_flight_mode = togglefunction(lastswitch, toggle_flight_mode);
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

togglefunction(lastswitch, toggle) {
    switch (toggle) {
      case false:
        toggle = true;
      case true:
        toggle = false;
  }
  return toggle;
}
 
 
 ```
 
 I also fixed an issue with the switch being connected to an analogue pin on the wiring diagram
 ![image](https://github.com/twodoot/RC-Drone/blob/main/Images/Controller_Wiring_V3.png)
 
 **Total time spent: 4.5h**