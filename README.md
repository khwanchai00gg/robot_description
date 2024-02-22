# RP Potentiometer 2 joint robot
robot arm 2joint project


# Reqired hardware
- Robot parts or assembled robot
- 2 of Hypertech servo ah1500a or similar servo with the same diameter
- 2 Potentiometer as input to control the joints one for R and one for P
- We use Arduino UNO R3 as a microcontroller (You can use other microcontrollers as long as they work on Arduino)
- Breadboard to put the circuit together
- Wires to connect the input and circuit between the robot and microcontroller
- USB-B to connect to the Arduino
- Computer that installed ROS
- Power source to the Arduino and Servos


# Asembly hardware 
You will see that the meshes folder will have the STL files for the robot (https://github.com/khwanchai00gg/robot_description/tree/main/robot_description/meshes)
you can print and assemble them with those parts or with your design.

Put all the Hardware GND wires connected to the same wire connect
Put all the Hardware Vin wires connected to the same wire and one wire to the 6volt power source (If you use another kind of servo that needs more than 6V you have to connect them to the voltage you have used)
**Do not connect wires while you turn the power on

You can define where the pin with this data sheet if you use Arduino UNO R3 https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf

The first Protentionmeter put into pot Pin1 A0 
The Second Protentionmeter put into pot Pin A1

The Signal wire on the R servo was put in the pot Pin 9
The Signal wire on the P servo was put in the pot Pin 10

and connect Arduino to your computer

# Required Software 
- Arduino IDE ( Link https://www.arduino.cc/en/software )

- ROS on Ubuntu (We use ROS noetic you can follow this step to install them https://wiki.ros.org/noetic/Installation/Ubuntu )

- Rvis on Ubuntu  (This is how to install them with ROS noetic http://wiki.ros.org/rviz/UserGuide )


# Set up before launch

- Upload "Project_Servo_ros.ino" to your Arduino controller (https://github.com/khwanchai00gg/robot_description/tree/main/Project_Servo_ros)
- Make a folder in your ROS workspace
- Open terminal in Ubuntu
- Create a package that will put all files in the ["robot_description"](https://github.com/khwanchai00gg/robot_description/tree/main/robot_description) with

```ruby
 catkin_create_pkg <your package name>
```
- Then go back to your workspace and use
  
```ruby
 catkin_make
```
when everything is done put all files in (https://github.com/khwanchai00gg/robot_description/tree/main/robot_description)https://github.com/khwanchai00gg/robot_description/tree/main/robot_description to your package folder

- Then go back to your workspace and use
  
```ruby
 catkin_make
```

go back to your package files and use this in the terminal
- Then go back to your workspace and use
- ** We use a virtual machine to run and code in Ubuntu so you need to change everything that "ttyACM0" to your USB port name
  
```ruby
 chmod +x Robot.launch
 chmod +x ROS_GUI_SERVO.py
 chmod +x robot.urdf
 sudo chmod a+rw /dev/ <your USB port name>
```
- go back to catkin_ws and

```ruby
 catkin_make
source ~/catkin_ws/devel/setup.bash
```

# Circuit diagram

![Screenshot 2024-02-22 104146](https://github.com/khwanchai00gg/robot_description/assets/54237112/388cfc9d-b543-4f89-ba89-4170a4723116)

![Screenshot 2024-02-22 104516](https://github.com/khwanchai00gg/robot_description/assets/54237112/03ac814c-2e16-4f60-9b37-c734c632005c)

![Screenshot 2024-02-22 104847](https://github.com/khwanchai00gg/robot_description/assets/54237112/fd1cf3e8-b91d-4184-baaf-800e51b37c97)

# Launch the Robot

Open the terminal and put this command

```ruby
 roscore
```

Then open another terminal go to your workspace and
```ruby
 roslaunch <your package name > Robot.launch 
```
to launch the robot

#RQT graph
You can check the node of ROS system while you active the robot with 
```ruby
 rqt_grph

```
Then you may see like this

![RQT](https://github.com/khwanchai00gg/robot_description/assets/156043362/8e1a341e-988f-4c5c-a3bb-b95a9d1bfea1)

Everything should be work here

When everything works it will show up Avriz and GUI, Avriz will show how your robot properly moves if you control the robot either with GUI or Potentiometer

![Screenshot 2024-02-22 105152](https://github.com/khwanchai00gg/robot_description/assets/156043362/ab7ab830-6a6c-4b49-98b8-7b1e6a7054be)

![Screenshot 2024-02-22 105134](https://github.com/khwanchai00gg/robot_description/assets/156043362/e36d9c9b-7cca-4b70-9883-1a51fa67a91e)
