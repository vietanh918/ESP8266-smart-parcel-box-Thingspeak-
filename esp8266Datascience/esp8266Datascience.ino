#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <Servo.h>

/*-------------------------BEGIN WIFI---------------------*/
const char* ssid = "";
const char* password = "";
WiFiClient client;
/*--------------------------END WIFI----------------------*/

/*--------------------------BEGIN THINGSPEAK----------------------*/
unsigned long myChannelNumber = ; //channel nummer
const char * myWriteAPIKey = ""; // API Key
/*---------------------------END THINGSPEAK-----------------------*/

Servo servo;
Servo servoLatchLock;
int angle = 0;
int angleSLL = 0;
const int pinSwitch = 4; //Pin reed switch
int switchState = 0;

void setup()
{
  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
  servo.attach(5);
  servoLatchLock.attach(16);
  servo.write(0); // open after initialization
  servoLatchLock.write(180); //close after initialization
  pinMode(pinSwitch, INPUT);
}

void loop()
{
  switchState = digitalRead(pinSwitch);
  Serial.println(switchState);
  ThingSpeak.writeField(myChannelNumber, 1, switchState, myWriteAPIKey);

  //  if (full then keep closed and send message full (led which shows its full) {
  //    servo.write(0);
  //  }

  //  else if(){ //If something stuck then keep locks closed
  //    servo.write(0);
  //  }

  if (switchState == 1 /*&& (gewicht > 0)*/) //If door is closed and weight > 0 then drop parcel
  {
    servo.write(180);
    delay(500); //Change to millis later
    servoLatchLock.write(0);

  }
//  else if (switchState == 0 /* && (gewicht == 0)*/) { //If door is open and weight == 0 then auto close door or give message
//    //Close the door!! OR close it automatic with another stepper motor
//    return;
//  }

  else
  {
    servoLatchLock.write(180);
    delay(500);
    servo.write(0);
  }

}
