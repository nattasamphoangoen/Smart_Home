#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

#define LED_PIN D1

// Config Firebase
#define FIREBASE_HOST "smart-e530a.firebaseio.com"
#define FIREBASE_AUTH "ChTDQzp5pF1xlwk8usuWm3nXww108yYQIaTqZP4g"

// Config connect WiFi
#define WIFI_SSID "ion00"
#define WIFI_PASSWORD "ion12345"

#define DHTPIN D4
#define DHTTYPE DHT11
#define LED0 D6
String name;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED0, OUTPUT);
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Serial.print("connected: ");
  Serial.println(WiFi.SSID());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/Home1/board1/led/led1");
  dht.begin();
}

void loop() {

  //==============================================================================
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }

  if (Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    eventType.toLowerCase();

    if (eventType == "") return ;
    Serial.print("event: ");
    Serial.println(eventType);
    if (eventType == "put") {
      String path = event.getString("path");
      int data = event.getInt("data");
      Serial.println("[" + path + "] " + String(data));
      if (path == "/") {
        if (data == 1) {
          digitalWrite(LED_PIN,  HIGH);
        } else {
          digitalWrite(LED_PIN,  LOW);
        }
      }
    }
  }
  delay(10);

}
