#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "apakau";
const char* password = "baniiiii"; 
const char* mqtt_broker = "broker.emqx.io";
const int mqtt_port = 1883; 

// Buzzer & LED pin
#define LED_MERAH D2
#define LED_KUNING D3
#define LED_HIJAU D4
#define BUZZER_PIN D1

int suaraBuzzer = 100; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

 void callback(char* topic, byte* payload, unsigned int length) {
  // menampilkan nama topik 
  Serial.print("Pesan diterima di topik: ");
  Serial.print(topic);

  // konversi payload jadi string 
  String data = ""; 
  for (int i=0; i<length; i++){
    Serial.print((char)payload[i]);
    data += (char)payload[i]; 
  }
  Serial.println(" "); 

  // nampilin pesan yang diterima 
  Serial.print("Suhu: ");
  Serial.print(data);

  // mengubah data suhu menjadi float 
  float suhu = data.toFloat();
  if (suhu < 27) {
    digitalWrite(LED_HIJAU, HIGH); 
    digitalWrite(LED_KUNING, LOW); 
    digitalWrite(LED_MERAH, LOW); 
    noTone(BUZZER_PIN);
  } else if (suhu >= 27 && suhu <= 30){
    digitalWrite(LED_KUNING, HIGH);
    digitalWrite(LED_HIJAU, LOW); 
    digitalWrite(LED_MERAH, LOW); 
    noTone(BUZZER_PIN);
  }else{
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW); 
    digitalWrite(LED_KUNING, LOW); 
    tone(BUZZER_PIN, suaraBuzzer);
    delay(1000);
  }
}

// fungsi untuk mengubungkan ke broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Mencoba koneksi ke MQTT...");
    String clientId = "mqttx_pa"; 
    clientId += String(WiFi.macAddress());
    Serial.printf("Client %s mencoba terhubung ke broker MQTT\n", clientId.c_str());
    if (client.connect(clientId.c_str())) {
      Serial.println("Berhasil terhubung");
      // client.subscribe("pa/iot/suhu");
      client.subscribe("pa/iot/suhu");
    } else {
      Serial.print("Gagal terhubung");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  pinMode(LED_MERAH, OUTPUT); 
  pinMode(LED_KUNING, OUTPUT);    
  pinMode(LED_HIJAU, OUTPUT);    
  pinMode(BUZZER_PIN, OUTPUT);    
  
  client.setServer(mqtt_broker, mqtt_port); 
  client.setCallback(callback); 
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}