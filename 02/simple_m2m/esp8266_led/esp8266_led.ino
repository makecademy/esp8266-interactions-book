// Import required libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>

// Clients
WiFiClient espClient;
PubSubClient client(espClient);

// Create aREST instance
aREST rest = aREST(client);

// Unique ID to identify the device for cloud.arest.io
char* device_id = "01e47f";

// WiFi parameters
const char* ssid = "wifi-name";
const char* password = "wifi-pass";

// LED state
bool ledState;

// Functions
void callback(char* topic, byte* payload, unsigned int length);
int toggle(String command);

void setup(void)
{
  
  // Start Serial
  Serial.begin(115200);

  // Set callback
  client.setCallback(callback);

  // Give name and ID to device
  rest.set_id(device_id);
  rest.set_name("led");

  // Function
  rest.function("toggle", toggle);

  // LED state
  ledState = false;

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Pin 5 as output
  pinMode(5, OUTPUT);
  
}

void loop() {

  // Connect to the cloud
  rest.handle(client);

}

// Handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {

  // Handle
  rest.handle_callback(client, topic, payload, length);

}

// Toggle LED
int toggle(String command) {

  ledState = !ledState;
  digitalWrite(5, ledState);
  return 1;
}
