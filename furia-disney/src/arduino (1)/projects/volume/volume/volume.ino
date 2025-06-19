#include <toneAC.h>

void setup() {} // Nothing to setup, just start playing!

void loop() {
//  for (unsigned long freq = 125; freq <= 15000; freq += 10) {  
//    toneAC(freq,2); // Play the frequency (125 Hz to 15 kHz in 10 Hz steps).
//    delay(1);     // Wait 1 ms so you can hear it.
//  }
//  toneAC(); // Turn off toneAC, can also use noToneAC().
//
//  while(1); // Stop (so it doesn't repeat forever driving you crazy--you're welcome).

toneAC(277,10);
delay(1000);
toneAC();

toneAC(277,6);
delay(1000);
toneAC();

toneAC(277,2);
delay(1000);
toneAC();

while(6);
}
