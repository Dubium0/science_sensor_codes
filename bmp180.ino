
#include <ros.h>
#include <std_msgs/String.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;
ros::NodeHandle nh;
std_msgs::String basinc_msg;

ros::Publisher Sensors("SENSORS",&basinc_msg);
void setup() {
  bmp.begin(); 
  nh.initNode();
  nh.advertise(Sensors);
}
  
void loop() {
    String temperature =  String(bmp.readTemperature());
    String pressure =  String(bmp.readPressure());
    String altitude =  String(bmp.readAltitude());
    String alldatas = temperature + "," + pressure + "," + altitude;

    basinc_msg.data = alldatas.c_str();
    Sensors.publish( &basinc_msg );
    nh.spinOnce();
    
    delay(500);
}
