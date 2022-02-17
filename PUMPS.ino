
#include <ros.h>

#include <SoftwareSerial.h>

#include <Servo.h>
#include <std_msgs/Int32.h>

#define A1  51
#define A2  49
#define A3  47
#define A4  45

ros::NodeHandle nh;
Servo myservo;

void servoC(const std_msgs::Int32& cmd_msg){
  if (cmd_msg.data ==1){
    digitalWrite(A1,1);
    digitalWrite(A2,0);
    digitalWrite(A3,0);
    digitalWrite(A4,0);
    
    }
   else if (cmd_msg.data == 0 ){
    digitalWrite(A1,0);
    digitalWrite(A2,0);
    digitalWrite(A3,1);
    digitalWrite(A4,0);
    
    }
  
  
  
  
  
  
  }
  


  // create servo object to control a servo
ros::Subscriber<std_msgs::Int32> sub("motor",servoC);
void setup() {
  pinMode(A1,OUTPUT);
   pinMode(A2,OUTPUT);
    pinMode(A3,OUTPUT);
     pinMode(A4,OUTPUT);

 
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {

nh.spinOnce();
delay(1);
}




  
 
                  
