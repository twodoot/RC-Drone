# RC Drone
	
This is a project in which I am making an RC Drone and Controller from scratch with 2 arduino nano ESP32s.  <br>   
Both the Drone and Controller are 3D printed, and assembled with various sized bolts and stand-offs.  <br>  
I'm making this project for personal experience in hardware and software design as it is my first embedded system project. <br>  

Here is a link to a video showing a demo of the drone that I built: [Drone Demo](https://youtube.com/shorts/FMnVdksYT60?si=8YT7XMB2EZSOUAqi)
	
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Drone/Drone_Final.jpeg) <br> Image of Drone <br> <br>
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Image_1.jpeg) <br> Controller with lid <br> <br>
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Image_2.jpeg) <br> Controller without lid <br> <br>
	
## Parts List
	
**3D Printed:**

- Drone Base
- Drone Top 
- Drone legs **x4** 
- Controller Body
- Controller Lid
- Controller Drawer
	
**Electronic Components**
	
- Adruino nano ESP32 without pins **x2**
- MPU-6050
- 4S 2200mah LiPo battery
- XT-60 1 female -> 2 male splitter **x3**
- 5 Volt USB Power Bank (max dimensions: 10.6L x 6.8W x 1.6Th cm)
- Electronic Speed Controller (ESC) at least 40amp rated **x4**
- KY-023 joystick modules **x2**
- jumper wires **many**
- male terminal banana connectors 3.5mm (for soldering not crimping) **x12**
- 2400kv brushless DC motors **x4**
- drone propellers (recommended  5.1x3.6x3) **x4**
- USBC to USBA cable (power and data) **x2**
- Power only USBC to bare wires
	
**Structural**
	
- M1.6 bolts **x8** minimum length 15mm
- M2.5 bolts **x8**
- M3 bolts  **x4** minimum length 18mm
- M3 bolts for motors **x16** minimum length 10mm
- M5 bolts **x4** minimum length 70mm
- electrical tape
- battery straps **x2**
- automotive plastic tubing 1.5mm inner diameter 2.5mm outer diameter for M1.6 stand-offs
- stiff foam (for MPU-6050 and joystick stand-off/ shock absorption)

**Tools**

- sandpaper low grit
- hacksaw
- soldering iron (and solder and a sponge)
- multimeter (for debugging in case you run into issues assembling)
- scissors
- pliers
- screwdriver

## Assembly

### Controller:

Slice and print the Lid and Base of the controller files can be found: ![Controller CAD Files](https://github.com/twodoot/RC-Drone/tree/main/CAD%20Files/Controller)

Solder wires with female headers onto the relevant pins of the arduino as seen in the wiring diagram below if you are unsure of my following description, ensuring they are large enough to reach the joystick pins when inside the controller but not too much longer so that the wires can fit inside easily, to the A0-A3 and to D3. Then make 2 wires that have 3 way connections stripping a section of casing off the middle off one wire with a female header and soldering another wire with a female header to it. Cover all exposed wires with either heat shrinks (if you have any) or electrical tape (what I did). 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Wiring%20Diagrams/Wiring%20Diagram%20Controller.png)

Extract supports from the controller body:

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Supports_Before.png)
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Supports_After.png)

Sand down the Drawer until it fits stiffly into the body slot for the power bank underneath but doesn't slide out easily.

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Drawer_Sanded.png)

Ensure all exposed bits of wire from soldering are covered up by either electrical tape or shrink-wraps.

Screw in and screw out M1.6 bolts out of the arduino stand-off locations on the controller to widen the tolerances.

Then cut 4 bolts down to size where they will be long enough to screw arduino in well but won't poke through base of controller into the power bank compartment.

Cut off 8 thin bits of the plastic tubing between 1-2mm in length but keep it consistent between the 8.

Fit one stand-off through each M1.6 bolt and then put them on the arduino through the top (USB port is on top) then on the bottom put the other 4 stand-offs sandwiching the arduino between them.

Place the arduino on top of the holes M1.6 holes and screw in the bolts first screwing in all the bolts a small amount until they are all in the threads then taking turns slowly screwing them in until all are screwed in tight and the arduino doesn't wobble.

<img width="812" height="557" alt="image" src="https://github.com/user-attachments/assets/5515f4c1-679b-428d-98b1-0b342da9a65f" />

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Arduino_Mounted.jpeg)

Screw in and out M2.5 bolts a small amount into each mounting hole to widen tolerances and make it easier to screw in joystick modules.

Cut a rectangle of foam around the base of one of the joystick modules then cut it down to only about 3mm thick and repeat for the other one. Thread M2.5 bolts through the mounting holes on each joystick modules and through the foam until it just is about to poke through the bottom then put the joysticks with the attached foam pads on top of the joystick mounting holes and screw them in. Ensure the joystick modules are screwed in with the pins facing the arduino.

Connect the wires up to the joystick modules: GND to GND to each module, 3.3V to +5V to each module, A3 to VRX of left joystick, A2 to VRY of left module, A1 to VRX of right module, A0 to VRY of right joystick, D3 to the SW of right joystick.

Connect a USBC to USBA cable that just reaches the power bank underneath to the slot on the arduino for it.

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Assembled.png)

Optionally the lid can also be put on and even without screws the fit is quite tight so they aren't necessary at all but if you do want to screw it in M3 screws are needed 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Image_1.jpeg)


### Drone:

