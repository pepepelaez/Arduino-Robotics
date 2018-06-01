//sketch to control robot with the IR-remote
#include <IRremote.h>

int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
int led = 13;
int AIN1 = 7;
int AIN2 = 8;
int BIN1 = 2;
int BIN2 = 12;

void setup() {
  Serial.begin(19200);
  irrecv.enableIRIn();
  pinMode(led, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void forward() {
 digitalWrite(led, HIGH);
 digitalWrite(AIN1, HIGH);
 digitalWrite(AIN2, LOW);
 digitalWrite(BIN1, HIGH);
 digitalWrite(BIN2, LOW);
}

void backward() {
 digitalWrite(led, HIGH);
 digitalWrite(AIN1, LOW);
 digitalWrite(AIN2, HIGH);
 digitalWrite(BIN1, LOW);
 digitalWrite(BIN2, HIGH);
}

void stops() {
 digitalWrite(led, LOW);
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

void loop () {
  if (irrecv.decode(&results)) {
    if (results.value == 0xC8155AB1) {
      forward();
    }
    else if (results.value == 0x55F2B93) {
      backward();
    }
    else if (results.value == 0x9C2A936C) {
      left();
      delay(250);
      stops();
    }
    else if (results.value == 0x969AE844) {
      right();
      delay(250);
      stops();
    }
    else if (results.value == 0x4AAFAC67) {
      stops();
    }
    irrecv.resume();
  }
  
}


//sketch for the robot to react to light
int AIN1 = 7;
int AIN2 = 8;
int BIN1 = 2;
int BIN2 = 12;


void setup () {
  Serial.begin(19200);
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
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

void stops() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void loop() {
  int value;
  int value2;

  value = analogRead(A0);
  Serial.print(value);
  Serial.print(" ");
  value2 = analogRead(A2);
  Serial.println(value2);

  if ((value > 120) || (value2 > 120)) {
    if (value > value2) {
      right();
      delay(250);
      stops();
    }
    else if (value2 > value) {
      left();
      delay(250);
      stops();
    }
  }
}
