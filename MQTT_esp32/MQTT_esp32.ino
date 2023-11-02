#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// Wifi informations
const char* ssid = "SSID"; // update this
const char* password = "WIFI_PASSWORD"; // update this

// MQTT Broker informations
#define MQTT_SERVER "BROKER_ADRESS" // update this
#define MQTT_PORT 1883 
#define MQTT_USERNAME "USERNAME" // update this
#define MQTT_PASSWORD "PASSWORD" // update this

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD);

// Define MQTT client and topics
Adafruit_MQTT_Subscribe statusSub = Adafruit_MQTT_Subscribe(&mqtt, "office1/call"); // update this

const int redLedPin = 12;   // red LED pin
const int greenLedPin = 13; // green LED pin

void setup() {
  Serial.begin(115200);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connection to Wifi...");
  }
  Serial.println("Connected to Wifi");

  mqtt.subscribe(&statusSub);
}

void loop() {
  Adafruit_MQTT_Subscribe* subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &statusSub) {
      char message[subscription->datalen];
      memcpy(message, (char*)subscription->lastread, subscription->datalen);
      message[subscription->datalen] = '\0';

      Serial.print("Received message on topic [");
      Serial.print(statusSub.topic);
      Serial.print("] : ");
      Serial.println(message);

      String messageString(message);

      if (messageString == "1") {
        digitalWrite(greenLedPin, LOW);
        digitalWrite(redLedPin, HIGH);
      } else if (messageString == "0") {
        digitalWrite(redLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
      }
    }
  }

  if (!mqtt.ping()) {
    mqtt.disconnect();
  }

  if (!mqtt.connected()) {
    connectToMQTT();
  }
}

void connectToMQTT() {
  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Trying to connect to MQTT...");
    delay(5000);  // wait 5s before retry
  }
  Serial.println("Connected to MQTT broker");