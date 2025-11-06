#include <Arduino.h>

// Pin del botón
const int botonPin = 0; // cambia al pin que uses
// Estado anterior y actual
bool estadoBotonActual = HIGH;
bool estadoBotonAnterior = HIGH;

// Tiempo de espera para 5 segundos (en milisegundos)
const unsigned long tiempoRequerido = 5000;

// Marca si ya ejecutaste el código tras 5 segundos
bool ejecutado = false;

// Tiempo cuando se detectó la presión inicial
unsigned long tPresionadoInicio = 0;

void setup() {
  Serial.begin(115200);
  pinMode(botonPin, INPUT_PULLUP); // si usas pull-up interno
  // Si tu botón es activo alto, cambia a INPUT y usa external pull-down
}

void loop() {
  estadoBotonActual = digitalRead(botonPin);

  //DETECCION DE FLANCO DE BAJADA - Detectar inicio de presión
  if (estadoBotonActual == LOW && estadoBotonAnterior == HIGH) {
    // El botón acaba de empezar a pulsarse
    tPresionadoInicio = millis();
    ejecutado = false; // reseteamos bandera para este ciclo de presión
  }
  ////////////////////

  // Si está presionado, calcular cuánto tiempo lleva
  if (estadoBotonActual == LOW) {
    unsigned long duracion = millis() - tPresionadoInicio;
    if (!ejecutado && duracion >= tiempoRequerido) {
      // Aquí va el código que quieres ejecutar al alcanzar 5 segundos
      Serial.println("Botón presionado 5 segundos. Ejecuto código.");
      // ---- PON TU CÓDIGO AQUÍ ----
      // Ejemplo: encender LED, mandar una señal, etc.
      
      ejecutado = true; // para que no se vuelva a ejecutar mientras siga presionado, evita que, si nunca se suelta el boton, se ejecute de nuevo la accion
    }
  } else {
    // Si se suelta, reiniciamos estado (y permitimos volver a empezar)
    ejecutado = false;
  }

  // Guardar estado para la siguiente iteración
  estadoBotonAnterior = estadoBotonActual;
}