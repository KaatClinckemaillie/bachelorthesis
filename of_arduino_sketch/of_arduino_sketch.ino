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
//#define echoPin3 6
//#define trigPin3 7

// defines variables
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement
long duration2;
int distance2;

int heightTable = 40;
int heightGame = 760;

int testnumber;

String number = "";

int positions[8];

//long duration3;
//int distance3;





void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  //pinMode(trigPin3, OUTPUT);
  //pinMode(echoPin3, INPUT);

  
}
void loop() {
  long duration1, distance1;

  char inByte = 0;

  //if(Serial.available() > 0){
    // get incoming byte:
    inByte = Serial.read();

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
