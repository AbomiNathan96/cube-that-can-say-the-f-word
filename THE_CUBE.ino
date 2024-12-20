/*
  Basic library example for TM1640. Kept small to fit in the limited space of an ATtiny44.

  Library based on TM1638 library by Ricardo Batista, adapted by Maxint-RD MMOLE 2018.
  Confirmed to work in the following environments:
      ATtiny44A using Arduino IDE 1.8.2 and ATTinyCore (8MHz, LTO enabled), 3232 bytes flash, 103 bytes RAM
      ATtiny44A using Arduino IDE 1.8.2 and ATtiny Microcontrolers (8MHz), 3212 bytes flash, 103 bytes RAM ==> 2892/95 ==> 2878/95

  Only compiled: not tested yet:
      Arduino Nano using Arduino IDE 1.8.2, Nano (Old Bootloader)), 3176 bytes flash, 95 bytes RAM

  For more information see  https://github.com/maxint-rd/TM16xx
*/
#include <TM1640.h>

#if !defined(LED_BUILTIN)
#define LED_BUILTIN 4
#endif

// Define a 4-digit display module. Pin suggestions:
// ESP8266 (Wemos D1): data pin 5 (D1), clock pin 4 (D2)
// ATtiny44A: data pin 9, clock pin 10 (LED_BUILTIN: 8 on ATTinyCore)
TM1640 module(3, 2, 4);    // data, clock, 4 digitsS

String test = "   ";
int in = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  module.clearDisplay();
  module.setupDisplay(true,1);
  displayString("TEST");
  delay(100);
  module.clearDisplay();
}

void pm() {
  module.setSegments(byte(0b10000000), byte(0));
}

void colon() {
  module.setSegments(byte(0b10000000), byte(1));
}

void dot() {
  module.setSegments(byte(0b10000000), byte(2));
}

void bell() {


  module.setSegments(byte(0b10000000), byte(3));
}

void displayString(String input) {
  input.trim();
  if (input == "") {
    return;
  }
  if (input.length() == 1) {
    input += "   ";
  }
  if (input.length() == 2) {
    input += "  ";
  }
  if (input.length() == 3) {
    input += " ";
  }

  for (int i = 0; i < input.length()-3; i ++) {
    delay(100);
    module.sendAsciiChar(byte(0),input[0+i],false);
    module.sendAsciiChar(byte(1),input[1+i],false);
    module.sendAsciiChar(byte(2),input[2+i],false);
    module.sendAsciiChar(byte(3),input[3+i],false);
  }
}

void loop()
{
  // reply only when you receive data:


  while (Serial.available() > 0) {

    // read the incoming byte:

    in = Serial.read();
    if (in != 10) {
      test += char(in);
    }
    

  }
  if (in == 10) {
    displayString(test);
    Serial.println(test);
    test = "";
  }
  
  

}
