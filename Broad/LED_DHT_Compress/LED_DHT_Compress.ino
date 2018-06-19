#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

#define WIFI_SSID       "ion00"
#define WIFI_PASSWORD   "ion12345"
#define FIREBASE_HOST "smart-e530a.firebaseio.com"
#define FIREBASE_AUTH "ChTDQzp5pF1xlwk8usuWm3nXww108yYQIaTqZP4g"
#define led2 D2
#define led1 D1
#define DHTPIN D4
#define DHTTYPE DHT11
#define LED0 D3

String name;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(LED0, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(WiFi.localIP());
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
  Firebase.setInt("Home1/board1/led/led1", 1);
  Firebase.setInt("Home1/board1/led/LED2", 1);
}


void loop() {
  digitalWrite(led1, Firebase.getInt("Home1/board1/led/led1"));
  Serial.print("LEDTEST : ");
  Serial.println(Firebase.getInt("Home1/board1/led/led1"));
  
  digitalWrite(led2, Firebase.getInt("Home1/board1/led/LED2"));
  Serial.print("LEDTEST : ");
  Serial.println(Firebase.getInt("Home1/board1/led/LED2"));
  

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(500);
    return;
  }
  name = Firebase.pushFloat("Home1/board1/temperature", t);
  if (Firebase.failed()) {
    Serial.print("pushing /temperature failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("pushed: /temperature/");
  Serial.println(name);
  delay(5000);
  if (t >= 34) {
    digitalWrite(LED0, HIGH);
  } else {
    for (int i = 1 ; i < 10; i++) {
      digitalWrite(LED0, HIGH);
      delay(100);
      digitalWrite(LED0, LOW);
      delay(100);
    }
  }
}

