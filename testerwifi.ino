
#include <ESP8266WiFi.h>
#include "secrets2.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int number1 = 0;
int number2 = random(0,100);
String myStatus = "";

void setup() {
  Serial.begin(115200);  // Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
    number1 = Serial.read();

  if (number1 <= 0)
    {
      ThingSpeak.setField(1, number1);
      ThingSpeak.setField(2, number2);
      myStatus = String(number1);
      ThingSpeak.setStatus(myStatus);
      // write to the ThingSpeak channel
      int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      ThingSpeak.setStatus("Wrote to Channel Call Just Happened");
      if(x == 200){
        Serial.println("Channel update successful.");
        ThingSpeak.setStatus("Channel update successful.");
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(x));
        ThingSpeak.setStatus("Problem updating channel. HTTP error code " + String(x));
      }  
      }
  else
    {
      //No Serial Bus Reading Nothing to Write
      ThingSpeak.setStatus("Nothing read from Serial Port");
    }
  }
  delay(60000); // Wait 60 seconds to update the channel again
}