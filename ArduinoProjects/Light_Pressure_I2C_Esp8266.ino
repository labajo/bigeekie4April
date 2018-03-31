#include <ESP8266WiFi.h>
const char* ssid = "risquetos";
const char* password = "password";

#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter(0x23);
#include <SFE_BMP180.h>
SFE_BMP180 pressure;
#define ALTITUDE 730.0

#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);
const char* mqtt_server = "192.168.2.1";
char message[90];
const int sleepTimeS = 70;

String getPressure()
{
  char status;
  double T,P,p0;
  String result = "";
  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      result.concat(",\"temp\": ");
      result.concat(T);
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          result.concat(", \"aPressure\": ");
          result.concat(P);
          p0 = pressure.sealevel(P,ALTITUDE);
          result.concat(", \"rPressure\": ");
          result.concat(p0);
        }
      }
    }
  }
  return result;
}

void setup() {
  //dht.begin();
  Serial.begin(115200);
  pressure.begin();
  lightMeter.begin(BH1750_CONTINUOUS_HIGH_RES_MODE);
  Serial.println("Starting ESP8266");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  //Serial.print(getPressure());
  String data = "{\"lum\": ";
  data.concat(lux);
  data.concat(getPressure());
  data.concat("}");
  /* publish the message */
  data.toCharArray(message, 90);
  client.setServer(mqtt_server, 1883);
  if (!client.connected()) {
    reconnect();
  }
  
  Serial.print("Publishing ");
  Serial.println(data);
  client.publish("sensors/esp8266_1", message);
  delay(250);
  Serial.println("Sleeping...Zzzzzz");
  ESP.deepSleep(sleepTimeS * 1000000);

}



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("esp8266_1")) {
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

void loop() 
{

}
