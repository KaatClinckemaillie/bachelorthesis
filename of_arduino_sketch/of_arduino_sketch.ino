#include <FastLED.h>

#define NUM_LEDS 30
#define LED_PIN 10
#define BRIGHTNESS  50
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];



#define echoPin1 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 4
#define trigPin2 5
#define echoPin3 6
#define trigPin3 7
#define echoPin4 8
#define trigPin4 9

int relay1 = 14;
int relay2 = 15;

// defines variables
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement
long duration2;
int distance2;
long duration3;
int distance3;
long duration4;
int distance4;



int score;

String number = "";

int level;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  score = 0;
  level = 1;

}
void loop() {
  long duration1, distance1;

  char inByte = 0;

  ////if(Serial.available() > 0){
    // get incoming byte:
    inByte = Serial.read();

    // level up 1->2
    if(inByte == 'a'){
      level = 2;
    }

    // level up 2->3
    if(inByte == 'b') {
      level = 3;
    }

    // reset
    if(inByte == 'c') {
      level = 1;
      score = 0;
      for(int i=0; i< 30; i++){
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    }

    // score 
    if(inByte == 'd'){
      leds[score] = CRGB::Green;
      score ++;
      FastLED.show();
    }

    // mismatch
    if(inByte == 'e'){
      leds[score] = CRGB::Red;   
      score ++; 
      FastLED.show();
    }

    if(level == 2){
      digitalWrite(relay1, LOW);
    }

    if(level == 3){
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
    }

    if(level == 1){
      digitalWrite(relay2, HIGH);
      digitalWrite(relay1, HIGH);
    }

    digitalWrite(trigPin1, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = (duration1/2) / 29.1;
    
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

    
    long duration2, distance2;
    digitalWrite(trigPin2, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    distance2= (duration2/2) / 29.1;

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

    long duration3, distance3;
    digitalWrite(trigPin3, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin3, LOW);
    duration3 = pulseIn(echoPin3, HIGH);
    distance3 = (duration3/2) / 29.1;

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

    long duration4, distance4;
    digitalWrite(trigPin4, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin4, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin4, LOW);
    duration4 = pulseIn(echoPin4, HIGH);
    distance4 = (duration4/2) / 29.1;

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
    Serial.flush(); 

//}  
}
