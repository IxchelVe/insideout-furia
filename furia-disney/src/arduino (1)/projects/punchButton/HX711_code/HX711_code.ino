 #include "HX711.h"
#include <toneAC.h>

const int DOUT = A1;
const int CLK = A0;
float current_reading;
float peak_reading = 0;
bool is_new_lecture = false;
unsigned int limit = 0;
//const int speaker = 9;
HX711 balanza;

void setup() {
  Serial.begin(57600);
  balanza.begin(DOUT, CLK);
  pinMode(2, OUTPUT);
  //pinMode(speaker, OUTPUT);
  //Serial.print("Lectura del valor del ADC:  ");
  //Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la palanca");
  Serial.println("Destarando...");
  Serial.println("...");
  //balanza.set_scale(439430.25); // Establecemos la escala
  balanza.set_scale(55661.8); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.

  Serial.println("Listo para golpear");
  digitalWrite(2, HIGH);
  //sound(277, 10, 500, 2000);
}

void loop() {
  current_reading = (balanza.get_units(20)) * -100;
  if (current_reading > limit)
  {
    digitalWrite(2, LOW);
    is_new_lecture = true;

  }
  if (is_new_lecture) {
    peak_reading = current_reading;
    is_new_lecture = false;
    //sound(261, 2, 1000, 2000);
    digitalWrite(2, LOW);
    Serial.print("Pico: ");
    Serial.print(peak_reading);
    Serial.print("\t");
    //sonido de intensidad
    int intValue = intensity(peak_reading);
    sound(277, intValue, 1000, 1000);
  } else {
    if (current_reading > peak_reading) {
      peak_reading = current_reading;
    }
    if (current_reading < limit)
    {
      is_new_lecture = false;
      digitalWrite(2, HIGH);
    }
  }
  //Serial.print("Peso: ");
  //Serial.print(current_reading);
  //Serial.println(" kg");
  delay(1);
}

void sound(unsigned int freq, int volume, unsigned int dur, unsigned int pause)
{
  toneAC(freq, volume);
  delay(dur);
  toneAC();
  delay(pause);
}

int intensity(float value)
{
  int volume;
  if (value < 10)
  {
    volume = 2;
  }
  if (value > 10 && value < 15)
  {
    volume = 5;
  }
  if (value > 15 && value < 20)
  {
    volume = 8;
  }
  if (value > 20)
  {
    volume = 10;
  }
  return volume;
}
