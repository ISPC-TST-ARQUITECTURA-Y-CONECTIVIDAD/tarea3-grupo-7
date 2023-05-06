#include <OneWire.h>
#include <DallasTemperature.h>

// Configuración del sensor de temperatura
#define ONE_WIRE_BUS 14
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Configuración del pin de salida de la luz
#define LIGHT_PIN 25

// Configuración del pin de entrada del botón
#define BUTTON_PIN 15

void setup() {
  // Configurar el sensor de temperatura
  sensors.begin();

  // Configurar el pin de salida de la luz como PWM
  ledcAttachPin(LIGHT_PIN, 1);
  ledcSetup(1, 5000, 10);

  // Configurar el pin de entrada del botón como entrada
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Leer la temperatura del sensor
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // Controlar la luz con el valor de temperatura
  int brightness = map(temperature, 0, 100, 0, 1023);
  ledcWrite(1, brightness);

  // Detectar el estado del botón
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {
    // Encender la luz si el botón está presionado
    digitalWrite(LIGHT_PIN, HIGH);
  } else {
    // Apagar la luz si el botón está suelto
    digitalWrite(LIGHT_PIN, LOW);
  }
}
