#include "HX711.h"

#define DOUT A1
#define CLK A0

HX711 balanza;

void setup() {
balanza.begin(DOUT, CLK);
Serial.begin(9600);
Serial.print("Lectura del valor del ADC: ");
Serial.println(balanza.read());
Serial.println("No ponga ningun objeto sobre la balanza");
Serial.println("Destarando...");
Serial.println("...");
balanza.set_scale(227891); // Establecemos la escala
balanza.tare(20); //El peso actual es considerado Tara.

Serial.println("Listo para pesar");
}

void loop() {
Serial.println(balanza.read());
Serial.print("Peso: ");
Serial.print(balanza.get_units(2),3);
Serial.println(" kg");
delay(100);
}
