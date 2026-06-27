# RC Drone
	
This is a project in which I am making an RC Drone and controller from scratch with 2 arduino nano ESP32s.  <br>   
Both the Drone and Controller are 3D printed in 2 main parts, and assembled with various sized bolts, nuts and standoffs, (as well as 4 3d printed landing legs for the drone).  <br>  
I'm making this project for personal experience in hardware and software design as it is my first embedded system project. <br>  
	
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Drone_Image_1.png) Image of Drone CAD <br> <br>
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Drone_Image_2.png) Top view of Drone CAD <br> <br>
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller_Image_1.png) Controller CAD with lid <br> <br>
![image](https://raw.githubusercontent.com/twodoot/RC-Drone/main/Images/Controller_Image_2.png) Controller CAD without lid <br> <br>
	
## Parts List
	
**3D Printed:**
- Drone Base
- Drone Top 
- Drone legs **x4** <br> <br>
	
- Controller Body
- Controller Lid
	
(where standoffs are mentioned in CAD spacers can be used instead and where M2.5 is mentioned in CAD M3 can be used)
	
- M1.6 Spacers **16**
- M3 Spacers **12**
	
**Electronic Components**
	
- Adruino nano ESP32 without pins **x2**
- MPU-6050
- 4S 2200mah LiPo battery
- XT 1felmale -> 2 male splitter **x3**
- 9 volt battery
- 9 volt battery connector
- Electronic Speed Controller (ESC) at least 40amp rated **x4**
- KY-023 joystick modules **x2**
- jumper wires **many**
	
**Structural**
	
(for bolts minimum length refers to the longest bolt of that length as rest can be cut to size) <br>
	
- M1.6 bolts **x8** minimum length ..mm
- M3 bolts  **x11** minimum length ..mm  (where I said M2.5 on CAD for the Controller I'm almost certain M3 would work but I will test when I assemble the drone)
- M5 bolts **x4** minimum length ..mm
	
- M1.6 Nuts **x4** (optional)
- M3 nuts **x8**
- M5 nuts **x12** (where the coupling nut is seen on CAD 2 regular nuts per each can be used instead)
- zip ties **x8**
- battery straps **x2**

## Assembly

Assembly of drone and controller will require soldering to solder wires to the pin less components as well as to potentially solder wires together for extension if requried
most of the assmebly can be done by refering to the wiring diagrams in ...

the ESCs will need to be strapped onto the arms of the drone using zip ties and the battery will be strapped to the top using battery straps into the notches in the top.

more detailed asseblyt construction will be provided after I assemble to drone myself

## Code

To flash the code to the arduinos you will need to install PlatformIO on github.
Libraries are already managed by Platform io in the platformio.ini file.
to flash connect the required arduino to the computer you are on via usb.
source code can be found in the src folder but to get all the code as a whole just clone the repo in vscode.

You will need the macadress of your drone arduino to insert into the code manually (in the controller code). This can be done by flashing the getmacadress file to your drone arduino and running it, which will print the mac adress of the drone in the serial monitor in a format where it can be simply copy pasted into the controller code.
