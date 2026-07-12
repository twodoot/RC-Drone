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
- Drone legs **x4** <br> <br>
	
- Controller Body
- Controller Lid
	
- M1.6 Spacers **16**
- M3 Spacers **20**
	
**Electronic Components**
	
- Adruino nano ESP32 without pins **x2**
- MPU-6050
- 4S 2200mah LiPo battery
- XT-60 1felmale -> 2 male splitter **x3**
- 9 volt battery
- 9 volt battery connector
- Electronic Speed Controller (ESC) at least 40amp rated **x4**
- KY-023 joystick modules **x2**
- jumper wires **many**
	
**Structural**
	
- M1.6 bolts **x8** minimum length 15mm
- M3 bolts  **x13** minimum length 18mm
- M3 bolts for motors (usually come included with motors) **x16**
- M5 bolts **x4** minimum length 73mm
	
- M1.6 Nuts **x4**
- M5 nuts **x12** 
- zip ties **x8**
- battery straps **x2**

## Assembly

### Controller:

Slice and print the Lid and Base of the controller and Spacers: files can be found ![Controller CAD Files](https://github.com/twodoot/RC-Drone/tree/main/CAD%20Files/Controller)

Wire up the Ardiuno nano ESP-32 and the joystick modules with relativly long cables so that they can be fit into the controller later easily by reffering to this wiring diagram. This will require soldering and where a 9 volt battery is mentioned in the wiring diagram solder the 9 volt battery connector between the VIN and GND of the arduino (the ground cable will require 2 cables be solderd together on a 3 way junciton as well as the 3.3V power and GND for the joysticks)

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Wiring%20Diagrams/Wiring%20Diagram%20Controller.png)

Place M1.6 spacers (or standoffs) on the M1.6 screw holes <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Nano_Standoffs.png)

Then place the arduino on top and place another spacer on top of the holes (to prevent bolt damaging it) <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Nano_Spacers.png)

Then screw M1.6 bolts through the arduino mounting holes <br> 

![images](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Nano_Bolts.png)

Do a similar process for the joystick modules sandwiching the mounting holes this time with M3 spacers and a KY-023 joystick module between. <br> 

![images](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Joystick_Spacers.png)

Then attach the battery inside the battery compartment and attach the battery connectors to the battery.<br> 

![iamge](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Battery_Compartment.png)

Finally screw on the lid with 3 M3 bolts into the lid mounting holes as shown below <br> 

![iamge](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Controller/Controller_Assembly_Lid_Bolts.png) <br> <br> 

### Drone:

Slice and print the Top and Base of the Drone and Spacers: files can be found ![Drone CAD Files](https://github.com/twodoot/RC-Drone/tree/main/CAD%20Files/Drone)

Wire up the arduino and MPU-6050 first using the wiring diagram for reference, ensure wires are kept long enough so that mounting will not be cumbersome.
Then wire up the digital pin connections to the PWMs of the ESCs and wire up A SINGLE secondary loop to power the ardiuono at 5 volts (as seen in diagram). Measuring out wires with the 3D printed base part on the table is strongly reccomeneded as the ESCs will be zip tied to the bottom of the arms of the drone base part so the wires will need to be reasonably long. The wiring for the motors and batteries can be done later as it requires no soldering.  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Wiring%20Diagrams/Drone%20Wiring%20Diagram.png)

The Arduino on the Drone will be mounted very simmilary to the one on the Controller, this time with nuts keeping it tighter in place threaded onto the bottom of the bolts below the base:  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Nano.png)
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Nano_Nuts.png)

To mount the MPU-6050 it should be noted that it should be mounted upside down with the bolts to the right if you are looking at the drone from its rear. It is also imperative that the M3 bolt used to connect the MPU to the top part not be sticking out of the top becuase the battery will be there, instead use M3 nuts or spacers to increase distance or cut the bolt to size  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_MPU.png)
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_MPU_Bolt_Length.png)

Then thread the M5 bolts first through the mounting holes on the 3D printed top part all the way, then either use a coupling nut as shown in 3D model or just 2 nuts for each bolt between the base and top to be able to adjust the height of the drone,  and thread each bolt through the base part until they just do not stick out of the bottom. Then position the landing legs at the desired angles (tilted at around 55 degrees or even more for improved balance) with an extra nut threaded inside the leg to tighten it down and thread each bolt farther and farther alternating which bolt you are tightening untill they are all the way through.  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Bolts_Just_Not_Out.png)
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Legs_Structural.png)

The ESCs should then be zip tied onto the arms of the drone on their narrower parts with 2 zip ties per ESC.  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_ESCs.png)

Then use M3 bolts to secure the motors to the arms of the drone with the wires of te motors facing their respective ESC and connect up the wires, ensureing that the front left and back right motors spin clockwise and that the front right and back left motors spin anticlockwise.  <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Motors.png)

then strap down the battery to the top of the drone using battery straps through the notches and connect it to the ESCs by making a 1-4 connector using 3 XT-60 splitters 1 female -> 2 male   <br> 

![image](https://raw.githubusercontent.com/twodoot/RC-Drone/refs/heads/main/Images/Drone/Assembly_Drone_Battery.png)  <br>  <br> 

## Code

To flash the code to the arduinos you will need to install PlatformIO on github.
Libraries are already managed by Platform io in the platformio.ini file.
to flash connect the required arduino to the computer you are on via usb.
source code can be found in the src folder but to get all the code as a whole just clone the repo in vscode.

You will need the macadress of your drone arduino to insert into the code manually (in the controller code). This can be done by flashing the getmacadress file to your drone arduino and running it, which will print the mac adress of the drone in the serial monitor in a format where it can be simply copy pasted into the controller code.

In its current state I have not yet tuned the PID controllers but I will provide updated code with tuned controllers after I build and calibrate it myself.
