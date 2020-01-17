#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <Servo.h>

/*-------------------------BEGIN WIFI---------------------*/
//const char* ssid = "Tesla IoT";
//const char* password = "";
const char* ssid = "";
const char* password = "";
WiFiClient client;
/*--------------------------END WIFI----------------------*/

/*--------------------------BEGIN THINGSPEAK----------------------*/
unsigned long myChannelNumber = ; //channel nummer
const char * myWriteAPIKey = ""; // API Key
/*---------------------------END THINGSPEAK-----------------------*/

Servo servo;
int angle = 0;
int val;
const int pinSwitch = 12; //Pin reed switch
int switchState = 0;

void setup()
{
  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
  servo.attach(5);
  servo.write(0);
  pinMode(pinSwitch, INPUT);
}

void loop()
{
  StatoSwitch = digitalRead(pinSwitch);
  Serial.println(switchState);
  ThingSpeak.writeField(myChannelNumber, 1, switchState, myWriteAPIKey);
  if (switchState == HIGH /*&& (gewicht > 0)*/)
  {
    servo.write(180);
  }
  else 
  {
        servo.write(0);
  }

}
