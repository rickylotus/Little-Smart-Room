#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define DHTPIN 4                                            // Menentukan Pin  DHT22
#define DHTTYPE DHT22                                       // Menentukan Tipe Sensor Suhu yang Dipakai

DHT dht(DHTPIN, DHTTYPE);
int ledPin = 5;                                             // Menentukan pin LED
int inputPin = 2;                                           // Menentukan pin Sensor PIR
int val = 0;                                                // Variabel untuk menyimpan hasil input sensor PIR
char auth[] = "0e39881650cd4b05a53a020f67eb62b8";           // Token Blynk
char ssid[] = "RICKY";                                      // SSID Wifi
char pass[] = "L0nghumen";                                  // Password Wifi
 
void setup() {  
  pinMode(ledPin, OUTPUT);                                  // Mendeklarasikan LED sebagai Output      
  pinMode(inputPin, INPUT);                                 // Mendeklarasikan Sensor PIR sebagai Input
  Blynk.begin(auth, ssid, pass);                            // Connectkan blynk ke Board ESP8266
  dht.begin();                                              // Menjalankan Sensor DHT22
}

void loop() {
  Blynk.run();                                               // Menjalankan Blynk
  val = digitalRead(inputPin);                               // Mambaca Nilai input Sensor Pir
  float h = dht.readHumidity();                              // Mambaca Nilai Kelembaban Sensor DHT22
  float t = dht.readTemperature();                           // Mambaca Nilai Suhu Sensor DHT22
  float q = analogRead(A0);                                  // Mambaca Nilai Kualitas Udara Sensor MQ-135
  Blynk.virtualWrite(V5, t);                                 // Mengirim nilai Suhu ke pin V5 pada blynk
  Blynk.virtualWrite(V6, h);                                 // Mengirim nilai Kelembaban ke pin V6 pada blynk
  Blynk.virtualWrite(V0, q);                                 // Mengirim nilai Kualitas Udara ke pin V0 pada blynk
  if (q>400) {                                               // Kondisi Jika nilai kualitas udara diatas 400 maka akan keluar notifikasi di HP
    Blynk.notify("Kadar Udara Berbahaya");
  }
  if (t>70) {                                                // Kondisi Jika nilai kualitas udara diatas 400 maka akan keluar notifikasi di HP
    Blynk.notify("Suhu Terlalu Panas");
  }
}
