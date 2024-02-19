#include "Arduino.h"
#include <Servo.h>
#include <ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/JointState.h>
#include <stdlib.h>

#define PI 3.1415926535897932384626433832795

#define potPin1 A0
#define potPin2 A1
// Define a threshold for change detection
const int threshold = 15; // Adjust this value according to your requirements

volatile int previousValue1 = 0;
volatile int previousValue2 = 0;
volatile int potValue1 = 0;
volatile int potValue2 = 0;

ros::NodeHandle  nh;
std_msgs::Float64 mydata0;
std_msgs::Float64 mydata1;
ros::Publisher chatter0("chatter0", &mydata0);
ros::Publisher chatter1("chatter1", &mydata1);

Servo servo1;
Servo servo2;

float angle[2] = {0, 0};

//void cmd_cb(const sensor_msgs::JointState& cmd_arm)
//{
//  angle[0] = (cmd_arm.position[0] / PI) * 150;
//  //  angle[0] = map(cmd_arm.position[0], 0, 3.1416, 0, 180);
//  angle[1] = cmd_arm.position[1] * 5500;
//  //  angle[1] = map(cmd_arm.position[1], 0, 0.02, 0, 110);
//  servo1.write(angle[0]); //set servo angle, should be from 0-180
//  servo2.write(angle[1]); //set servo angle, should be from 0-180
//}

//ros::Subscriber<sensor_msgs::JointState> sub("/joint_states", cmd_cb);

void cmd_servo1(const std_msgs::Float64& servo_cmd1)
{
//  angle[0] = (servo_cmd1.data / PI) * 150;
  servo1.write(servo_cmd1.data); //set servo angle, should be from 0-180
}

void cmd_servo2(const std_msgs::Float64& servo_cmd2)
{
//  angle[1] = servo_cmd2.data * 5500;
  servo2.write(servo_cmd2.data); //set servo angle, should be from 0-180
}

ros::Subscriber<std_msgs::Float64> sub0("servo1", &cmd_servo1);
ros::Subscriber<std_msgs::Float64> sub1("servo2", &cmd_servo2);

void setup() {
  pinMode(13, OUTPUT);

  Serial.begin(57600);
  nh.getHardware()->setBaud(57600);
  nh.initNode();
  nh.subscribe(sub0);
  nh.subscribe(sub1);
  nh.advertise(chatter0);
  nh.advertise(chatter1);
  servo1.attach(9); //attach it to pin 9
  servo2.attach(10); //attach it to pin 10

  // Set the interrupt pins as input
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
}

void loop() {
  mydata0.data = map(analogRead(potPin1), 0, 1024, 0, 150);
  //  chatter0.publish( &mydata0 );
  mydata1.data = map(analogRead(potPin2), 0, 1024, 0, 110);
  //  chatter1.publish( &mydata1 );
  // Read the value of the potentiometer
  //  potValue1 = analogRead(potPin1);
  //  potValue2 = analogRead(potPin2);
  //  potValue1 = map(analogRead(potPin1), 0, 1024, 0, 180);
  //  potValue2 = map(analogRead(potPin2), 0, 1024, 0, 110);

  // Check if the value has changed beyond the threshold
  if (abs(mydata0.data - previousValue1) > threshold) {
    // Print the value to Serial Monitor
    //    Serial.print("Potentiometer 1 Value: ");
    //    Serial.println(potValue1);
    //    mydata0.data = potValue1;
    chatter0.publish( &mydata0 );

    // Update the previous value
    previousValue1 = mydata0.data;
  }

  if (abs(mydata1.data - previousValue2) > threshold) {
    //    // Print the value to Serial Monitor
    //    Serial.print("Potentiometer 2 Value: ");
    //    Serial.println(potValue2);
    //    mydata1.data = potValue2;
    chatter1.publish( &mydata1 );

    // Update the previous value
    previousValue2 = mydata1.data;
  }
  nh.spinOnce();
  delay(1);
}
