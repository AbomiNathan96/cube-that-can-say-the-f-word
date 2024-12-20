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
TM1640 module(3, 2, 4);    // data, clock, 4 digits
/* Rick Roll Code

AUTHOR: Samantha Lagestee

Copyright 2017 samilagestee at gmail dot com


    This program is free software: you can redistribute it and/or

    modify it under the terms of the GNU General Public License as

    published by the Free Software Foundation, either version 3 of

    the License, or (at your option) any later version.


    DISCLAIMER: The song "Never Gonna Give You Up" by Rick Astley

    is not the creative property of the author. This code simply

    plays a Piezo buzzer rendition of the song.


*/


#define a3f 208 // 208 Hz

#define b3f 233 // 233 Hz

#define b3 247 // 247 Hz

#define c4 261 // 261 Hz MIDDLE C

#define c4s 277 // 277 Hz

#define e4f 311 // 311 Hz

#define f4 349 // 349 Hz

#define a4f 415 // 415 Hz

#define b4f 466 // 466 Hz

#define b4 493 // 493 Hz

#define c5 523 // 523 Hz

#define c5s 554 // 554 Hz

#define e5f 622 // 622 Hz

#define f5 698 // 698 Hz

#define f5s 740 // 740 Hz

#define a5f 831 // 831 Hz


#define rest -1


// change these pins according to your setup

int piezo = 4;

int led = 9;


volatile int beatlength = 100; // determines tempo

float beatseparationconstant = 0.3;


int a; // part index

int b; // song index

int c; // lyric index


boolean flag; // play/pause


// Parts 1 and 2 (Intro)


int song1_intro_melody[] =

{c5s, e5f, e5f, f5, a5f, f5s, f5, e5f, c5s, e5f, rest, a4f, a4f};


int song1_intro_rhythmn[] =

{6, 10, 6, 6, 1, 1, 1, 1, 6, 10, 4, 2, 10};


// Parts 3 or 5 (Verse 1)


int song1_verse1_melody[] =

{ rest, c4s, c4s, c4s, c4s, e4f, rest, c4, b3f, a3f,

rest, b3f, b3f, c4, c4s, a3f, a4f, a4f, e4f,

rest, b3f, b3f, c4, c4s, b3f, c4s, e4f, rest, c4, b3f, b3f, a3f,

rest, b3f, b3f, c4, c4s, a3f, a3f, e4f, e4f, e4f, f4, e4f,

c4s, e4f, f4, c4s, e4f, e4f, e4f, f4, e4f, a3f,

rest, b3f, c4, c4s, a3f, rest, e4f, f4, e4f

};


int song1_verse1_rhythmn[] =

{ 2, 1, 1, 1, 1, 2, 1, 1, 1, 5,

1, 1, 1, 1, 3, 1, 2, 1, 5,

1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3,

1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 4,

5, 1, 1, 1, 1, 1, 1, 1, 2, 2,

2, 1, 1, 1, 3, 1, 1, 1, 3

};


char* lyrics_verse1[] =

{ "Were ", "not", "new", "", "to ", "love ", "", "",

"You ", "know ", "the ", "rule ", "and ", "so ", "do ", "I",

"A ", "full ", "hard ", "ship", "", "what ", "I'm ", "tikn ", "", "of", "",

"You ", "woud", "not", "get ", "this ", "from ", "any ", "", "oter ", "", "guy",

"I ", "just ", "wana ", "", "tell ", "you ", "how ", "I'm ", "feel", "",

"Gota ", "", "make ", "you ", "get", "it", ""

};


// Parts 4 or 6 (Chorus)


int song1_chorus_melody[] =

{ b4f, b4f, a4f, a4f,

f5, f5, e5f, b4f, b4f, a4f, a4f, e5f, e5f, c5s, c5, b4f,

c5s, c5s, c5s, c5s,

c5s, e5f, c5, b4f, a4f, a4f, a4f, e5f, c5s,

b4f, b4f, a4f, a4f,

f5, f5, e5f, b4f, b4f, a4f, a4f, a5f, c5, c5s, c5, b4f,

c5s, c5s, c5s, c5s,

c5s, e5f, c5, b4f, a4f, rest, a4f, e5f, c5s, rest

};


int song1_chorus_rhythmn[] =

{ 1, 1, 1, 1,

3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,

1, 1, 1, 1,

3, 3, 3, 1, 2, 2, 2, 4, 8,

1, 1, 1, 1,

3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,

1, 1, 1, 1,

3, 3, 3, 1, 2, 2, 2, 4, 8, 4

};


char* lyrics_chorus[] =

{ "Nevr ", "", "gona ", "", "give ", "you ", "up",

"Nevr ", "", "gona ", "", "let ", "you ", "down", "", "",

"Nevr ", "", "gona ", "", "run ", "arud ", "", "", "", "and ", "dsrt ", "", "you",

"Nevr ", "", "gona ", "", "make ", "you ", "cry",

"Nevr ", "", "gona ", "", "say ", "goby ", "", "", "",

"Nevr ", "", "gona ", "", "tell ", "a ", "lie ", "", "", "and ", "hurt ", "you"

};


void setup()

{
  module.setupDisplay(true, 3);

  pinMode(piezo, OUTPUT);

  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);

  Serial.begin(9600);

  flag = true;

  a = 4;

  b = 0;

  c = 0;

}


void loop()

{

  // edit code here to define play conditions

  /*

  if (CONDITION 1) { // play

    flag = true;

  }

  else if (CONDITION2) { // pause

    flag = false;

  }

  */

  

  // play next step in song

  if (flag == true) {

    play();

  }

}


void play() {

  int notelength;

  if (a == 1 || a == 2) { // Intro

    // intro

    notelength = beatlength * song1_intro_rhythmn[b];

    if (song1_intro_melody[b] > 0) { // if not a rest, play note

    digitalWrite(led, HIGH);

    tone(piezo, song1_intro_melody[b], notelength);

    }


    b++;

    if (b >= sizeof(song1_intro_melody) / sizeof(int)) {

      a++;

      b = 0;

      c = 0;

    }

  } else if (a == 3 || a == 5) { // Verse 1

    // verse

    notelength = beatlength * 2 * song1_verse1_rhythmn[b];

    if (song1_verse1_melody[b] > 0) {

    digitalWrite(led, HIGH);

    displayString(lyrics_verse1[c]);

    tone(piezo, song1_verse1_melody[b], notelength);

    c++;

    }

    b++;

    if (b >= sizeof(song1_verse1_melody) / sizeof(int)) {

    a++;

    b = 0;

    c = 0;

    }

  } else if (a == 4 || a == 6) { //chorus

    // chorus

    notelength = beatlength * song1_chorus_rhythmn[b];

    if (song1_chorus_melody[b] > 0) {

      digitalWrite(led, HIGH);

      displayString(lyrics_chorus[c]);

      tone(piezo, song1_chorus_melody[b], notelength);

      c++;

    }


    b++;

    if (b >= sizeof(song1_chorus_melody) / sizeof(int)) {

      Serial.println("");

      a++;

      b = 0;

      c = 0;

    }

  }


  delay(notelength); // necessary because piezo is on independent timer

  noTone(piezo);

  digitalWrite(led, LOW);

  delay(notelength * beatseparationconstant); // create separation between notes

  if (a == 7) { // loop back around to beginning of song

    a = 1;

  }

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

