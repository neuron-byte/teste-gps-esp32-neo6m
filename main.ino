#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

#define LED_BUILTIN 2

//----
// Código para AI Thinker ESP-32S e NEO-6M
// - Imagem com os pinos do esp32: https://i.pinimg.com/originals/c6/57/83/c657835e84aaf91832a770ea0d7d0767.jpg
// - Datasheet do esp32: https://www.es.co.th/Schemetic/PDF/ESP32.PDF
// - Datasheet do neo-6m: https://www.digikey.com.br/htmldatasheets/production/2757457/0/0/1/neo-6.html
// - Selecione a placa NodeMCU-32S no Arduino IDE
//----

HardwareSerial port(1);
TinyGPSPlus gps;

void setup() {
  port.setRxBufferSize(1024);
  port.begin(9600, SERIAL_8N1, 9, 10);
  Serial.begin(9600);
}

void loop() {
  while(port.available() > 0) {
    if(gps.encode(port.read())) { // se os dados recebidos são válidos
      ler();
    }
  } 
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
}

// gps.distnace_between
// gps.course_to

void ler() {
  Serial.println("---");
  if(gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(", ");
    Serial.print(gps.location.lng(), 6);
    Serial.print(" - lag (ms): ");
    Serial.print(gps.location.age());
    Serial.print(" - ")
  } else {
    Serial.print("Invalido.");
  }

  Serial.print(F("  Data/Hora: "));
  if (gps.date.isValid()) {
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  } else {
    Serial.print(F("Inválido."));
  }

  Serial.print(F(" "));
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  } else {
    Serial.print(F("Inválido"));
  }
  Serial.println();
}
