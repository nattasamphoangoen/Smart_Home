#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>
#include "LedControl.h"

#define WIFI_SSID       "ion00"
#define WIFI_PASSWORD   "ion12345"
#define FIREBASE_HOST "smart-e530a.firebaseio.com"
#define FIREBASE_AUTH "ChTDQzp5pF1xlwk8usuWm3nXww108yYQIaTqZP4g"
#define led2 D2
#define led1 D1
#define DHTPIN D4
#define DHTTYPE DHT11
#define LED0 D3
int c0, c1, c2, c3, u, u1, t3, t2, t1, t0;
String name;
DHT dht(DHTPIN, DHTTYPE);
// pin D5 is connected to the DataIn
// pin D7 is connected to CS
// pin D6 is connected to the CLK
LedControl lc = LedControl(D5, D6, D7, 1);
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
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("Home1/board1/led/led1", 1);
  Firebase.setInt("Home1/board1/led/LED2", 1);
  Firebase.setFloat("Home1/board1/Clock/segment", 00.00);
}

void loop() {
  float clk = Firebase.getFloat("Home1/board1/Clock/segment");
  Serial.print("Clock : ");
  Serial.println(clk);

  digitalWrite(led1, Firebase.getInt("Home1/board1/led/led1"));
  Serial.print("LEDTEST : ");
  Serial.println(Firebase.getInt("Home1/board1/led/led1"));

  digitalWrite(led2, Firebase.getInt("Home1/board1/led/LED2"));
  Serial.print("LEDTEST : ");
  Serial.println(Firebase.getInt("Home1/board1/led/LED2"));
  delay(200);

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
  Serial.print("tem = ");
  Serial.println(t);
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

  u = clk * 100;
  c3 = clk / 10;
  c2 = (int)clk % 10;
  c1 = u / 10 % 10;
  c0 = u % 10;

  u1 = t * 100;
  t3 = t / 10;
  t2 = (int)t % 10;
  t1 = u1 / 10 % 10;
  t0 = u1 % 10;
  
  lc.setDigit(0, 7, c3, false);
  lc.setDigit(0, 6, c2, true);
  lc.setDigit(0, 5, c1, false);
  lc.setDigit(0, 4, c0, false);

  lc.setDigit(0, 3, t3, false);
  lc.setDigit(0, 2, t2, true);
  lc.setDigit(0, 1, t1, false);
  lc.setRow(0, 0, B00001101);
}
