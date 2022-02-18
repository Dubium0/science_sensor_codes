
#include <ros.h>
#include <std_msgs/String.h>
#include <Wire.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>

// defines pins numbers
const int tubeStepPin = 9; 
const int tubeDirPin = 8; 

const int shovelStepPin = 11; 
const int shovelDirPin = 12;


ros::NodeHandle nh;
std_msgs::String allSensor_msg;

void tubes(const std_msgs::Float32& cmd_msg){

   
    digitalWrite(tubeDirPin,LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(float x = 0; x < cmd_msg.data; x++) {
    digitalWrite(tubeStepPin,HIGH); 
    delayMicroseconds(800); 
    digitalWrite(tubeStepPin,LOW); 
    delayMicroseconds(800); 
  }
  // One second delay
  
 delay(1000); 
 
}

void shovelUp(const std_msgs::Float32& cmd_msg){

    digitalWrite(shovelDirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(float x = 0; x < cmd_msg.data; x++) {
    digitalWrite(shovelStepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(shovelStepPin,LOW); 
    delayMicroseconds(500); 
  }
  // One second delay
  delay(1000);
 
}

void shovelDown(const std_msgs::Float32& cmd_msg){

    digitalWrite(shovelDirPin,LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(float x = 0; x < cmd_msg.data; x++) {
    digitalWrite(shovelStepPin,HIGH); 
    delayMicroseconds(800); 
    digitalWrite(shovelStepPin,LOW); 
    delayMicroseconds(800); 
  }
  // One second delay
  
 delay(1000);
 
}


ros::Publisher Sensors("SENSORS",&allSensor_msg);

ros::Subscriber<std_msgs::Float32> Tubes("tubes",tubes);
ros::Subscriber<std_msgs::Float32> ShovelUp("shovelUp",shovelUp);

ros::Subscriber<std_msgs::Float32> ShovelDown("shovelDown",shovelDown);

 
void setup() {

   pinMode(tubeStepPin,OUTPUT); 
  pinMode(tubeDirPin,OUTPUT);
    pinMode(shovelStepPin,OUTPUT); 
  pinMode(shovelDirPin,OUTPUT);
  nh.initNode();
  //nh.advertise(Sensors);
  nh.subscribe(Tubes);
  nh.subscribe(ShovelDown);
  nh.subscribe(ShovelUp);
}
  
void loop() {
  
   //readData();
   nh.spinOnce();
   delay(1);
}


void readData(){

  
   String gas = String(analogRead(A5)); // MQ-2
    String methan = String(analogRead(A6)); // MQ-4
    String carbonMono = String(analogRead(A1)); // MQ-7
    String karbon = "135";
    String alldatas = gas + "," + methan + "," + carbonMono +","+ karbon;
     
  
    allSensor_msg.data = alldatas.c_str();
    
    Sensors.publish( &allSensor_msg );
}


  
 
                  
