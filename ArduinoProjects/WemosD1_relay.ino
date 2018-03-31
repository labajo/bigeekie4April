#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid = "risquetos";
const char* password = "password";
const char* mqtt_server = "192.168.2.1";

const int relayPin = D1;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int currentStatus = 0;
bool cliConnected = false;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    currentStatus = HIGH;
    digitalWrite(relayPin, HIGH);
    Serial.println("ON");
    client.publish("sensors/wemos_2_out", "1");
  } else {
    currentStatus = LOW;
    digitalWrite(relayPin, LOW);
    Serial.println("OFF");
    client.publish("sensors/wemos_2_out", "0");
  }

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("wemos_2")) {
      if (!cliConnected) {
        client.publish("sensors/wemos_2_out", "0");
      }
      Serial.println("connected");
      client.subscribe("sensors/wemos_2_in");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