Slice and print the Top and Base of the Drone and Spacers: files can be found ![Drone CAD Files](https://github.com/twodoot/RC-Drone/tree/main/CAD%20Files/Drone)

Connecting the drone arduino and the MPU-6050 IMU: 4 wires will need to be soldered, cut off wire about 20mm long with both ends exposed. Solder one end of the wires onto the MPU-6050 soldering A4 to SDA and A5 to SCL, GND to GND and 3.3V to VCC.

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Wiring%20Diagrams/Drone%20Wiring%20Diagram.png)

Screw in M3 bolts to widen the tolerances on the holes for  the mounting of MPU-6050 into drone top part then cut out a piece of the stiff foam to act as a shock absorber and stand-off for the MPU-6050 and screw in the MPU-6050 to the top part of the drone. Ensure that these bolts are cut down to size so that they don't poke out of the top of the drone but fit it perfectly because the battery will be there. To mount the MPU-6050 it should be noted that it should be mounted upside down with the bolts to the right if you are looking at the drone from its rear (USB port of arduino is in rear).

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Drone_MPU_LID.jpeg)

Solder short male header wires onto D6-D9 pins of the drone arduino

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Drone_Arduino_PWMs.png)

Solder male headers onto the GND and Power wires of the USBC to bare wires cable

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Drone_USB_Headers.png)

Then mount the arduino onto the bottom part of the drone in a method identical to the one previously mentioned with the controller.

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Drone_Arduino_Mounted.png)

Then insert the M5 70mm into the top of the drone top and screw them down until they around 30mm below the top part with the rest still sticking out the top, then screw them into the base part of the drone until they just don't stick out the bottom, then screw them into the legs which are kept pressed into the bottom until they are screwed in and tighten the bolt to tighten the leg orientation and prevent wobbling.

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Drone_Frame_Assembled.png)

Solder 2.5mm male banana connectors to each bare wire of the motor (if not already attached).

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Drone_Bulltets_Motor.png)

Then also screw in the motors into the base part from the bottom with M3 bolts.

Then tape ESCs under each arm of the base part wiring up the 3 motor wires for each motor to an individual ESC. And wrap electrical tape around each joint to prevent them touching and shorting

Then connect the ESCs power together with the XT-60 1 female -> 2 male splitters connecting the left side with one splitter and the right side with one and connecting them together over the top of the top part of the drone with the third.

Then route the BEC and PWM wires of the ESC through the others to keep them in place at bottom of drone and around the sides to connect into the D6-D9 male headers
also connect the USBC 5 volt and GND to the respective 5 volt and GND of a BEC and around the drone so that it can connect to the drone arduino. Make sure that you also tape these connections (except for the XT-60 ones) to keep them secure

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Drone_Electronics_Mounted.png)

## Code

To flash the code to the arduinos you will need to install Platform IO on VS code
Libraries are already managed by Platform IO in the platformio.ini file.

<img width="390" height="143" alt="image" src="https://github.com/user-attachments/assets/f2b7b3b2-9168-4254-9a31-abd1b677980c" />

to flash connect the required arduino to the computer you are on via USB.
Select which file you want to build from the SRC filter by uncommenting it

<img width="353" height="237" alt="image" src="https://github.com/user-attachments/assets/1acd23e8-5335-461d-bd45-51830343d55f" />

source code can be found in the src folder but to get all the code as a whole just clone the repo in vscode.

You will need the mac address of your drone arduino to insert into the code manually (in the controller code). This can be done by flashing the GetMacAddress.cpp file to your drone arduino and running it, which will print the mac address of the drone in the serial monitor in a format where it can be simply copy pasted into the controller code.

Then you should calibrate the Controller by running the JoystickGetOffsets.cpp file so all values being sent are 0 when joystick is not being pushed. and these offsets should be input into the offsets for the 2 controller code versions.

flash the ControllerCode.cpp to the controller 

Then flash the bldctest.cpp to the drone arduino to see which motor is which (MOT1 should  be left stick up, MOT2 left stick right,  MOT3 right stick up, MOT4 right stick right) and swap the BEC PWM wires (D6-D9) accordingly until the correct motors get powered by the correct actions.

Then add tape to to each motor to observe its direction of spin. and swap any 2 of the 3 phase connectors between motor and ESC to change direction of spin until MOT1 and MOT4 are counter clockwise and MOT 2 and MOT 3 are clockwise. MOT1 is front left, MOT2 is front right, MOT3 is back left, MOT4 is back right, taking the back to be where the USB port of the drone arduino is.

Then Calibrate the ESCs by powering controller on with ControllerCode.cpp flashed to it with max throttle being held down and then turn on the drone from battery with ESC calibration code flashed to it after the first series of beeps are heard immediately lower throttle stick to 0 and wait until the ESCs stop beeping.

Then flash Drone code to the Drone arduino and flash ControllerCodeAltThrottle.cpp to the controller and with ESCcalibrate.cpp flashed to the drone arduino
the left stick up and down lowers and increases throttle, if let go the current throttle signal is kept, actively needs to be held down to  decrease throttle, left and right on left stick is yaw left and right, right stick left and right is x axis roll left and right, right stick up and down is y roll of drone. In the main flight mode which is the only one that actually functions well from my testing roll rate is controller by stick and drone and in the alternate one which is accessed by pressing down the right stick once will the be the angle based flight mode but i haven’t been able to get it functioning too well so be warned if using it.

Also mount the propellers onto the motors after removing the tape from them and screw the nut as tight as possible so that it doesn’t come out.
