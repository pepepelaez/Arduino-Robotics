//servo controlled by IR-remote
#include <Servo.h>
#include <IRremote.h>

int servoPin = 6;
Servo servo;
int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  servo.attach(servoPin);
  Serial.begin(19200);
  irrecv.enableIRIn();
  
}


void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == 0xC8155AB1) {
      servo.write(90);
    }
    else if (results.value == 0x9C2A936C) {
      servo.write(180);
    }
    else if (results.value == 0x969AE844) {
      servo.write(0);
    }
    irrecv.resume();
  }
 
}



//sketch for robot with mounted sensor moving with servo to collect data
#include <Servo.h>

int servoPin = 6;
Servo servo;
int triggerPin = 8;
int echoPin = 7;
int AIN1 = 11;
int AIN2 = 2;
int BIN1 = 4;
int BIN2 = 12;

void setup() {
  Serial.begin(19200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);
  servo.attach(servoPin);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void forward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void backward() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void stops() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void right() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void left() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

float ping() {
  unsigned long maxTime = 20000;
  unsigned long us;
  float inches;

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  us = pulseIn(echoPin, HIGH, maxTime);
  if (us == 0) {
    us = maxTime;
  }

  inches = us * 0.013504 / 2;
  return inches;


}

void loop() {
  // Servo 90
  Serial.println("Ultrasonic to 90");
  servo.write(90);
  delay(1000);
  //Read 1
  float read1 = ping();

  // Servo 180
  Serial.println("Ultrasonic to 180");
  servo.write(180);
  delay(1000);
  // Read 2
  float read2 = ping();

  //Servo 0
  Serial.println("Ultrasonic to 0");
  servo.write(0);
  delay(1000);
  //Read 3
  float read3 = ping();
  //Servo 90
  Serial.println("Ultrasonic to 90");
  servo.write(90);

  //If Read 1 has the most space move forward for half a second
  if ((read1 >= read2) && (read1 >= read3)) {
    Serial.println("Moving forward half second");
    forward();
    delay(500);
    stops();
  }
  //If Read 2 has the most space move to right for 250ms
  if ((read2 >= read1) && (read2 >= read3)) {
    Serial.println("Moving left");
    right();
    delay(250);
    stops();
  }
  //If Read 3 has the most space move to left for 250ms
  if ((read3 >= read1) && (read3 >= read2)) {
    Serial.println("Moving right");
    left();
    delay(250);
    stops();
  }



}
