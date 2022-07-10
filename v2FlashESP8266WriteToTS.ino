#include "secrets.h"
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

char networkname[] = SECRET_SSID;   // your network SSID (name) 
char passcode[] = SECRET_PASS;   // your network password
WiFiClient client;

unsigned long tsChannelID = SECRET_CH_ID;         // ThingSpeak Channel ID
const char *tsWriteAPIKey = SECRET_WRITE_APIKEY; // ThingSpeak Write API Key

// Initialize Values 
String airQuaility = "";
const int fieldOne = 1;

// Initialize our values
String field1 = "7134RVC AQ Placeholder";
String field2 = "AirQuality Placeholder";
String field3 = "Alert Status Placeholder";
String field4 = "Status Message Placeholder";

void setup()
{
    Serial.begin(115200);
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
            field1 = inChar;
            field2 = airQuaility;
        }
    }
    pushData();
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
    int getData = ThingSpeak.writeField(tsChannelID, field1, field2, field3, field4, tsWriteAPIKey);
    if (getData != 200)
    {
        delay(15000);
        pushData();
    }
    airQuaility = “”;
}