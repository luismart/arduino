/*
##Xively WiFi Sensor Tutorial##
This sketch is designed to take sensors (from photocell) and upload the values to Xively
at consistant intervals. At the same time it gets a setable value from Xively to adjust the brigthness
of an LED. This sketch is reusable and can be adapted for use with many different sensors.
Derived from Xively Ardino Sensor Client by Sam Mulube.
By Calum Barnes 3-4-2013
BSD 3-Clause License - [http://opensource.org/licenses/BSD-3-Clause]
Copyright (c) 2013 Calum Barnes
*/
#include <SPI.h>
//#include <WiFi.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>
#include <dht.h>
 
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
 
// Your Xively key to let you upload data
char xivelyKey[] = "";
//your xively feed ID
#define xivelyFeed 1110648409
//datastreams
char temperatureID[] = "temperature";
char humidityID[] = "humidity";
 
// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
//#define sensorPin A2
//led connected pin
//#define ledPin 9
#define dht_dpin A2 //no ; here. Set equal to channel sensor is on
dht DHT;

 
// Define the strings for our datastream IDs
XivelyDatastream datastreams[] = {
XivelyDatastream(temperatureID, strlen(temperatureID), DATASTREAM_FLOAT),
XivelyDatastream(humidityID, strlen(humidityID), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(xivelyFeed, datastreams, 2 /* number of datastreams */);
 
EthernetClient client;
XivelyClient xivelyclient(client);
 
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
//pin setup
//pinMode(dht_dpin, INPUT);
Serial.println("Starting single datastream upload to Xively...");
Serial.println();

while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }
 
}
 
void loop() {
//read sensor values
//int sensorValue = analogRead(sensorPin);
//datastreams[0].setFloat(sensorValue);

DHT.read11(dht_dpin);
Serial.print("Current humidity = ");
Serial.print(DHT.humidity);
Serial.print("% ");
datastreams[1].setFloat(DHT.humidity);
Serial.print("temperature = ");
Serial.println(DHT.temperature);
datastreams[0].setFloat(DHT.temperature);

 
//send value to xively
Serial.println("Uploading it to Xively");
int ret = xivelyclient.put(feed, xivelyKey);
//return message
Serial.print("xivelyclient.put returned ");
Serial.println(ret);
Serial.println("");
//delay between calls
delay(15000);
}
