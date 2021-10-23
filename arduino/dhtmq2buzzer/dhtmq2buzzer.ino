#include "DHT.h"
#define         MQ_PIN                       (A0)     
#define         RL_VALUE                     (5)     
#define         RO_CLEAN_AIR_FACTOR          (9.83)  
                                                     

/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    
#define         CALIBRATION_SAMPLE_INTERVAL  (500)  
                                                    
#define         READ_SAMPLE_INTERVAL         (50)   
#define         READ_SAMPLE_TIMES            (5)     


#define DHTPIN D2     // what pin we're connected to
#define MQ2 A0     // what pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT12   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
const int buzzer = 13;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
    pinMode(MQ2, INPUT);
    Serial.print("Calibrating...\n");                
  Ro = MQCalibration(MQ_PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
  Serial.print("\n");

  dht.begin();
}
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}
float MQCalibration(int mq_pin)
{
  int i;
  float val=0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value

  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 

  return val; 
}

int MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == 0 ) {
     return pow(10, ((log(rs_ro_ratio)-LPGCurve[1])/ LPGCurve[2]) + LPGCurve[0]);

  } else if ( gas_id == 1 ) {
     return rs_ro_ratio;
  } else if ( gas_id == 2 ) {
     return rs_ro_ratio;
  }    

  return 0;
}


void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Impossible de lire la sonde DHT!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  float mq2_read = analogRead(A0)/Ro;
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  Serial.print("Gas: "); 
  Serial.print(mq2_read);
   Serial.print(" ppm");
   Serial.print("\n");
   if(mq2_read > float(320) && t > float(32)){
     tone(buzzer, 1000); // Send 1KHz sound signal...
     
     delay(500);        // ...for 1 sec
     noTone(buzzer);     // Stop sound...
   }

}
