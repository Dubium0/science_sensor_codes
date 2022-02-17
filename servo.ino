#include <ros.h>

#include <SoftwareSerial.h>

#include <Servo.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;
Servo myservo;

void servoC(const std_msgs::Int32& cmd_msg){
  if (cmd_msg.data ==0){
  for (int i =  0; i<=150;i+=2){myservo.write(i);  delay(15);   }
 delay(1000);}}


  // create servo object to control a servo
ros::Subscriber<std_msgs::Int32> sub("motor",servoC);
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {

nh.spinOnce();
delay(1);
}




  
 
                  
