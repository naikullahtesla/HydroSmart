#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "SuperMon.h"


#define USE_INTRANET
#define LOCAL_SSID "HUAWEI-R7fn"
#define LOCAL_PASS "BJyJVG6u"
#define AP_SSID "TestWebSite"
#define AP_PASS "023456789"

const int shadePin = 27;
const int controlPin1_A = 0;
const int controlPin1_B = 2;
int flowSensor = 34;
int pacflowSensor = 12;
int dcflowSensor = 17;
int catflowSensor = 14;

const int trigPin = 32;
const int echoPin = 33;
long duration = 0;
int distance = 0;
const int shadeValue  = 0;

long currentMillis = 0; //  effluent flow rate
long previousMillis = 0;
int interval = 1000;
//boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

//pac
long paccurrentMillis  = 0;
long pacpreviousMillis = 0;
int pacinterval = 1000;
//boolean ledState = LOW;
float paccalibrationFactor = 4.5;
volatile byte pacpulseCount;
byte pacpulse1Sec = 0;
unsigned int pacflowMilliLitres;
unsigned long pactotalMilliLitres;

//dc
long dccurrentMillis  = 0;
long dcpreviousMillis = 0;
int dcinterval = 1000;
//boolean ledState = LOW;
float dccalibrationFactor = 4.5;
volatile byte dcpulseCount;
byte dcpulse1Sec = 0;
unsigned int dcflowMilliLitres;
unsigned long dctotalMilliLitres;

//cat
long catcurrentMillis  = 0;
long catpreviousMillis = 0;
int catinterval = 1000;
//boolean ledState = LOW;
float catcalibrationFactor = 4.5;
volatile byte catpulseCount;
byte catpulse1Sec = 0;
unsigned int catflowMilliLitres;
unsigned long cattotalMilliLitres;

float pacflowRate;
float dcflowRate;
float catflowRate;

uint32_t SensorUpdate = 0;

int pwmValue  = 0;
char XML[2048];
char buf[32];

IPAddress Actual_IP;
IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

WebServer server(80);

void IRAM_ATTR pulseCounter();
void IRAM_ATTR pacpulseCounter();
void IRAM_ATTR dcpulseCounter();
void IRAM_ATTR catpulseCounter();
void printWifiStatus();
void SendWebsite();
void SendXML();
void UpdateSlider();

void setup() {
  Serial.begin(115200);
  disableCore0WDT();

  Serial.println("starting server");
  pinMode(shadePin, INPUT);
  pinMode(controlPin1_A, OUTPUT);
  pinMode(controlPin1_B, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(flowSensor, INPUT_PULLUP);
  pinMode(pacflowSensor, INPUT_PULLUP);
  pinMode(dcflowSensor, INPUT_PULLUP);
  pinMode(catflowSensor, INPUT_PULLUP);
  //effluentflow
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres;
  previousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(flowSensor), pulseCounter, FALLING);
  //pac
  pacpulseCount = 0;
  pacflowRate = 0.0;
  pacflowMilliLitres = 0;
  pactotalMilliLitres;
  pacpreviousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(pacflowSensor), pacpulseCounter, FALLING);
  //dc
  dcpulseCount = 0;
  dcflowRate = 0.0;
  dcflowMilliLitres = 0;
  dctotalMilliLitres;
  dcpreviousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(dcflowSensor), dcpulseCounter, FALLING);
  //cat
  catpulseCount = 0;
  catflowRate = 0.0;
  catflowMilliLitres = 0;
  cattotalMilliLitres;
  catpreviousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(catflowSensor), catpulseCounter, FALLING);

#ifdef USE_INTRANET
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
#endif

#ifndef USE_INTRANET
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: ");
  Serial.println(Actual_IP);
#endif

  printWifiStatus();

  server.on("/", SendWebsite);
  server.on("/xml", SendXML);
  server.on("/UPDATE_SLIDER", UpdateSlider);
  
  server.begin();
}

