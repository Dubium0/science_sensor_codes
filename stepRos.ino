
// defines pins numbers
const int stepPin = 9; 
const int dirPin = 8; 
#include <ros.h>

#include <SoftwareSerial.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;

void servoC(const std_msgs::Float32& cmd_msg){

    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(float x = 0; x < cmd_msg.data; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(800); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(800); 
  }
  // One second delay
  
 delay(1000); 
 
 }

ros::Subscriber<std_msgs::Float32> sub("motor",servoC);

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}
void loop() {

  nh.spinOnce();
delay(1);
}
