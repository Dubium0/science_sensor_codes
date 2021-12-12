
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
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  nh.initNode();
  nh.advertise(Sensors);
}
  
void loop() {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
    Serial.println(" meters");
    
    Serial.println();

    String temperature =  String(bmp.readTemperature());
    String pressure =  String(bmp.readPressure());
    String altitude =  String(bmp.readAltitude());
    String alldatas = temperature + "," + pressure + "," + altitude;
    Serial.print("Alldatas = ");
    Serial.print(alldatas);
    Serial.println();

    basinc_msg.data = alldatas.c_str();
    Sensors.publish( &basinc_msg );
    nh.spinOnce();
    
    delay(500);
}
