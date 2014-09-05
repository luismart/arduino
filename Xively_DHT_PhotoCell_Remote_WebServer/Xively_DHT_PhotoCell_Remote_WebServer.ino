/*
##Xively WiFi Sensor Tutorial##
This sketch is designed to 
1. read data from a DHT and photocell sensors
2. send data to xively
3. act as a webserver
*/
#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>
#include <dht.h>
 
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
// The IP address will be dependent on your local network:
byte mac[] = {  
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
IPAddress ip(192,168,1,139);
// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

 
// Your Xively key to let you upload data
char xivelyKey[] = "";
//your xively feed ID
#define xivelyFeed 1110648409
//datastreams
char temperatureID[] = "temperature";
char humidityID[] = "humidity";
char lightID[] = "light";
 
// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
#define sensorPin A3
//led connected pin
//#define ledPin 9
#define dht_dpin A2 //no ; here. Set equal to channel sensor is on
dht DHT;
 
// Define the strings for our datastream IDs
XivelyDatastream datastreams[] = {
XivelyDatastream(temperatureID, strlen(temperatureID), DATASTREAM_FLOAT),
XivelyDatastream(humidityID, strlen(humidityID), DATASTREAM_FLOAT),
XivelyDatastream(lightID, strlen(lightID), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(xivelyFeed, datastreams, 3 /* number of datastreams */);
 
EthernetClient client;
XivelyClient xivelyclient(client);
 
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
// start the Ethernet connection and the server:
Ethernet.begin(mac, ip);
server.begin();
Serial.print("server is at ");
Serial.println(Ethernet.localIP());

//pin setup
pinMode(sensorPin, INPUT);
Serial.println("Starting single datastream upload to Xively...");
Serial.println();

while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }
 
}
 
void loop() {
   // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available ()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
	  client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");       
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
  //read sensor values
  int sensorValue = analogRead(sensorPin);
  datastreams[2].setFloat(sensorValue);
  //print the sensor valye
  Serial.print("Read sensor value ");
  Serial.println(datastreams[2].getFloat());
  
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
  delay(30000);
}
