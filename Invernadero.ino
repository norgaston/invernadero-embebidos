#include <DHT.h>            // Librería DHT (Adafruit)
#include <LiquidCrystal.h>  // Librería LCD

// Definiciones de pines y tipo de sensor
#define DHTPIN 13      // Pin al que está conectado el sensor DHT11
#define DHTTYPE DHT11  // Tipo de sensor DHT que utilizado

#define FAN_PIN 6         // Pin al que está conectado el motor ventilador
#define WATER_PUMP_PIN 7  // Pin al que está conectada la bomba de agua
#define GREEN_LED_PIN 11  // Pin al que está conectado el LED verde
#define RED_LED_PIN 12    // Pin al que está conectado el LED rojo

// Inicialización del objeto LCD
LiquidCrystal lcd(10, 9, 8, 5, 4, 3, 2); // RS, RW, E, D4, D5, D6, D7

DHT dht(DHTPIN, DHTTYPE);  // Creación de una instancia del objeto DHT

void setup() {
  lcd.begin(16, 2);  // Inicializa el LCD de 16x2

  // Configuración de pines como salidas
  pinMode(FAN_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  // Apaga todos los componentes al inicio
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(WATER_PUMP_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  dht.begin();  // Inicializa el sensor DHT11

  // Muestra los títulos en el LCD al inicio
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Humedad:     ");
  lcd.setCursor(14, 0);  // Coloca el cursor después de "Temp: "
  lcd.write(223);        // Código para el símbolo de grados Celsius (°C)
  lcd.write("C");        // Muestra el símbolo de grados Celsius
  lcd.setCursor(14, 1);  // Coloca el cursor después de "Humedad: "
  lcd.print("%");        // Muestra el símbolo de porcentaje
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Actualiza solo los valores de temperatura y humedad en el LCD
  lcd.setCursor(9, 0);        // Posición para la temperatura
  lcd.print(temperature, 1);  // Mostrar un decimal para la temperatura
  lcd.setCursor(9, 1);        // Posición para la humedad
  lcd.print(humidity, 1);     // Mostrar un decimal para la humedad

  // Control de componentes según las condiciones
  if (temperature >= 25) {
    digitalWrite(FAN_PIN, HIGH);  // Enciende el motor ventilador
  } else {
    digitalWrite(FAN_PIN, LOW);  // Apaga el motor ventilador
  }

  if (humidity <= 40) {
    digitalWrite(WATER_PUMP_PIN, HIGH);  // Enciende la bomba de agua
    digitalWrite(GREEN_LED_PIN, HIGH);   // Enciende el LED verde
    digitalWrite(RED_LED_PIN, LOW);      // Apaga el LED rojo
  } else {
    digitalWrite(WATER_PUMP_PIN, LOW);  // Apaga la bomba de agua
    digitalWrite(GREEN_LED_PIN, LOW);   // Apaga el LED verde
    digitalWrite(RED_LED_PIN, HIGH);    // Enciende el LED rojo
  }

  delay(1000);  // Pausa de 1 segundo entre cada ciclo de lectura y control
}
