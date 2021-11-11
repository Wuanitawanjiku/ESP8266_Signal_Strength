#include "ThingSpeak.h"
//#include "secrets.h"

unsigned long myChannelNumber = 1518556;
const char * myWriteAPIKey = "J39LACWL3HSU2CPZ";

#include <ESP8266WiFi.h>

char ssid[] = "codehive";   
char pass[] = "codehive!";   
//int keyIndex = 0;            // your network key index number (needed only for WEP)
WiFiClient  client;

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
}

void loop() {

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); 
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  // Measure Signal Strength (RSSI) of Wi-Fi connection
  long rssi = WiFi.RSSI();

  // Write value to Field 1 of a ThingSpeak Channel
  int httpCode = ThingSpeak.writeField(myChannelNumber, 1, rssi, myWriteAPIKey);

  if (httpCode == 200) {
    Serial.println("Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  }

  // Wait 20 seconds to update the channel again
  delay(20000);
}
