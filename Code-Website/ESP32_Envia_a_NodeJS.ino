#include <DHT.h>            // Khai báo s? d?ng thu vi?n DHT
// #include <ESP8266WiFi.h>   // Khai báo s? d?ng thu vi?n ESP8266WiFi.h d? thi?t l?p ch? d? HTTP client cho ESP8266
#include <WiFi.h>   // ESP32
#define DHTPIN 4            // Chân d? li?u c?a DHT11 k?t n?i v?i GPIO4 c?a ESP8266
#define DHTTYPE DHT11       // Lo?i DHT du?c s? d?ng

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;          // T?o 1 bi?n client thu?c ki?u WiFiClient
const char* ssid = "Nombre_WiFi";      // Tên m?ng Wifi du?c ch? d?nh s? k?t n?i (SSID)
const char* password = "Clave_WiFi";  // Password c?a m?ng Wifi du?c ch? d?nh s? k?t n?i
const char* server = "IP del servidor, por ejemplo 192.168.1.40";     // Ð?a ch? IP c?a máy khi truy c?p cùng m?ng WiFi
const int port = 8000;                    // Port c?a server dã m?
const int sendingInternval = 2 * 1000;    // Bi?n c?p nh?t d? li?u sau m?i 2s

void setup() {
  Serial.begin(115200);
  dht.begin();                            // Kh?i t?o DHT1 11 d? truy?n nh?n d? li?u
  Serial.println("Connecting");

  // Thi?t l?p ESP8266 là Station và k?t n?i d?n Wifi. in ra d?u `.` trên terminal n?u chua du?c k?t n?i
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\r\nWiFi connected");
}

void loop() {

// Ð?c gía tr? nhi?t d? (d? C), d? ?m. Xu?t ra thông báo l?i và thoát ra n?u d? li?u không ph?i là s?
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  temp = random(0,50); // ALEATORIOS
  humi = random(0,100); // ALEATORIOS
  if (isnan(temp) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(server, port)) {       // Kh?i t?o k?t n?i d?n server thông qua IP và PORT dã m?
  //---------------------------------------------------------------------------------------
    String req_uri = "/update?temp=" + String(temp, 1) + "&humd=" + String(humi, 1);
    client.print("GET " + req_uri + " HTTP/1.1\n" + "Host: "+ server +"\n" + "Connection: close\n" + "Content-Length: 0\n" +"\n\n");   
  //---------------------------------------------------------------------------------------

  // temp, humi chuy?n t? d?nh d?ng float sang d?nh d?ng string và in ra màn hình serial      // terminal trên Arduino.
    Serial.printf("Nhiet do %s - Do am %s\r\n", String(temp, 1).c_str(), String(humi, 1).c_str());
  }
  client.stop();                          // Ng?t k?t n?i d?n server

  delay(sendingInternval);
}