void loop() {

  server.handleClient();
  currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    pulse1Sec = pulseCount;
    pulseCount = 0;

    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
    delay(1000);
  }
  
  if (paccurrentMillis - pacpreviousMillis > pacinterval) 
  {
    pacpulse1Sec = pacpulseCount;
    pacpulseCount = 0;

    pacflowRate = ((1000.0 / (millis() - pacpreviousMillis)) * pacpulse1Sec) / paccalibrationFactor;
    pacpreviousMillis = millis();

    pacflowMilliLitres = (pacflowRate / 60) * 1000;
    pactotalMilliLitres += pacflowMilliLitres;
    delay(1000);
  }

  if (dccurrentMillis - dcpreviousMillis > dcinterval) 
  {
    dcpulse1Sec = dcpulseCount;
    dcpulseCount = 0;

    dcflowRate = ((1000.0 / (millis() - dcpreviousMillis)) * dcpulse1Sec) / dccalibrationFactor;
    dcpreviousMillis = millis();

    dcflowMilliLitres = (dcflowRate / 60) * 1000;
    dctotalMilliLitres += dcflowMilliLitres;
    delay(1000);
  }

  if (catcurrentMillis - catpreviousMillis > pacinterval) 
  {
    catpulse1Sec = catpulseCount;
    catpulseCount = 0;

    catflowRate = ((1000.0 / (millis() - catpreviousMillis)) * catpulse1Sec) / catcalibrationFactor;
    catpreviousMillis = millis();

    catflowMilliLitres = (catflowRate / 60) * 1000;
    cattotalMilliLitres += catflowMilliLitres;
  }
  int shadeValue = map(analogRead(shadePin),  0, 2000, 20,  0);
  
    digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        shadeValue = map(analogRead(shadePin),  0, 2000, 20,  0);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Flow rate: ");
  Serial.print(int(flowRate));
  Serial.print("L/min");
  Serial.print("\t");
  
  Serial.print("PAC Flow rate: ");
  Serial.print(int(pacflowRate));
  Serial.print("L/min");
  Serial.print("\t");

  Serial.print("DC Flow rate: ");
  Serial.print(int(dcflowRate));
  Serial.print("L/min");
  Serial.print("\t");
  
  Serial.print("Cat Flow rate: ");
  Serial.print(int(flowRate));
  Serial.print("L/min");
  Serial.print("\t");

  Serial.print("Output Liquid Quantity: ");
  Serial.print(totalMilliLitres);
  Serial.print("mL / ");
  Serial.print(totalMilliLitres / 1000);
  Serial.println("L");

  Serial.print(distance);
  Serial.print(",");
  Serial.print(shadeValue);

  int pwmValue = map(shadeValue, 0, 20, 0, 255);

  if (distance > 3) {
    analogWrite(controlPin1_A, 0);
    analogWrite(controlPin1_B, 0);
  } else {
    analogWrite(controlPin1_A, pwmValue);
    analogWrite(controlPin1_B, 0);
    delay(100);
  }
  if (shadeValue > 100) {
    analogWrite(controlPin1_A, 0);
    analogWrite(controlPin1_B, 0);
  } else {
    analogWrite(controlPin1_A, pwmValue);
    analogWrite(controlPin1_B, 0);
    delay(100);
  }

}
void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

void IRAM_ATTR pacpulseCounter() {
  pulseCount++;
}

void IRAM_ATTR dcpulseCounter() {
  pulseCount++;
}

void IRAM_ATTR catpulseCounter() {
  pulseCount++;
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  Serial.print("Open http://");
  Serial.println(ip);
}

void SendWebsite() {
  Serial.println("sending web page");
  server.send(200, "text/html", PAGE_MAIN);
}

void SendXML() {
  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  int shadeValue = map(analogRead(shadePin),  0, 2000,  20, 0);
  
  sprintf(buf, "<B0>%d</B0>\n", shadeValue );
  strcat(XML, buf);

  // sprintf(buf, "<V0>%d.%d</V0>\n", int(VoltsA0), int(VoltsA0 * 10) % 10);
  // strcat(XML, buf);
  if (currentMillis - previousMillis > interval) 
  {
    pulse1Sec = pulseCount;
    pulseCount = 0;

    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
    delay(1000);
  }
  
  if (paccurrentMillis - pacpreviousMillis > pacinterval) 
  {
    pacpulse1Sec = pacpulseCount;
    pacpulseCount = 0;

    pacflowRate = ((1000.0 / (millis() - pacpreviousMillis)) * pacpulse1Sec) / paccalibrationFactor;
    pacpreviousMillis = millis();

    pacflowMilliLitres = (pacflowRate / 60) * 1000;
    pactotalMilliLitres += pacflowMilliLitres;
    delay(1000);
  }

  if (dccurrentMillis - dcpreviousMillis > dcinterval) 
  {
    dcpulse1Sec = dcpulseCount;
    dcpulseCount = 0;

    dcflowRate = ((1000.0 / (millis() - dcpreviousMillis)) * dcpulse1Sec) / dccalibrationFactor;
    dcpreviousMillis = millis();

    dcflowMilliLitres = (dcflowRate / 60) * 1000;
    dctotalMilliLitres += dcflowMilliLitres;
    delay(1000);
  }

  if (catcurrentMillis - catpreviousMillis > pacinterval) 
  {
    catpulse1Sec = catpulseCount;
    catpulseCount = 0;

    catflowRate = ((1000.0 / (millis() - catpreviousMillis)) * catpulse1Sec) / catcalibrationFactor;
    catpreviousMillis = millis();

    catflowMilliLitres = (catflowRate / 60) * 1000;
    cattotalMilliLitres += catflowMilliLitres;
    delay(1000);
  }

  sprintf(buf, "<B1>%d</B1>\n", distance);
  strcat(XML, buf);
  
  sprintf(buf, "<F1>%0.2f</F1>\n",  flowRate);
  strcat(XML, buf);
  
  sprintf(buf, "<T1>%0.2f</T1>\n",  pacflowRate);
  strcat(XML, buf);

  sprintf(buf, "<T2>%0.2f</T2>\n",  dcflowRate);
  strcat(XML, buf);

  sprintf(buf, "<T3>%0.2f</T3>\n",  catflowRate);
  strcat(XML, buf);

  sprintf(buf, "<F2>%0.2f</F2>\n",  totalMilliLitres);
  strcat(XML, buf);
  // sprintf(buf, "<V1>%d.%d</V1>\n", int(VoltsA1), int(VoltsA1 * 10) % 10);
  // strcat(XML, buf);

  // sprintf(buf, "<D0>%d.%d</D0>\n", int(distance), int(distance * 10) % 10);
  // strcat(XML, buf);

  strcat(XML, "</Data>\n");
  server.send(200, "text/xml", XML);
}

void UpdateSlider() {
  Serial.println("updating slider");
  String sliderValue = server.arg("plain");
  pwmValue = sliderValue.toInt();
  ledcWrite(0, pwmValue);
}


