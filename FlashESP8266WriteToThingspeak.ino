#include <ESP8266WiFi.h>
#include "secretsp.h"
#include <string>
#include <iostream>
#include "ThingSpeak.h"

char networkname[] = SECRET_SSID;   // your network SSID (name) 
char passcode[] = SECRET_PASS;   // your network password

WiFiClient client;

unsigned long tsChannelID = SECRET_CH_ID;         // ThingSpeak Channel ID
const char *tsWriteAPIKey = SECRET_WRITE_APIKEY; // ThingSpeak Write API Key

String airQuaility = "";
//int alarmValue = random(0,10);
const int fieldOne = 1;
const int fieldTwo = 2;

void setup()
{
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    ThingSpeak.begin(client);
    thingSpeak();
}

void loop()
{
    thingSpeak();
    if (Serial.available() > 0)
    {
        while (Serial.available() > 0)
        {
            int inChar = Serial.read();
            airQuaility += (char)inChar;
            //alarmValue = alarmValue;            
            //ThingSpeak.setField(fieldOne, airQuaility);
            //ThingSpeak.setField(fieldTwo, AlarmValue;
            //ThingSpeak.setStatus("Sensor Value is: " + String(airQuaility));
        }
    }
    pushData();
    //pushDataTwo();
}

void thingSpeak()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            WiFi.begin(networkname, passcode);
            delay(5000);
        }
    }
}

void pushData()
{  
    int getData = ThingSpeak.writeField(tsChannelID, fieldOne, airQuaility, tsWriteAPIKey);
    //ThingSpeak.writeFields(tsChannelID, tsWriteAPIKey);
    if (getData != 200)
    {
        delay(15000);
        pushData();
    }
    airQuaility = "";
}

void pushDataTwo()
{
    int alarmValue = random(0,10);
    int getData2 = ThingSpeak.writeField(tsChannelID, fieldTwo, alarmValue, tsWriteAPIKey);
    //ThingSpeak.writeFields(tsChannelID, tsWriteAPIKey);
    if (getData2 != 200)
    {
        delay(15000);
        pushDataTwo();
    }
}