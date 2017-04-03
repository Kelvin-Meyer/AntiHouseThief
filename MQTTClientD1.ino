#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DHTTYPE DHT11
#define DHTPIN  2
#define SLEEP_DELAY_IN_SECONDS  30

unsigned long previousMillis = 0; 
const long interval = 2000; 
//const char* ssid = "Syntaxis";
//const char* password = "syntaxiswifi!";
const char* ssid = "iPhone van Casper";
const char* password = "sterkwachtwoord1";
//const char* ssid = "pudding";
//const char* password = "lekkerpuddingeten";
const char* mqtt_server = "172.20.10.4";
const char* mqtt_username = "testje";
const char* mqtt_password = "testje";
const char* mqtt_topic = "nieuws";

int tiltSensorPin = D1;
int periodLength = 1000; // Milliseconds per period

WiFiClient espClient;
PubSubClient client(espClient);

String dataString;
char charBuf[100];

void setup() {
  Serial.begin(115200);

  // setup WiFi
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void setup_wifi() {
  delay(10);
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
}

void reconnect() {
  //WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    setup_wifi();
  }
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("test con", mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("MQTT connection failed, retry count: ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void loop() {
  if (measureMovement() > 0) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    dataString = String("Er is beweging gedecteerd");
    dataString.toCharArray(charBuf, 150);
    Serial.println(charBuf);
    client.publish(mqtt_topic, charBuf );
    Serial.println( "Closing MQTT connection...");
    client.disconnect();
    Serial.println( "Closing WiFi connection...");
    WiFi.disconnect();
    Serial.println( "Sleeping for a minute");
    delay(3000); 
  }
}

/**
 * Measures the amount of movement within one period
 * @return the amount of times the tilt sensor switched state within one period
 */
int measureMovement() {
  int oldTiltState = digitalRead(tiltSensorPin);
  int newTiltState = digitalRead(tiltSensorPin);
  int timesTriggered = 0;
  unsigned long startTime = millis();
  unsigned long currentTime;

  // for periodLength milliseconds:
  do {
    oldTiltState = digitalRead(tiltSensorPin);
    if (newTiltState != oldTiltState) {
      timesTriggered++;
      newTiltState = oldTiltState;
    }
    currentTime = millis();
  } while ((currentTime - startTime) < periodLength);

  return timesTriggered; // return the results
  
}
