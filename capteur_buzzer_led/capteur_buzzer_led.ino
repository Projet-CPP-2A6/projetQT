#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
#define PIN_LED1 12
#define PIN_LED2 6


long duration;
int distance;
int safetyDistance;
char test = 'z';

Servo myservo;
int servoPin = 7;
int pos = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);

  Serial.begin(9600);
  myservo.attach(servoPin);
  myservo.write(0);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  safetyDistance = distance;
  if (Serial.available() > 0) {
    test = Serial.read();
  }

  if (test != 'a') {
     digitalWrite(PIN_LED2, HIGH);
    if (safetyDistance >= 5) {
      digitalWrite(PIN_LED2, LOW);
      digitalWrite(buzzer, HIGH);
      digitalWrite(PIN_LED1, HIGH);
      myservo.write(90);
      blinkLED();
      Serial.print('b');
      delay(5000);
    } else {
      digitalWrite(buzzer, LOW);
      myservo.write(0); 
       
    }
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(PIN_LED1, LOW);
    digitalWrite(PIN_LED2, HIGH);
    delay(5000);
    test = 'b';
  }
}

void blinkLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(PIN_LED1, HIGH);
    delay(500); 
    digitalWrite(PIN_LED1, LOW);
    delay(500); 
  }
}
