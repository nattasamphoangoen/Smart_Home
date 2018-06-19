#include <ESP8266WiFi.h>
#include <time.h>
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
DHT dht(DHTPIN, DHTTYPE);
int timezone = 7 * 3600;
int dst = 0;
// pin D5 is connected to the DataIn
// pin D7 is connected to CS
// pin D6 is connected to the CLK
LedControl lc = LedControl(D5, D6, D7, 1);
int a3, a2, a1, a0;
void setup()
{

  Serial.setDebugOutput(true);

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
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nLoading time");
  while (!time(nullptr)) {
    Serial.print("*");
    delay(100);
  }
  Serial.println("");

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  String clk1 = Firebase.getString("Home1/board1/Clock/segment");
  float clk = clk1.toFloat();
  bool k = Firebase.getBool("Home1/board1/Clock/M");
  Serial.print("Clock : ");
  Serial.println(clk1);
  Serial.println(clk);

  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.print(p_tm->tm_sec);
  Serial.println("");
  if (Firebase.getBool("Home1/board1/led/led1") == true) {
    digitalWrite(led1, HIGH);
    Serial.print("LEDTEST : ");
    Serial.println(Firebase.getBool("Home1/board1/led/led1"));
  }else{
    digitalWrite(led1, LOW);
  }
  if (Firebase.getBool("Home1/board1/led/LED2") == true) {
    digitalWrite(led2, HIGH);
    Serial.print("LEDTEST : ");
    Serial.println(Firebase.getBool("Home1/board1/led/LED2"));
  }else{
    digitalWrite(led2, LOW);
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

  a3 = p_tm->tm_hour / 10;
  a2 = p_tm->tm_hour % 10;
  a1 = p_tm->tm_min / 10;
  a0 = p_tm->tm_min % 10;
  String clock = (String)a3 + (String)a2 + (String)a1 + (String)a0;
  float ccc = clock.toFloat() / 100.0;
  Serial.println("");
  Serial.println(ccc);
  Serial.println("");

  //  if (isnan(h) || isnan(t)) {
  //    Serial.println(t);
  //    delay(100);
  //    return;
  //  }
  Firebase.setFloat("Home1/board1/temperature", t);
  Serial.print("tem = ");
  Serial.println(t);
  delay(200);
  if (t >= 26) {
    digitalWrite(LED0, HIGH);
  }

  if (k == true) {
    lc.setDigit(0, 7, c3, false);
    lc.setDigit(0, 6, c2, true);
    lc.setDigit(0, 5, c1, false);
    lc.setDigit(0, 4, c0, false);

    lc.setDigit(0, 3, t3, false);
    lc.setDigit(0, 2, t2, true);
    lc.setDigit(0, 1, t1, false);
    lc.setRow(0, 0, B00001101);
  } else {
    lc.setDigit(0, 7, a3, false);
    lc.setDigit(0, 6, a2, true);
    lc.setDigit(0, 5, a1, false);
    lc.setDigit(0, 4, a0, false);

    lc.setDigit(0, 3, t3, false);
    lc.setDigit(0, 2, t2, true);
    lc.setDigit(0, 1, t1, false);
    lc.setRow(0, 0, B00001101);
    Firebase.setFloat("Home1/board1/Clock/segment", ccc);
  }
}
