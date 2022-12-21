#include "Keyboard.h"
#include <FastLED.h>


#define NUM_LEDS 30
#define LED_PIN 10
#define BRIGHTNESS  50
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

 //HCSR04 echo pins
const int echoPin1 = 5;
const int echoPin2 = 6;
const int echoPin3 = 7;
const int echoPin4 = 8;

//Pin connected to ST_CP of 74HC595
const int latchPin = 4;
//Pin connected to DS of 74HC595
const int dataPin = 2;
//Pin connected to SH_CP of 74HC595
const int clockPin = 3;

byte triggerPin1On = B00000001;
byte triggerPin2On = B00000010;
byte triggerPin3On = B00000100;
byte triggerPin4On = B00001000;

byte ledPin1On = B10000000;
byte ledPin2On = B01000000;
byte ledPin3On = B00100000;
byte ledPin4On = B00010000;

// example: set triggerPin1 to on qnd ledPin1 to on
// byte result = 0 | triggerPin1On | ledPin1On;

const int relay1 = 14;
const int relay2 = 15;
const int relay3 = 16;

byte ledsLevel = 0xe0 ;// 11100000;
byte skip =  0x10 ;//00010000;

byte triggerPin1;
byte triggerPin2;
byte triggerPin3;
byte triggerPin4;
byte zero;

String game_state = ""; // start introVideo introGame countdown game levelUp end outro score
String number = "";


int level;
int score;



void setup() {
  Serial.begin (9600);

  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);  
  pinMode(echoPin4, INPUT);


  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  Keyboard.begin();

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  score = 0;
  level = 0;

  for(int i=0; i< 30; i++){
      leds[i] = CRGB::Black;
  }


  game_state = "start" ;  
  
}


