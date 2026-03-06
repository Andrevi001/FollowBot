#include <WiFi.h>
#include <esp_camera.h>
#include <camera.h>
#include <comunicazioneEsp.h>

/*
// saponetta
const char* ssid = "Andrea-wifi";
const char* password = "YeAndreaMelata";
*/
/*//wifi addis
const char* ssid = "ViganoHouse 1";
const char* password = "CrazyBanana2339";*/
// Wi-Fi giordy
//const char* ssid = "Vodafone-C02180153";
//const char* password = "9TYTJssNKgyyyTeT";

// Hotspot
const char* ssid = "Andrea's S21+";
const char* password = "gskf7724";

// CONFIGURAZIONE SERVER TCP
//saponetta
//const char* server_ip = "192.168.0.160";
//Wifi giordy
//const char* server_ip = "192.168.1.15";
//hotspot
const char* server_ip = "10.113.153.79";
//wifi addis
//const char* server_ip = "192.168.1.17";
//wifi giordy
//const char* server_ip = "192.168.1.12";
const uint16_t server_port = 1234;

SerialTransfer busEsp;
WiFiClient client;

void Riconnessione();
void InvioDatiESPMovimento();
void InvioFrameServer();

void setup() {
  camera_init();

  Serial.begin(115200);
  // 35 -> rx ; 33 -> tx
  Serial2.begin(115200, SERIAL_8N1, 35, 33);
  busEsp.begin(Serial2);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connesso!");
  WiFi.setTxPower(WIFI_POWER_19_5dBm);
  WiFi.setSleep(false);

  // Connessione al server TCP
  Serial.println("Connettendo al server...");
  if (!client.connect(server_ip, server_port)) {
    Serial.println("Connessione fallita!");
  } else {
    Serial.println("Connesso al server.");
    client.setNoDelay(true);
  }
}

void loop() {

  // 0. Riconnessione
  if (!client.connected()) {
    Riconnessione();
  }

  // 1. Invio dati ESP-movimento
  InvioDatiESPMovimento();


  // 2. Invio frame al server
  if (client.connected()) {
    InvioFrameServer();
  }
  
}

void Riconnessione() {
  Serial.println("Riconnessione...");
  client.stop();
  delay(2000);
  if (!client.connect(server_ip, server_port)) {
    return;
  }
  Serial.println("Connesso!");
  client.setNoDelay(true);
}

void InvioDatiESPMovimento() {
  if (client.available() >= 4 && client.connected()) {
    if (client.peek() == 0x80 || client.peek() == 0x90) {
      dati.header = client.read();
      dati.pan_sum = client.read();
      dati.tilt_sum = client.read();
      dati.distance = client.read();
      busEsp.sendDatum(dati);
    } else {
      client.read();
    }
  }
}

void InvioFrameServer() {
  camera_fb_t * fb = esp_camera_fb_get();
  if (fb==NULL) {
    return;
  }
  
  client.write("FRAME");
  client.write((uint8_t *)&fb->len, 4); 
  size_t sent = client.write(fb->buf, fb->len); 
  esp_camera_fb_return(fb);

  if (sent != fb->len) {
    client.stop();
    return;
  }
}