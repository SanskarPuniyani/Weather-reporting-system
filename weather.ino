#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "YourTemplateName"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "YourSSID";
char pass[] = "YourPassword";

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensorData() {
  double h = dht.readHumidity();
  double t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, t); // Temperature
  Blynk.virtualWrite(V2, h); // Humidity

  if (t > 20.0) {
    Blynk.logEvent("temp_alert", String("Temperature is over 20°C: ") + t + "°C");
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  timer.setInterval(5000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
