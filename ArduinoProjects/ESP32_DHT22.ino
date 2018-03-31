#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 19
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
char message[50];


// should be replaced by WiFi.gatewayIP().toString()
const char* mqtt_server = "192.168.2.1"; //MQTT broker ip
const char* ssid = "risquetos";
const char* password = "password";
const char* device_name = "esp32_1";
const int sleepTimeS = 40;

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(device_name)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void setup() {  
  // begin sensor  
  dht.begin();

  Serial.begin (115200);
  // connect to wifi
  Serial.print("Connecting to Wifi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wifi");
  
  // add certificates
  Serial.println("Adding certificates");

  Serial.println("Certificates added");


  client.setServer(mqtt_server, 1883);
  if (!client.connected()) {
    reconnect();
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  delay(400);
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    
    String data = "{\"temp\": ";
    data.concat(t);
    data.concat(", \"hum\": ");
    data.concat(h);
    data.concat("}");
    /* publish the message */
    
    data.toCharArray(message, 50); 
    Serial.print("Publishing ");
    Serial.println(message);
    client.publish("sensors/esp32_1", message);
  }
  
  delay(250);
  Serial.println("Sleeping...Zzzzzz");
  ESP.deepSleep(sleepTimeS * 1000000);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}
