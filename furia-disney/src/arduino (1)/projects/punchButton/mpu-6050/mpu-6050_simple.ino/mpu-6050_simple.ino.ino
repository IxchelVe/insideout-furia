// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <toneAC.h>
// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor;

// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int ax, ay, az;
int gx, gy, gz;
float current_reading;
unsigned int peak_reading = 0;
unsigned int limit = 20;
bool is_new_lecture = false;
void setup() {
  Serial.begin(57600);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C
  sensor.initialize();    //Iniciando el sensor
  pinMode(2, OUTPUT);  // led
  if (sensor.testConnection())
  { Serial.println("Sensor iniciado correctamente");
    digitalWrite(2, HIGH);
  } else {
    Serial.println("Error al iniciar el sensor");
  }
}


void loop() {
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);
  //float ax_m_s2 = ax * (9.81/16384.0);
  //float ay_m_s2 = ay * (9.81/16384.0);
  float az_m_s2 = az * (9.81/16384.0);
  // Leer las aceleraciones y velocidades angulares
  
  
  current_reading = gy * (250.0/32768.0);

  //Mostrar las lecturas separadas por un [tab]
  //Serial.print("[x y z] [x y z]:\t");
  //Serial.print("acx \t agy\n");
  //Serial.print(ax); Serial.print("\t");
  //Serial.print(ay); Serial.print("\t");
  //Serial.println(az_m_s2); //Serial.print("\t");
  
  //Serial.print(gy); Serial.print("\t");
  
  if (current_reading > limit)
  {
    digitalWrite(2, LOW);
    is_new_lecture = true;

  }
  if (is_new_lecture) {
    peak_reading = current_reading;
    is_new_lecture =  false;
    //sound(261, 2, 1000, 2000);
    digitalWrite(2, LOW);
    //Serial.print("Pico: ");
    Serial.print(peak_reading);
    Serial.print("\t");
    Serial.print(az_m_s2); Serial.print("\n");
    
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
    delay(5);
  }
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
    if (value < 80)
    {
      volume = 2;
    }
    if (value > 80 && value < 160)
    {
      volume = 2;
    }
    if (value > 160 && value < 220)
    {
      volume = 2;
    }
    if (value > 220)
    {
      volume = 2;
    }
    return volume;
  }
