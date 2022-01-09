#include "dht11.h"
DHT11 dht(4);
uint16_t temp=0;
uint16_t humd=0;

void setup() {
  Serial.begin(115200);

}

void loop() {
  Serial.println("Debug");
  bool citit = dht.read(temp,humd);
  citit=true;
    if(citit){
    Serial.println(temp);
    Serial.println(humd);
  }
  else{
    Serial.println("nu s-a putut citii");
  }


}
