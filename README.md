# RC Drone
	
This is a project in which I am making an RC Drone and controller from scratch with 2 arduino nano ESP32s.  <br>   
Both the Drone and Controller are 3D printed in 2 main parts, and assembled with various sized bolts, nuts and standoffs, (as well as 4 3d printed landing legs for the drone).  <br>  
I'm making this project for personal experience in hardware and software design as it is my first embedded system project. <br>  
	
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Drone/Drone_Image_1.png) <br> Image of Drone CAD <br> <br>
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Drone/Drone_Image_2.png) <br> Top view of Drone CAD <br> <br>
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Image_1.png) <br> Controller CAD with lid <br> <br>
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller/Controller_Image_2.png) <br> Controller CAD without lid <br> <br>
	
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
- male terminal banana connectors 2.5mm (for soldering not crimping) **x12**
- 2400kv brushless DC motors **x4**
- drone propellers (recommended  5.1x3.6x3) **x4** 
	
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
- sandpaper low grit
- hacksaw
- soldering iron (and solder and a sponge)
- multimeter (for debugging in case you run into issues assembling)
- scissors
- pliers

## Assembly

### Controller:

Slice and print the Lid and Base of the controller files can be found: ![Controller CAD Files](https://github.com/twodoot/RC-Drone/tree/main/CAD%20Files/Controller)

solder wires with female headers onto the relevant pins of the arduino as seen in the wiring diagram below if you are unsure of my following description, ensuring they are large enough to reach the joystick pins when inside the controller but not too much longer so that the wires can fit inside easily. to the A0-A3 and to D3 solder wires with female headers, and then make 2 wires that have 3 way connectoins stripping a section of casing off the middle off one wire with a female header and soldering another wire with a female header to it. Cover all exposed wires with either heat shrinks (if you have any) or electrical tape (what I did). 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Wiring%20Diagrams/Wiring%20Diagram%20Controller.png)

sand down the Drawer until it fits stiffly into the body slot for the power bank underneath but doesn't  slide out easily.

first screw in and screw out M1.6 bolts out of the arduino stand-off locations on the controller to widen the tolerances.

cut off 8 thin bits of the plastic tubing between 1-2mm in length but keep it consistent between the 8.

fit one stand-off through each M1.6 bolt and then put them on the arduino through the top (USB port is on top) then on the bottom put the other 4 stand-offs sandwiching the arduino between them.
place the arduino on top of the holes M1.6 holes and screw in the bolts first screwing in all the bolts a small amount until they are all in the threads then taking turns slowly screwing them in until all are screwed in tight and the arduino doesn't wobble.

screw in and out M2.5 bolts a small amount into each mounting hole to widen tolerances and make it easier to screw in joystick modules

cut a rectangle of foam around the base of one of the joystick modules then cut it down to only about 3mm thick and repeat for the other one. thread M2.5 bolts through the mounting holes on each joystick modules and through the foam until it just is about to poke through the bottom then put the joysticks with the attached foam pads on top of the joystick mounting holes and screw them in. ensure the joystick modules are screwed in with the pins facing the arduino.

connect the wires up to the joystick modules: GND to GND to each module, 3.3V to +5V to each module, A3 to VRX of left joystick, A2 to VRY of left module, A1 to VRX of right module, A0 to VRY of right joysick, D3 to the SW of right joystick.

connect a USBC to USBA cable that just reaches the power bank underneath to the slot on the arduino for it.

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Nano_Standoffs.png)

**4.** Then place the arduino on top and place another spacer on top of the holes (to prevent bolt damaging it) <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Nano_Spacers.png)

**5.** Then screw M1.6 bolts through the arduino mounting holes <br> 

![images](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Nano_Bolts.png)

**6.** Do a similar process for the joystick modules sandwiching the mounting holes this time with M3 spacers and a KY-023 joystick module between. <br> 

![images](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Joystick_Spacers.png)

**7.** Then attach the battery inside the battery compartment and attach the battery connectors to the battery.<br> 

![iamge](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Battery_Compartment.png)

**8.** Finally screw on the lid with 3 M3 bolts into the lid mounting holes as shown below <br> 

![iamge](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Lid_Bolts.png) <br> <br> 

### Drone:

**1.** Slice and print the Top and Base of the Drone and Spacers: files can be found ![Drone CAD Files](https://github.com/twodoot/RC-Drone/tree/main/CAD%20Files/Drone)

**2.** Wire up the arduino and MPU-6050 first using the wiring diagram for reference, ensure wires are kept long enough so that mounting will not be cumbersome.
Then wire up the digital pin connections to the PWMs of the ESCs and wire up A SINGLE secondary loop to power the ardiuono at 5 volts (as seen in diagram). Measuring out wires with the 3D printed base part on the table is strongly reccomeneded as the ESCs will be zip tied to the bottom of the arms of the drone base part so the wires will need to be reasonably long. The wiring for the motors and batteries can be done later as it requires no soldering.  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Wiring%20Diagrams/Drone%20Wiring%20Diagram.png)

**3.** The Arduino on the Drone will be mounted very simmilary to the one on the Controller, this time with nuts keeping it tighter in place threaded onto the bottom of the bolts below the base:  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Nano.png)
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Nano_Nuts.png)

**4.** To mount the MPU-6050 it should be noted that it should be mounted upside down with the bolts to the right if you are looking at the drone from its rear. It is also imperative that the M3 bolt used to connect the MPU to the top part not be sticking out of the top becuase the battery will be there, instead use M3 nuts or spacers to increase distance or cut the bolt to size  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_MPU.png)
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_MPU_Bolt_Length.png)

**5.** Then thread the M5 bolts first through the mounting holes on the 3D printed top part all the way, then either use a coupling nut as shown in 3D model or just 2 nuts for each bolt between the base and top to be able to adjust the height of the drone,  and thread each bolt through the base part until they just do not stick out of the bottom. Then position the landing legs at the desired angles (tilted at around 55 degrees or even more for improved balance) with an extra nut threaded inside the leg to tighten it down and thread each bolt farther and farther alternating which bolt you are tightening untill they are all the way through.  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Bolts_Just_Not_Out.png)
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Legs_Structural.png)

**6.** The ESCs should then be zip tied onto the arms of the drone on their narrower parts with 2 zip ties per ESC.  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_ESCs.png)

**7.** Then use M3 bolts to secure the motors to the arms of the drone with the wires of te motors facing their respective ESC and connect up the wires, ensureing that the front left and back right motors spin clockwise and that the front right and back left motors spin anticlockwise.  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Motors.png)

**8.** then strap down the battery to the top of the drone using battery straps through the notches and connect it to the ESCs by making a 1-4 connector using 3 XT-60 splitters 1 female -> 2 male   <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Battery.png)  <br>  <br> 

## Code

To flash the code to the arduinos you will need to install PlatformIO on github.
Libraries are already managed by Platform io in the platformio.ini file.
to flash connect the required arduino to the computer you are on via usb.
source code can be found in the src folder but to get all the code as a whole just clone the repo in vscode.

You will need the macadress of your drone arduino to insert into the code manually (in the controller code). This can be done by flashing the getmacadress file to your drone arduino and running it, which will print the mac adress of the drone in the serial monitor in a format where it can be simply copy pasted into the controller code.

In its current state I have not yet tuned the PID controllers but I will provide updated code with tuned controllers after I build and calibrate it myself.
