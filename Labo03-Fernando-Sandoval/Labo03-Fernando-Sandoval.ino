// ===== Librerías para OLED =====
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
// Dirección I2C de la OLED 
#define i2c_Address 0x3C

// Dimensiones del display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int pinLM35 = A0; // pin analógico donde está conectado LM35
const unsigned long intervalo = 1000; // intervalo de actualización (1 seg)
unsigned long ultimaMillis = 0;

void setup() {
Serial.begin(9600);
while (!Serial) { }
delay(100);
Serial.println("Iniciando lectura LM35 + OLED...");

delay(250);
display.begin(i2c_Address, true);
display.setContrast(255);
display.clearDisplay();
display.display();
}

void loop() {
unsigned long ahora = millis();

if (ahora - ultimaMillis >= intervalo) {
ultimaMillis = ahora;

int lectura = analogRead(pinLM35);
const float Vref = 5.0;
float voltaje = lectura * (Vref / 1023.0);
float tempC = voltaje * 100.0;

Serial.print("Temperatura: ");
Serial.print(tempC, 2);
Serial.println(" °C");

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SH110X_WHITE);

display.setCursor(10, 10);
display.println("Temperatura:");

display.setTextSize(2);
display.setCursor(15, 30);
display.print(tempC, 1);
display.println(" C");

display.display();
}
}

