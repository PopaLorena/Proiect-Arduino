#include <DHT.h>
// #include "dht11.h"
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
// InfluxDB v2 server or cloud API token (Use: InfluxDB UI -> Data -> API Tokens -> <select token>)
#define INFLUXDB_TOKEN "55trP1i-mBCyoUNGlbLwiRuz-dZ4HTB368xsU_j-JoxKEbxSTxhUhcATze2TResaeP1dCiSegd3yH1QgVgdYCw=="
// InfluxDB v2 organization id (Use: InfluxDB UI -> User -> About -> Common Ids )
#define INFLUXDB_ORG "arduinosio2021@gmail.com"
// InfluxDB v2 bucket name (Use: InfluxDB UI ->  Data -> Buckets)
#define INFLUXDB_BUCKET "ArduinoESP"

#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"
#define DEVICE "ESP8266"
// Replace with your network credentials
const char* ssid = "Kid";
const char* password = "aaaabbbb";
// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Data point
Point sensor("esp8266s");

#define         MQ_PIN                       (A0)     
#define         RL_VALUE                     (5)     
#define         RO_CLEAN_AIR_FACTOR          (9.83)  
                                                     

/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    
#define         CALIBRATION_SAMPLE_INTERVAL  (500)  
                                                    
#define         READ_SAMPLE_INTERVAL         (50)   
#define         READ_SAMPLE_TIMES            (5)     

#define PIR D1
#define DHTPIN D2     // what pin we're connected to
#define MQ2 A0     // what pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT12   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

const int buzzer = 13;
int Ro = 10;
DHT dht(DHTPIN, DHTTYPE);
//DHT_Module dht2(DHTPIN);           
void setup() {
  
  Serial.begin(115200);

   WiFi.mode(WIFI_STA);
  wifiMulti.addAP(ssid, password);
 
  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  
  pinMode(PIR,INPUT);
  Serial.print("PIR Installed\n");
  Serial.println("DHTxx test!");
    pinMode(MQ2, INPUT);
    Serial.print("Calibrating...\n");                
                     //Calibrating the sensor. Please make sure the sensor is in clean air 
             
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
  Serial.print("\n");
  dht.begin();
    if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
     sensor.addTag("device", DEVICE);
}
void loop() {
// Wait a few secondsbetween measurements.
  delay(1500);
  
  sensor.clearFields();
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)


 int val = digitalRead(PIR);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    Serial.println("presence detected");   // turn LED ON  
    sensor.addField("PIR", 1);
  }
  else {
    Serial.println("Nothing to show");
    sensor.addField("PIR", 0);
    }
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Nu se poate citi de la DHT!");

  }
  //uint16_t h2, t2;
  //if(dht2.read(t2,h2)){
  //  Serial.println();
  //  Serial.print(t2);
  //  Serial.print("   ");
  //  Serial.print(h2);
  //  Serial.println();
 // }
 // else{
 //   Serial.println("Modulul nu functioneste pupjos");
 // }
  // Compute heat index in Fahrenheit (the default)
  //float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);
  float mq2_read = analogRead(MQ2);
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  Serial.print("Gas: "); 
  Serial.print(mq2_read);
   Serial.print(" ppm");
   Serial.print("\n");
   if(mq2_read > float(1000) || t > float(50)){
     tone(buzzer, 1000); // Send 1KHz sound signal...
     
     delay(500);        // ...for 1 sec
     noTone(buzzer);     // Stop sound...

     sensor.addField("Buzzer", 1);
   }

   else{
     sensor.addField("Buzzer", 0);
   }

  sensor.addField("Temp", t);
  sensor.addField("Humidity", h);
  sensor.addField("GAZ", mq2_read);
  // Accurate time is necessary for certificate validation and writing in batches
  // For the fastest time sync find NTP servers in your area: https://www.pool.ntp.org/zone/
  // Syncing progress and the time will be printed to Serial.
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
 
  // Print what are we exactly writing
  Serial.print("Writing: ");
  Serial.println(sensor.toLineProtocol());

  // Check server connection

    if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}
