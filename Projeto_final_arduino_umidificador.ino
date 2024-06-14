#include "DHT.h"

#define DHTPIN 7          // Pino do sensor DHT22
#define DHTTYPE DHT22     // Tipo do sensor DHT22
#define RELAYPIN 8        // Pino do módulo relé

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, HIGH);  // Desliga o relé (assumindo que HIGH é desligado)
}

void loop() {
  // Espera alguns segundos entre leituras
  delay(2000);

  // Lê a umidade
  float h = dht.readHumidity();
  
  // Checa se houve uma falha na leitura e sai se for o caso
  if (isnan(h)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  }

  // Imprime os valores lidos
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.println(" %");

  // Define o limite de umidade
  float humidityThreshold = 80.0;  // Altere para o valor desejado

  // Controla o umidificador com base na umidade lida
  if (h < humidityThreshold) {
    digitalWrite(RELAYPIN, LOW);  // Liga o umidificador
    Serial.println("Umidificador LIGADO");
  } else {
    digitalWrite(RELAYPIN, HIGH); // Desliga o umidificador
    Serial.println("Umidificador DESLIGADO");
  }
}
