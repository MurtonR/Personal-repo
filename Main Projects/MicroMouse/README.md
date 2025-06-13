# MicroMouse Project Repo
## Overview:

- The goal of this project is to create a functional MicroMouse that is able to navigate through a maze to reach an end position.<br>
- This project will have documentation to ensure that it could be repeated without difficulty.
## Notion Log:

- This notion documents my progress in this project, it includes select drawings, code snippets and information of how each major step in the project was achieved.<br>
- Notion Link: https://www.notion.so/Development-Log-207-10dfe3942e8a80e990e4eb2578364845
- [DevLog-207.pdf](https://github.falmouth.ac.uk/RM305181/COMP207-project/files/41/DevLog-207.pdf)
## Objectives:

- Design a PCB that has the required components for the MicroMouse<br>
- Design required elements in Fusion 360 (i.e Wheels, Shell, Motor Mounts)<br>
- Solder components to the PCB and test for functionality<br>
- 3D print and attach to PCB<br>
- Code maze navigation and iterate until it reaches the end position.<br>
## Repo Organisation:

* CAD<br>
  - Assemblies<br>
  - Fusion<br>
  - Mesh<br>
  - dxf<br>
  - stl<br>
* Code
  - Comp207_Test_Code
  - Comp207_Main_Code
* Documentation<br>
  - Drawings<br>
  - datasheets<br>
* Electronics
* media
  - Renders
# Guide for replication
-This segment is a guide to replicate each step in this project<br>
## Components
* Pi Pico - C7203003
* Motor Driver(L293D) - C12340
* Proximity Sensor(TCRT5000) - C2984661
* Switch - C2939728
* Voltage Regulator (L7805) - C347289
* DC Motors (12V N20)
* Various M-M and M-F Jumper Wires
* Resistors (1k and 330)
  
## EasyEDA

* The first step is to made a schematic sheet for your PCB, this will include all of the components for the MicroMouse project and how they are connected.<br>
[Schematic_Timothy-Q.Mouse_2024-10-26.pdf](https://github.falmouth.ac.uk/RM305181/COMP207-project/files/36/Schematic_Timothy-Q.Mouse_2024-10-26.pdf)

* The next step is to use this schematic to make a layout that will be used as the base for all the other elements of the Mouse. <br>
* First create a 3D model of the PCB with the desired width and length in Fusion 360, by creating a sketch on the flat face of this model we can save it as a dxf.<br>
![PCB Drawing](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/609491fb-c242-4aab-9ccf-a6c0b6f26bbd)

* Import the dxf file into easyEDA, this will provide us with a 1:1 copy that will allow us to use our model in Fusion 360 as a base for other components (Shell, Motor Mounts).<br>
* The next step is to place the components onto the board outline, there are some basic rules to follow that will make this much easier:<br>
![Board Outline](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/23147df5-7b96-4c5f-aca7-d68eee883f89)
     - Number one rule to make sure all of the components are not overlapping, they are fully on the board and that they do not cover the mounting holes.<br>
     - Place core components such as the pico and motor driver first, this means we can ensure good positioning for both.<br>
     - When placing TCRT's ensure they are fully on the board and facing the correct directions, whether you position them 45 or 90 degrees relative to the front of the MicroMouse is up 
       to you<br>
     - When placing related components (LED and Resistor for example) ensure they are placed close together to make it easier to solder and identify how it works should you forget.<br>
     - Adding a silkscreen with important info about where, when and who constructed the PCB is important for documentation<br>
     - When routing the wires double check every connection before you finalise the design, any incorrect connection could cause shorting or power to flow incorrectly (easyEDA should 
       warn you if there are any issues but it is good practise to double check yourself) <br>
     - Shorter paths lead to decreased resistance so make sure that you aren't taking unnecessarily long routes, this will require changing the layout of components many times to find 
       the best layout for you <br>

At the end it should look something like this:
![PCB Layout Basic](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/d08df1c3-0645-4f89-a912-e42772dd0ee1)

## Fusion 360

* In order to attach the wheels, protect the PCB and balance the MicroMouse we will need to add additional components that will either be 3D printed or Lasercut.
* Let's start with the motor, this will be used to 
![Motor Drawing](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/2c4a0b7f-64cb-462b-a5f6-4cb858dd4d56)
* Using this we can then make the motor mount from these dimensions, remember to add the mounting holes to the motor mount to make connecting it to the PCB simple.
  - To get the motor hole correct we can use the dimesions from the motor model and use this to create correctly sized sketches. However we need to print the hole slightly bigger than the dimensions, as the 3D printing will reduce the diameter.
![Square + Circle](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/c854d035-4e59-4c9c-8d89-8d7affe9e2fa)
  - 3D prints usually print better with more edges, to do this we can either use the chamfer or filet tools, in this case I've used chamferring but either will do.
![Chamferring](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/1eefa9a6-d32c-4930-a602-ebaf14432dbc)

![MotorMount Drawing](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/39df3187-e0a8-433d-bc21-0221b7a3cfd4)
* Additional parts such as a balance or shell could be helpful to keep the mouse upright and protected from bumps
![Shell Drawing](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/0352def0-03f2-4205-823b-e9db2f8ced22)

* When designing a 3D model for laser cutting take into account the fact that the object can only have features on a single face, so more complex desings will have to be made from multiple seperate pieces that are laser cut.
* A wheel is a good example of an appropriate use case for using lasercutting, another would be cutting an acrylic screen that can be used to see the components while still providing protection for the other components.
![Wheel Drawing](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/d744bbec-ce6a-4912-aa1c-d0804bf5d231)
![AcrylidLid Drawing](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/f31a84fb-6f58-4452-81ff-a711e57e0a40)


* The overall assembly should look something like this once you're done, however feel free to customise it as much as you want.
![FullAssembly Drawing](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/d414fb49-00d4-4290-9152-65d8fb129f39)
![Full Assembly Render](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/b2fead95-fc60-440d-9fb4-22b5fa05e6f0)


## Code
* The code consists of a state machine, this determines what the robot should do next depeding on the inputs from the 3 infared sensors.

* The first code snippet contains the functions used for the movement of the MicroMouse, with the forwardMovement function being the most complex.
  - The map function maps the values received from the TCRT to the range of the motors, this is inversed so a small distance leads to a large increase in power to the motor

* The second code snippet contains the code for the state machine. It has 4 states, one for turning left and right, another for when the robot meets a crossroad and finally one for moving forward.
  - The code for sensing takes place in the loop, this is for simplicity.
    
```csharp
void turnLeft() {  //Turns left and then continues for a short time
  motorDriving(-100 , motorLB, motorLA);
  motorDriving(motorSpeed, motorRA, motorRB);
}
void turnRight() {  //Turns right and then continues for a short time
  motorDriving(motorSpeed, motorLA, motorLB);
  motorDriving(-100, motorRB, motorRA);
}
void wallInfront() {  //Decides which way to turn depending on the closest distance and then turns
  if (analogRead(leftTCRT) < analogRead(rightTCRT)) {
    motorDriving(-motorSpeed, motorLB, motorLA);
    motorDriving(motorSpeed, motorRA, motorRB);
    delay(500);
  } else {
    motorDriving(motorSpeed, motorLA, motorLB);
    motorDriving(-motorSpeed, motorRB, motorRA);
    delay(500);
  }
}
void forwardMovement() {  //Moves the mouse forwards should accomodate to ensure it stays in the middle of the path by adjusting the amount of power to each wheel depending on the distance
  float right = map(analogRead(leftTCRT), 800, 1030, 20,30 );
  float left = map(analogRead(rightTCRT), 800, 1030, 20,30);
  Serial.println(left);
  Serial.println(right);
  motorDriving(left, motorLA, motorLB);
  motorDriving(right, motorRA, motorRB);
}
```

```csharp
void mouseStates(uint8_t Sensor_enum) {//each state has a LED that only lights up when it is active
  switch (mouse) {
    case FORWARD:  //Set the state depending on which direction walls are detected in, if there are no walls go forward
      if (sensor == LEFT) {
        timer = millis();
        mouse = TURNRIGHT;
      }
      if (sensor == MIDDLE) {
        mouse = CROSSROAD;
      }
      if (sensor == RIGHT) {
        timer = millis();
        mouse = TURNLEFT;
      }
      if (sensor == NONE) {
        forwardMovement();
      }
      break;
    
    case CROSSROAD:
      if (sensor != MIDDLE) {  //For each of these states a corrosponding LED will light up to signify that they are the active state
        mouse = FORWARD;
        digitalWrite(blueLED, LOW);
      } else {
         digitalWrite(blueLED, HIGH);
        wallInfront();
       
      }
      break;

    case TURNLEFT:  //The timer means that the robot will turn for a specified amount of time, allowing it to make corners with less collisions
      if (millis() - timer >= 20) {
        digitalWrite(redLED, LOW);
        mouse = FORWARD;

      } else {
        digitalWrite(redLED, HIGH);
        turnLeft();
      }
      break;

    case TURNRIGHT:
      if (millis() - timer >= 20) {
        digitalWrite(yellowLED, LOW);
        mouse = FORWARD;
      } else {
        digitalWrite(yellowLED, HIGH);
        turnRight();
      }
      break;
  }
}
```
## Final PCB and Physical Design
* Here is an example PCB:
![PCB Basic](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/d501b754-8014-48eb-9dca-95960a4ff34f)

* Once you get your PCB the next step is to solder the components on , there are a few things that you need to keep in mind when soldering.
  - Ensure that the solder is fully connected to the component and board, any gaps or places with not enough may not work. Better to double check the connections now then have issues 
    once all the components are connected and issues are harder to fix.
  - Be careful that you don't solder different components together with stray solder, this can be very dangerous and may lead to a short circuit or non functioning circuits.
  - Referrence your schematic and layout to ensure that all the components are connected in the correct orientation.
  - This is when arranging your components efficiently helps massively, it is much simpler to add components when the arrangement and orientation makes sense.
* Here is a example of a PCB with all of the components connected:
![PCB with Components](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/e0ece3f1-342a-487d-8701-436f61563b65)


* You may want to make a battery that can be used with this MicroMouse project, in this case I've used two recycled llithium-ion vape batteries connected with wires in this arrangement:<br>
![Battery diagram](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/d66adb73-938f-4dd9-8405-b152450b0610)<br>
-Remember to tape up the battery, you don't want the movement of the MicroMouse to pull a wire loose!

## Acting on Feedback 
* I gathered feedback from my peers and used this to improve upon this project. <br>
[Market research- revan.docx](https://github.falmouth.ac.uk/RM305181/COMP207-project/files/38/Market.research-.revan.docx)

### Inital comments on feedback
* One consistent feedback was that the shell is unstable and doesn't fit correctly, along with the aesthetics being off. Improving this would help to make the bot look sleeker.
* The physical design of the robot was the element that was unanimously disliked, this was not a suprise but the feedback given focused mainly on the shell with some mentions of the motors being hot glued to the motor mounts. Although this is not ideal I don't have the time to fix this given it doesn't affect the movement at this moment, If i have enough time this will be one of my main focuses.
  
* Another piece of feedback is how parts of the code are uncommented, I’ll fix this as well commented cpde can make understanding the code much easier and will help if I need to go back and change the code at a later date.

* Need to add technical drawings, as at the moment there is little documentation for the CAD inside the github, this makes the project easier to replicate and provides exact dimensions

### Improvements made
* To hopefully remedy this I’ve moved onto a new idea of making a roof that is held up using the m3 bolts and should provide room for the battery, also it should be more secure and 
  allow the robot to be powered on with the switch more easily. The original shell was far too complex and didn't have any way of connected securely to the PCB
* Original Shell:
![Shell Render](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/9d1aa338-20f6-4dab-92d6-505e9b1103ce)

* Updated Shell:
![Roof Assembly Render](https://github.falmouth.ac.uk/RM305181/COMP207-project/assets/2282/db0b89c6-736b-43c0-ac19-ebda2daa5fbc)

* The code is now commented, one part that I may need to improve on is how detailed each comment is. I've tried to avoid the comments just repeating the code line by line and instead have focused on describing what each chunk of code should do, to hopefully help give more context.

* Drawings have been added for the majority of the parts and added to the documentation folder.
