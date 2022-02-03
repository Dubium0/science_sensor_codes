#define PRE_PIN          8
#define VNOX_PIN         A0
#define VRED_PIN         A1

#define PRE_HEAT_SECONDS 10

int vnox_value = 0;
int vred_value = 0;

void setup() {
  
  // Setup preheater pin
  pinMode(PRE_PIN, OUTPUT);
  
  // Initialize serial port
  Serial.begin(9600);
  Serial.println("MiCS-4514 Test Read");
  Serial.print("Preheating...");

  // Wait for preheating

}
 void loop(){
   vred_value = analogRead(VRED_PIN);
  vnox_value = analogRead(VNOX_PIN); // take reading of ADC value from NOX-pin of NO2-sensor
   uint8_t Vin = int(vnox_value/15.5+0.5);
  float Vout = vnox_value/207.5; // convert ADC value to voltage (voltage divider on board: 5V->3.2V and 10bit ADC for Vref=3.3V -> 1023, hence 3.2V -> 992 and 992/198.4 = 5,
  //Serial.println("Vout: " + String(Vout)); // but because of resistor tolerance of 10% the value 207,5 is taken experimentally by measuring real output voltage on NOX-pin)
  float RlRs = Vout/(Vin/10-Vout); // find load resistance over sensor resistance proportion from Vout, using Vin as supply voltage
  float ppmNO2 = pow(10, 0.9682*log(RlRs)/log(10)-0.8108); // convert RsR0 to ppm concentration NO2 (refer to http://myscope.net/auswertung-der-airpi-gas-sensoren/)
 Serial.println("ppm NO2: " + String(ppmNO2));
  Serial.println(" REd pin " + vred_value );
 // Serial.print("mgNO2: " );
 // Serial.println(mgNO2);

  }