void loop() {

  char inByte = 0;
  int valueButton = analogRead(A0);


  if(game_state == "start"){
    //registerWrite(ledsLevel);
    triggerPin1 = 0 | triggerPin1On | ledPin1On | ledPin2On | ledPin3On;
    triggerPin2 = 0 | triggerPin2On | ledPin1On | ledPin2On | ledPin3On;
    triggerPin3 = 0 | triggerPin3On | ledPin1On | ledPin2On | ledPin3On;
    triggerPin4 = 0 | triggerPin4On | ledPin1On | ledPin2On | ledPin3On;
    zero = 0 | ledPin1On | ledPin2On | ledPin3On;

    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    

  }else if(game_state == "introVideo" || game_state == "introGame" || game_state == "score"){
    //registerWrite(skip);
   /* triggerPin1 = 0x11; 
    triggerPin2 = 0x12;
    triggerPin3 = 0x14;
    triggerPin4 = 0x18;
    zero = 0x10;*/

    triggerPin1 = 0 | triggerPin1On | ledPin4On;
    triggerPin2 = 0 | triggerPin2On | ledPin4On;
    triggerPin3 = 0 | triggerPin3On | ledPin4On;
    triggerPin4 = 0 | triggerPin4On | ledPin4On;
    zero = 0 | ledPin4On;

  
  }else if(game_state == "countdown" || game_state == "game" || game_state == "levelUp" ){



    triggerPin1 = triggerPin1On;
    triggerPin2 = triggerPin2On;
    triggerPin3 = triggerPin3On;
    triggerPin4 = triggerPin4On;
    zero = 0;
  }

  if(game_state == "introGame"){
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
  }

  // get incoming byte:
  inByte = Serial.read();

    // light on => Level 2
  if(inByte == 'a'){
    /*if(level < 3){
      level ++;
    }*/
    
  }
  
  if(inByte == 'b') {
    //digitalWrite(relay2, LOW);

    game_state = "introVideo";
  }

  if(inByte == 'c'){
    game_state = "introGame";
  }

  if(inByte == 'd'){
    game_state = "game";
  }

  // score
  if(inByte == 'e'){
    leds[score] = CRGB::Green;
    score ++;
    FastLED.show();
  }

  // miss
  if(inByte == 'f'){
    leds[score] = CRGB::Red;   
    score ++; 
    FastLED.show();
  }

  if(inByte == 'g'){
    game_state = "score";
  }


  //reset
  if(inByte == 'r'){
    level = 0;
    score = 0;

    for(int i=0; i< 30; i++){
      leds[i] = CRGB::Black;
    }
    FastLED.show();

    game_state = "start" ; 
  }

  if(score >= 10){
    digitalWrite(relay1, LOW);
  }

  if(score >= 20){
    digitalWrite(relay2, LOW);
  }

  if(score == 30){
    digitalWrite(relay3, LOW);
  }


  

  if (valueButton >= 700 && valueButton < 800) {
    //button 1: hard
    Keyboard.write('h');
  } else if (valueButton >= 600 && valueButton < 700) {
    //button 2: medium
    Keyboard.write('i');
  } else if (valueButton > 480 && valueButton < 600) {
    //button 3: easy
    Keyboard.write('e');
  } else if (valueButton < 480) {
    //button 4: skip
    Keyboard.write('s');

  }



  if(level == 2){
    digitalWrite(relay1, LOW);
  }

  
  long  distance1;
  distance1 = get74HC595DistanceHCSSR04(triggerPin1,echoPin1, zero);
  if (distance1 >= 500 || distance1 <= 0){
      number += "00";     
    } else { 
      if(distance1 < 10) {
        number += "0";
        number += String(distance1);
      }else {
        number += String(distance1);
      }
    }


  long  distance2;
  distance2 = get74HC595DistanceHCSSR04(triggerPin2,echoPin2, zero);
  if (distance2 >= 500 || distance2 <= 0){
      //Serial.println("99");
      distance2 = 0;
    }
    else {
      if(distance2 < 10) {
        number += "0";
        number += String(distance2);
      }else {
        number += String(distance2);

      }
    }


  long distance3;
  distance3 = get74HC595DistanceHCSSR04(triggerPin3,echoPin3, zero);
  if (distance3 >= 500 || distance3 <= 0){
      //Serial.println("99");
      distance3 = 0;
    }
    else {
      if(distance3 < 10) {
        number += "0";
        number += String(distance3);
      }else {
        number += String(distance3);

      }
    }

  long distance4;
  distance4 = get74HC595DistanceHCSSR04(triggerPin4,echoPin4, zero);
  if (distance4 >= 500 || distance4 <= 0){
      //Serial.println("99");
      distance4 = 0;
    }
    else {
      if(distance4 < 10) {
        number += "0";
        number += String(distance4);
      }else {
        number += String(distance4);
      }
    }


  Serial.println(number);
  number = "";
  //Serial.println(String("43452"));
  Serial.flush(); 
}

void registerWrite(int funcLeds) {
  digitalWrite(latchPin, LOW);//stop anything changine while writing
  shiftOut(dataPin, clockPin, MSBFIRST, funcLeds);
  digitalWrite(latchPin, HIGH);//allow pins to change
}

int get74HC595DistanceHCSSR04(int funcTriggerPin, int funcEchoPin, int zero){

  unsigned long duration;  //time taken for echo
  int myDistance;

  digitalWrite(latchPin, LOW);//stop anything changine while writing
  shiftOut(dataPin, clockPin, MSBFIRST, zero);//send all zeros
  digitalWrite(latchPin, HIGH);//allow pins to change
  
  //A tiny delay 2 millionths of a second
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  //same as turing the LED on in the blink sketch
  //digitalWrite(funcTriggerPin, HIGH);
  digitalWrite(latchPin, LOW);//stop anything changine while writing
  shiftOut(dataPin, clockPin, MSBFIRST, funcTriggerPin);//pin to go HIGH
  digitalWrite(latchPin, HIGH);//allow pins to change
  
  
  //pin stays HIGH (5v) for 10 microseconds to trigger a pulse
  delayMicroseconds(10);
  
  //Pin taken LOW (0v) after pulse triggered ready for next pulse
  //digitalWrite(funcTriggerPin, LOW);
  digitalWrite(latchPin, LOW);//stop anything changine while writing
  shiftOut(dataPin, clockPin, MSBFIRST, zero);//send all zeros
  digitalWrite(latchPin, HIGH);//allow pins to change

  duration = pulseIn(funcEchoPin, HIGH);

   myDistance = (duration/2) / 29.1;
   return myDistance;
}

  
  
  
  
