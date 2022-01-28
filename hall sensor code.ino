const int pinHall = A0; 
int counter = 0 ;
int counter2 = 0 ;
unsigned long myTimeStart;
unsigned long myTimeFinish;
bool StartTime = false;
void setup() {
  pinMode(pinHall, INPUT);
  Serial.begin(9600);
  
} 
void loop() {
  ReadHallSensor();
  
}



void ReadHallSensor()
  {
    //we measure 10 times adn make the mean
  long measure = 0;
  for(int i = 0; i < 10; i++){
      int value = 
      measure += analogRead(pinHall);
  }

  
  measure /= 10;  
  //voltage in mV
  float outputV = measure * 5000.0 / 1023;
  //flux density
  float magneticFlux =  outputV * 53.33 - 133.3;
  if(counter >3)
  {
    Serial.println("Takili kaldı");
  }
  else if (magneticFlux > -133.3) 
  {
    counter ++;
    Serial.println("Gecti");
    Serial.println(counter);
    counter2 = 0;
    if (!StartTime)
    {
      StartTime = true;
      myTimeStart = millis();
    }
    else
    {
        myTimeFinish = millis();
        Serial.print("HIZ : ");
        Serial.println(0.5/ ((myTimeFinish-myTimeStart)/1000));
        StartTime= false;
        
    }
  }
  if(counter2 >30)
  {
    Serial.println("Takili kaldı");
  }
  else if (magneticFlux <= -133.3)
  {
    Serial.println("Gecmedi");
    counter = 0;
    counter2 ++;
  }

    
  /*
  if(magneticFlux <= -133.3) {
    Serial.println("Gecmedi");
    Serial.println(counter);
    counter = 0;}  */
  
  delay(100);
    
    
   
   
   
  }
