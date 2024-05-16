#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

// Wi-Fi dan broker MQTT 
const char *ssid = "Ipppppp"; 
const char *pass = "ipppppp7"; 
const char *mqtt_broker = "broker.emqx.io";
const int mqtt_port = 1883;

// Penggunaan pin  
#define PIR_PIN D6

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi terhubung");
  Serial.println("Alamat IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Mencoba koneksi ke MQTT...");
    String clientId = "mqttx_pa"; 
    clientId += String(WiFi.macAddress());
    Serial.printf("Client %s mencoba terhubung ke broker MQTT\n", clientId.c_str());
    if (client.connect(clientId.c_str())) {
      Serial.println("Berhasil terhubung");
    } else {
      Serial.print("Gagal terhubung");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void publishSuhu() {
  float suhu = mlx.readObjectTempC();
  if (isnan(suhu)) {
    Serial.println("Gagal membaca suhu tubuh");
  } else {
    char suhuString[8];
    dtostrf(suhu, 1, 2, suhuString);
    Serial.print("Mengirim suhu: ");
    Serial.print(suhu);
    Serial.println(" °C");
    client.publish("pa/iot/suhu", suhuString);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT); 
  setup_wifi();
  client.setServer(mqtt_broker, mqtt_port);
  if (!mlx.begin()) {
    Serial.println("Gagal menginisialisasi MLX90614. Periksa koneksi sensor.");
    // Berhenti jika sensor gagal diinisialisasi
    while (1); 
  } else {
    Serial.println("Sensor MLX90614 berhasil diinisialisasi.");
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 

  int gerak = digitalRead(PIR_PIN);
  Serial.print("Status PIR: "); 
  Serial.println(gerak);
  if (gerak == HIGH) {
    if(client.publish("pa/iot/gerak", "Gerakan terdeteksi")){
      Serial.println("========================================");
      Serial.println("Deteksi: Gerakan terdeteksi");
      delay(2000);
      publishSuhu();
       Serial.println("========================================");
    } else {
      Serial.println("Gagal");
    }
  } else {
    if(client.publish("pa/iot/gerak", "Tidak ada gerakan terdeteksi")){
      Serial.println("========================================");
      Serial.println("Deteksi: Tidak ada gerakan terdeteksi");
      Serial.println("========================================");
    } else {
      Serial.println("Gagal");
    }
  }

  delay(5000);
}