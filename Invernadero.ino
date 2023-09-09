#include <DHT.h>
#include <LiquidCrystal.h>  // Incluye la librería para el LCD

#define DHTPIN 13
#define DHTTYPE DHT11

#define FAN_PIN 6         // Ventilador en el pin 6
#define WATER_PUMP_PIN 7  // Bomba de agua en el pin 7
#define GREEN_LED_PIN 11  // LED verde en el pin 11
#define RED_LED_PIN 12    // LED rojo en el pin 12

// Configuración del LCD
LiquidCrystal lcd(10, 9, 8, 5, 4, 3, 2);  // RS, RW, E, D4, D5, D6, D7

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);  // Inicializa el LCD de 16x2

  pinMode(FAN_PIN, OUTPUT);         // Configura el pin del ventilador como salida
  pinMode(WATER_PUMP_PIN, OUTPUT);  // Configura el pin de la bomba de agua como salida
  pinMode(GREEN_LED_PIN, OUTPUT);   // Configura el pin del LED verde como salida
  pinMode(RED_LED_PIN, OUTPUT);     // Configura el pin del LED rojo como salida

  digitalWrite(FAN_PIN, LOW);         // Apaga el ventilador al inicio
  digitalWrite(WATER_PUMP_PIN, LOW);  // Apaga la bomba de agua al inicio
  digitalWrite(GREEN_LED_PIN, LOW);   // Apaga el LED verde al inicio
  digitalWrite(RED_LED_PIN, LOW);     // Apaga el LED rojo al inicio

  dht.begin();  // Inicializa el sensor DHT11
}

void loop() {
  float temperature = dht.readTemperature();  // Lee la temperatura del sensor
  float humidity = dht.readHumidity();        // Lee la humedad del sensor

  lcd.clear();  // Limpia la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp.: ");
  lcd.print(temperature);
  lcd.print(" ");
  lcd.write(0xDF);  // Inserta el símbolo de grado centígrado (°)
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humedad: ");
  lcd.print(humidity);
  lcd.print(" %");

  if (temperature >= 25) {
    digitalWrite(FAN_PIN, HIGH);  // Enciende el ventilador si la temperatura es mayor o igual a 25°C
  } else {
    digitalWrite(FAN_PIN, LOW);  // Apaga el ventilador si la temperatura es menor a 25°C
  }

  if (humidity <= 40) {
    digitalWrite(WATER_PUMP_PIN, HIGH);  // Enciende la bomba de agua y el LED verde si la humedad es menor o igual al 40%
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);  // Apaga el LED rojo
  } else {
    digitalWrite(WATER_PUMP_PIN, LOW);  // Apaga la bomba de agua y el LED verde si la humedad es mayor al 40%
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);  // Enciende el LED rojo
  }

  delay(1000);  // Espera 1 segundo antes de volver a ejecutar el bucle
}
