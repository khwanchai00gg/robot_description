#include "Arduino.h"
#include <Servo.h>
#include <ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>
#include <stdlib.h>

#define PI 3.1415926535897932384626433832795

ros::NodeHandle  nh;
std_msgs::Float64 mydata0;
std_msgs::Float64 mydata1;
ros::Publisher chatter0("chatter0", &mydata0);
ros::Publisher chatter1("chatter1", &mydata1);

Servo servo1;
Servo servo2;

float angle[6] = {0, 0, 0, 0, 0, 0};

void cmd_cb(const sensor_msgs::JointState& cmd_arm)
{
  angle[0] = cmd_arm.position[0] * (180.0 / PI);
  angle[1] = cmd_arm.position[1] * (180.0 / PI);
  //  angle[2] = cmd_arm.position[2];
  //  angle[3] = cmd_arm.position[3];
  //  angle[4] = cmd_arm.position[4];
  //  angle[5] = cmd_arm.position[5];
  servo1.write(angle[0]); //set servo angle, should be from 0-180
  servo2.write(angle[1]); //set servo angle, should be from 0-180
}

ros::Subscriber<sensor_msgs::JointState> sub("/joint_states", cmd_cb);

void setup() {
  pinMode(13, OUTPUT);hc

  Serial.begin(57600);
  nh.getHardware()->setBaud(57600);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter0);
  nh.advertise(chatter1);
  servo1.attach(9); //attach it to pin 9
  servo2.attach(10); //attach it to pin 10
}

void loop() {
  mydata0.data = angle[0];
  chatter0.publish( &mydata0 );
  mydata1.data = angle[1];
  chatter1.publish( &mydata1 );
  nh.spinOnce();
  delay(1);
}
