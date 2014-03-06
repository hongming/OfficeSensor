//Sharp Dust Sensor and Arduino by Pdeng@sensorapp.net http://sensorapp.net/?p=479
//DHT Library by Robtillaart http://playground.arduino.cc/Main/DHT11Lib
//Air Quality Sensor Setup by Stace@cmu.edu  http://www.staceyk.org/airSensors/sensorsetup.php
//Dust denisty caculation by Chris Nafis http://www.howmuchsnow.com/arduino/airquality/

#include <dht11.h>
dht11 DHT;
//int dhtPin=1;
#define dhtPin A1
int dustPin=0;
//analog pin connect to pin 5 on dust sensor
int dustledPin=5;
//connect to pin 3 on dust sensor
int dustVal=0;
int dustdelay1=280;
int dustdelay2=40;
int offTime=9680;
//delay time for dust sensor
void setup(){
  Serial.begin(9600);
  pinMode(dustledPin,OUTPUT);
  pinMode(dustPin,INPUT);
  Serial.println("Office Temperature and Humidity");
    Serial.print("DHT LIBRARY VERSION");
  Serial.println(DHT11LIB_VERSION);
    int dhtinfo = DHT.read(dhtPin);
//  Serial.print("Read dht sensor");
  switch(dhtinfo){
  case DHTLIB_OK:
    Serial.println("OK");
    break;
  case DHTLIB_ERROR_CHECKSUM:
    Serial.println("DHT Checksum Error");
    break;
  case DHTLIB_ERROR_TIMEOUT:
    Serial.println("DHT Time Out Error");
    break;
  default:
    Serial.println("Unkonwn Error");
    break;
  }
    Serial.print("Temperature(C)\t");
    Serial.print("Humidity(%)\t");
    Serial.println("Dust\t");
}

void loop(){
  officetemperatureandhumidity();
  officedustsensor();
}

void officetemperatureandhumidity(){
  Serial.print((float)DHT.temperature,2);
  Serial.print("\t");
  Serial.print((float)DHT.humidity,2);
    Serial.print("\t");
  delay(2000);
}

void officedustsensor(){
  digitalWrite(dustledPin,LOW); 
  //dustledPin on arduino must be connected to pin 3 on the dust sensor GP2Y 1010AU0F
  delayMicroseconds(dustdelay1);
  dustVal = analogRead(dustPin);
//Read sensor value on pin 5
  float dustdensity=dustVal*5*0.172/1024-0.0999;
  delayMicroseconds(dustdelay2);
  digitalWrite(dustledPin,HIGH);
  Serial.print(dustVal);
  Serial.print("\t");
  Serial.print(dustdensity);
  Serial.println("mg/(m^3)");
  delayMicroseconds(offTime);
  delay(2000);
}

