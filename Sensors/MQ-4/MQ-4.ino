
const byte MQ4_Pin = A0; //MQ4 A0 pin
const int R_0 = 945; //Change this to your own R0 measurements
 
void setup() {
   Serial.begin(9600);
}
 
void loop() {
   Serial.println(getMethanePPM());
}
 
/*
* getMethanePPM returns a float value in PPM of methane concentration
*/
float getMethanePPM(){
   float a0 = analogRead(A0); // get raw reading from sensor
   float v_o = a0 * 5 / 1023; // convert reading to volts
   float R_S = (5-v_o) * 1000 / v_o; // apply formula for getting RS
   float PPM = pow(R_S/R_0,-2.95) * 1000; //apply formula for getting PPM
   return PPM; // return PPM value to calling function
}
