#include <DHT.h> // Incluye la librería para el sensor DHT11

#define DHTPIN 2    // Pin al que está conectado el sensor DHT11
#define DHTTYPE DHT11   // Tipo de sensor DHT que estás utilizando

#define FAN_PIN 3    // Pin al que está conectado el motor ventilador
#define WATER_PUMP_PIN 4   // Pin al que está conectada la bomba de agua
#define GREEN_LED_PIN 5   // Pin al que está conectado el LED verde
#define RED_LED_PIN 6   // Pin al que está conectado el LED rojo

DHT dht(DHTPIN, DHTTYPE); // Crea una instancia del objeto DHT

void setup() {
  pinMode(FAN_PIN, OUTPUT); // Configura el pin del motor ventilador como salida
  pinMode(WATER_PUMP_PIN, OUTPUT); // Configura el pin de la bomba de agua como salida
  pinMode(GREEN_LED_PIN, OUTPUT); // Configura el pin del LED verde como salida
  pinMode(RED_LED_PIN, OUTPUT); // Configura el pin del LED rojo como salida
  
  digitalWrite(FAN_PIN, LOW); // Apaga el motor ventilador al inicio
  digitalWrite(WATER_PUMP_PIN, LOW); // Apaga la bomba de agua al inicio
  digitalWrite(GREEN_LED_PIN, LOW); // Apaga el LED verde al inicio
  digitalWrite(RED_LED_PIN, HIGH); // Enciende el LED rojo al inicio
  
  dht.begin(); // Inicializa el sensor DHT11
}

void loop() {
  float temperature = dht.readTemperature(); // Lee la temperatura del sensor DHT11
  float humidity = dht.readHumidity(); // Lee la humedad del sensor DHT11
  
  if (temperature >= 25) {
    // Si la temperatura es igual o superior a 25 grados Celsius, enciende el motor ventilador
    digitalWrite(FAN_PIN, HIGH);
  } else {
    // Si la temperatura desciende por debajo de 25 grados Celsius, apaga el motor ventilador
    digitalWrite(FAN_PIN, LOW);
  }
  
  if (humidity <= 40) {
    // Si la humedad es menor o igual al 40%, enciende la bomba de agua y el LED verde, y apaga el LED rojo
    digitalWrite(WATER_PUMP_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  } else {
    // Si la humedad asciende por encima del 40%, apaga la bomba de agua y el LED verde, y enciende el LED rojo
    digitalWrite(WATER_PUMP_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }
  
  delay(1000);  // Pausa de 1 segundo entre cada ciclo de lectura y control
}
