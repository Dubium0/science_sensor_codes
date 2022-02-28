 #include <Servo.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <Wire.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
//pump pins
#define A1  51
#define A2  49
#define A3  47
#define A4  45
#define m1  39
#define m2  37
#define m3  35
#define m4  33
int pos = 0;

// defines pins numbers
const int tubeStepPin = 9; 
const int tubeDirPin = 8; 

const int shovelStepPin = 11; 
const int shovelDirPin = 12;

bool isShovelDown = false;


Servo myservo;  // create servo object to control a servo


ros::NodeHandle nh;
std_msgs::String allSensor_msg;
bool p1,p2,p3,p4;

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

void waterPumps(const std_msgs::Float32& cmd_msg) 
    {
     
      
    
    if (cmd_msg.data == 1){

        digitalWrite(A1,1);
        digitalWrite(A2,0);
        
         digitalWrite(A3,0);
        digitalWrite(A4,1);
        
        digitalWrite(m1,1);
        digitalWrite(m2,0);
        
         digitalWrite(m3,1);
        digitalWrite(m4,0);
     }
     
    else if (cmd_msg.data == 2 ){
     
        stopMotors();

      }
/*
    else if (cmd_msg.data == 3 ){

        digitalWrite(m1,0);
        digitalWrite(m2,1);
      
      }
    else if (cmd_msg.data == 4 ){

        digitalWrite(m3,1);
        digitalWrite(m4,0);      
      }

       else if (cmd_msg.data == 5 ){
        digitalWrite(A1,0);
        digitalWrite(A2,0);
      }
        else if (cmd_msg.data == 6 ){

        digitalWrite(A3,0);
        digitalWrite(A4,0);
      
      }
        else if (cmd_msg.data == 7 ){

        digitalWrite(m1,0);
        digitalWrite(m2,0);
      
      }
        else if (cmd_msg.data == 8 ){

           digitalWrite(m3,0);
           digitalWrite(m4,0);
      
        }
      */
      
      
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
    delayMicroseconds(500); 
    digitalWrite(shovelStepPin,LOW); 
    delayMicroseconds(500); 
  }
  // One second delay
  delay(1000);
}

void shovelServo(const std_msgs::Float32& cmd_msg)
{
  
  if (cmd_msg.data ==1) {
    for (pos = 0; pos <= 15; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                   // waits 15ms for the servo to reach the position 
  }
  delay(1000);
  for (pos = 15; pos <= 130; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
                delay(15);           // waits 15ms for the servo to reach the position 
  }
  
  }

  else if (cmd_msg.data ==0) 
  {

    for (pos = 130; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
	
  }
  }
 
  
  }



ros::Publisher Sensors("SENSORS",&allSensor_msg);

ros::Subscriber<std_msgs::Float32> Tubes("tubes",tubes);
ros::Subscriber<std_msgs::Float32> ShovelUp("shovelUp",shovelUp);

ros::Subscriber<std_msgs::Float32> ShovelDown("shovelDown",shovelDown);
ros::Subscriber<std_msgs::Float32> WaterPumps("waterPumps",waterPumps);
ros::Subscriber<std_msgs::Float32> ShovelServo("shovel",shovelServo);
 
void setup() {

   pinMode(tubeStepPin,OUTPUT); 
  pinMode(tubeDirPin,OUTPUT);
    pinMode(shovelStepPin,OUTPUT); 
  pinMode(shovelDirPin,OUTPUT);
    pinMode(A1,OUTPUT);
   pinMode(A2,OUTPUT);
    pinMode(A3,OUTPUT);
     pinMode(A4,OUTPUT);
         pinMode(m1,OUTPUT);
   pinMode(m2,OUTPUT);
    pinMode(m3,OUTPUT);
     pinMode(m4,OUTPUT);
     p1=false;
     p2=false;
     p3=false;
     p4=false;
     myservo.attach(41);


    
  nh.initNode();
  nh.advertise(Sensors);
  nh.subscribe(Tubes);
  nh.subscribe(ShovelDown);
  nh.subscribe(ShovelUp);
  nh.subscribe(WaterPumps);
  nh.subscribe(ShovelServo);
}
  
void loop() {
  
   readData();
   nh.spinOnce();
   delay(1);
   
}


void stopMotors() {
    digitalWrite(A1,0);
        digitalWrite(A2,0);
         digitalWrite(A3,0);
        digitalWrite(A4,0);

          digitalWrite(m1,0);
        digitalWrite(m2,0);
         digitalWrite(m3,0);
        digitalWrite(m4,0);
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


  
 
                  
