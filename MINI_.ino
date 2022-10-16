#define BLYNK_TEMPLATE_ID "TMPLpw2t93Tj"
#define BLYNK_DEVICE_NAME "Smart Farm"
//#define BLYNK_AUTH_TOKEN "NmlBlVFbopXj67dQPP30KTltEcM-1T9Z"
#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2
#define waterPump D3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
char auth[] ="NmlBlVFbopXj67dQPP30KTltEcM-1T9Z";
char ssid[] = "Rgukt";
char pass[] = "rguktece";
//code written by Md iqbal
//website:-techiqbal.com
//Youtube:-Techiqbal
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
bool Relay = 0;
SimpleTimer timer;

void sendSensor()
{
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

Blynk.virtualWrite(V5, h); //V5 is for Humidity
Blynk.virtualWrite(V6, t); //V6 is for Temperature
}
void setup()
{
Serial.begin(9600);
dht.begin();
Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);
  //lcd.init();
  //lcd.backlight();

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  

/*BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
    //lcd.setCursor(0, 1);
    //lcd.print("Motor is ON ");
  } else {
    digitalWrite(waterPump, HIGH);
    //lcd.setCursor(0, 1);
    //lcd.print("Motor is OFF");
  }}*/
timer.setInterval(1000L, sendSensor);
Blynk.begin(auth, ssid, pass);
sensors.begin();
}
BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
    //lcd.setCursor(0, 1);
    //lcd.print("Motor is ON ");
  } else {
    digitalWrite(waterPump, HIGH);
    //lcd.setCursor(0, 1);
    //lcd.print("Motor is OFF");
  }}
int sensor=0;
int output=0;
void sendTemps()
{
sensor=analogRead(A0);
output=(145-map(sensor,0,1023,0,100)); //in place 145 there is 100(it change with the change in sensor)
delay(1000);
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0);
Serial.println(temp);
Serial.print("moisture = ");
Serial.print(output);
Serial.println("%");
Blynk.virtualWrite(V1, temp);
Blynk.virtualWrite(V2,output);
delay(1000);}



void loop()
{
Blynk.run();
timer.run();
sendTemps();
}
