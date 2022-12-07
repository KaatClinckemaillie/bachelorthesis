// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define echoPin1 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 4
#define trigPin2 5
#define echoPin3 6
#define trigPin3 7
#define echoPin4 8
#define trigPin4 9

// defines variables
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement
long duration2;
int distance2;
long duration3;
int distance3;
long duration4;
int distance4;

int relay1 = 14;
int relay2 = 15;


String number = "";


int level = 1;








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

  
}
void loop() {
  long duration1, distance1;

  char inByte = 0;

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

  //if(Serial.available() > 0){
    // get incoming byte:
    inByte = Serial.read();

    // light on => Level 2
    if(inByte == 'a'){
      level = 2;
      //digitalWrite(relay1, LOW);
    }

    if(inByte == 'b') {
      digitalWrite(relay2, LOW);
    }

    if(level == 2){
      digitalWrite(relay1, LOW);
    }

    digitalWrite(trigPin1, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = (duration1/2) / 29.1;
    
    

    if (distance1 >= 500 || distance1 <= 0){
      //Serial.print("99");
      //Serial.print(",");
      number += "00";
      
    }
    else {
      //Serial.print(distance1); 
      //Serial.print(",");  
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
    //Serial.println(String("43452"));
    Serial.flush(); 

//}
  
  
  
  

/*  long duration3, distance3;
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3= (duration3/2) / 29.1;

   if (distance3 >= 500 || distance3 <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print("Sensor3  ");
    Serial.print(distance3);
    Serial.println("cm");
  }
  delay(1000); */
  
}
