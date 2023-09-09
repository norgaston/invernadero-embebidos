#include <DHT.h>
#include <LiquidCrystal.h> // Incluye la librería para el LCD

#define DHTPIN 2
#define DHTTYPE DHT11

#define FAN_PIN 6 // Ventilador en el pin 6
#define WATER_PUMP_PIN 7 // Bomba de agua en el pin 7
#define GREEN_LED_PIN 11 // LED verde en el pin 11
#define RED_LED_PIN 12 // LED rojo en el pin 12

// Configuración del LCD
LiquidCrystal lcd(10, 9, 8, 5, 4, 3, 2); // RS, RW, E, D4, D5, D6, D7

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2); // Inicializa el LCD de 16x2

  pinMode(FAN_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  digitalWrite(FAN_PIN, LOW);
  digitalWrite(WATER_PUMP_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH);

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  lcd.clear(); // Limpia la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  if (temperature >= 25) {
    digitalWrite(FAN_PIN, HIGH);
  } else {
    digitalWrite(FAN_PIN, LOW);
  }

  if (humidity <= 40) {
    digitalWrite(WATER_PUMP_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  } else {
    digitalWrite(WATER_PUMP_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }

  delay(1000);
}
