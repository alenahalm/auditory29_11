#include "wifi.h"
#include "Server.h"

#define echoPin 5
#define trigPin 4

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  WiFi_init(true);
  server_init();
}

void loop() {
  server.handleClient();
  
}
