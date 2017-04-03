#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DHTTYPE DHT11
#define DHTPIN  2
#define SLEEP_DELAY_IN_SECONDS  30

unsigned long previousMillis = 0; 
const long interval = 2000; 

const char* ssid = "Your SSID";
const char* password = "Your SSID password";
const char* mqtt_server = "Your MQTT Server name";
const char* mqtt_username = "Your MQTT username";
const char* mqtt_password = "Your MQTT password";
const char* mqtt_topic = "Your publish topic";
const int* mqtt_port = 1883; // Standard port for MQTT
const char* client_id = "Your client id";

String dataString = String("Your message");
char charBuf[100];

int tiltSensorPin = D1;
int periodLength = 1000; // Milliseconds per period

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Baudrate
  Serial.begin(115200);

  // setup WiFi
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

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
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    setup_wifi();
  }
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("MQTT connection failed, retry count: ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

/*
 * If measureMovement() returns more than zero. 
 * Connect to the Wi-Fi network, connect to MQTT Server and send a message.
 * After doing this it will sleep for 3 seconds.
 */
void loop() {
  if (measureMovement() > 0) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    dataString.toCharArray(charBuf, 150);
    Serial.println(charBuf);
    client.publish(mqtt_topic, charBuf );
    Serial.println( "Closing MQTT connection...");
    client.disconnect();
    Serial.println( "Closing WiFi connection...");
    WiFi.disconnect();
    Serial.println( "Sleeping for three seconds");
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
