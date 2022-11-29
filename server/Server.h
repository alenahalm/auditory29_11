#include <ESP8266WebServer.h>

#define echoPin 5
#define trigPin 4

ESP8266WebServer server(80);

void handle_root() {
  String form = "<form action=\"/LED\" method=\"POST\">";
  form = form + "<input type=\"submit\" value=\"Toggle LED\">";
  form = form + "</form>";
  server.send(200, "text/html", form);
}

void handleLED() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  Serial.println(duration);
  int distance = duration * 0.034 / 2;
  server.send(200, "text/html", String(distance));
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}

void server_init() {
  server.on("/", HTTP_GET, handle_root);
  server.on("/LED", HTTP_POST, handleLED);
  server.on("/SENSOR", HTTP_GET, handleSensor);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Server started at port 80");
}
