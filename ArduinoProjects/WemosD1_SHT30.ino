#include <WEMOS_SHT3X.h>
SHT3X sht30(0x45);

char message[80];

#include <ESP8266WiFi.h>
const char* ssid = "risquetos";
const char* password = "password";

#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);
const char* mqtt_server = "192.168.2.1";

const int sleepTimeS = 50;

unsigned int raw=0;
float volt=0.0;


void setup() {
  pinMode(A0, INPUT);
  int i = 0;
  Serial.begin(115200);
  Serial.println("Starting ESP8266");
  raw = analogRead(A0);
  volt = raw/1023.0;
  volt = volt*4.3981;
  Serial.print("Battery Voltage: ");
  Serial.println(volt);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
  
  while((sht30.get()==0) && i < 3) {
    delay(500);
    Serial.print("Connecting to SHT30... Try ");
    Serial.println(i);
    i++;
  }
  if(sht30.get()==0){
    float t = sht30.cTemp;
    float h = sht30.humidity;
    String data = "{\"temp\": ";
    data.concat(t);
    data.concat(", \"hum\": ");
    data.concat(h);
    data.concat(", \"volt\": ");
    data.concat(volt);
    data.concat("}");
    /* publish the message */
    data.toCharArray(message, 80);
    client.setServer(mqtt_server, 1883);
    if (!client.connected()) {
      reconnect();
    }
    delay(50);
    Serial.print("Publishing ");
    Serial.println(data);
    client.publish("sensors/wemos_1", message);
  } else {
    Serial.println("Cannot connect to device...");
  }
  
  
  delay(350);
  Serial.println("Sleeping...Zzzzzz");
  ESP.deepSleep(sleepTimeS * 1000000);
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
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
