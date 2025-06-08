#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22

#define RED_LED_PIN 13   
#define GREEN_LED_PIN 12 

const char* WIFI_NAME = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
const char* THINGSPEAK_API_KEY = "YUGY2SMMR53QH201";  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  dht.begin();

  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.println("🔄 Conectando ao Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("⏳ Aguardando conexão Wi-Fi...");
  }
  Serial.println("✅ Conectado! IP: " + String(WiFi.localIP()));
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  float windSpeed = random(0, 50);  

  if (isnan(temp) || isnan(hum)) {
    Serial.println("⚠️ Erro no sensor. Usando valores simulados.");
    temp = random(10, 45);
    hum = random(30, 90);
  }

  Serial.println("📍 Leitura Atual:");
  Serial.println("🌡️ Temp: " + String(temp, 1) + " °C");
  Serial.println("💧 Umidade: " + String(hum, 1) + " %");
  Serial.println("🌬️ Vento: " + String(windSpeed, 1) + " km/h");

  if (temp < 12 || temp > 35 || hum < 40 || hum > 70) {
    digitalWrite(RED_LED_PIN, HIGH);   // Liga LED vermelho
    digitalWrite(GREEN_LED_PIN, LOW);  // Desliga LED verde
    Serial.println("🚨 Alerta de condição extrema.");
  } else {
    digitalWrite(RED_LED_PIN, LOW);    // Desliga LED vermelho
    digitalWrite(GREEN_LED_PIN, HIGH); // Liga LED verde
    Serial.println("✅ Ambiente estável.");
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://api.thingspeak.com/update?api_key=" + String(THINGSPEAK_API_KEY) +
                 "&field1=" + String(temp) +
                 "&field2=" + String(hum) +
                 "&field3=" + String(windSpeed);

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.println("📤 Dados enviados ao ThingSpeak! Código: " + String(httpResponseCode));
    } else {
      Serial.println("❌ Falha ao enviar.");
    }
    http.end();
  }

  Serial.println("--------------------------------------------------");
  delay(15000);
}
