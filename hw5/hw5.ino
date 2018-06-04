//sketch for IR Remote with speed change

#include <IRremote.h>

int motorPWM = 6;
int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;
int AIN1 = 11;
int AIN2 = 2;
int BIN1 = 4;
int BIN2 = 12;
int fast;

void setup() {
  Serial.begin(19200);
  irrecv.enableIRIn();
  pinMode(motorPWM, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void forward(int howFast) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  analogWrite(motorPWM, howFast);
}

void backward(int howFast) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(motorPWM, howFast);
}

void stops() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void right(int howFast) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(motorPWM, howFast);
}

void left(int howFast) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(motorPWM, howFast);
}

void loop () {

  if (irrecv.decode(&results)) {
    if (results.value == 0xE6D07133) {
      fast = 64;
    }
    else if (results.value == 0x9A6F0576) {
      fast = 128;
    }
    else if (results.value == 0x9B72C267) {
      fast = 255;
    }
    else if (results.value == 0xC8155AB1) {
      forward(fast);
    }
    else if (results.value == 0x55F2B93) {
      backward(fast);
    }
    else if (results.value == 0x9C2A936C) {
      left(255);
      delay(250);
      stops();
    }
    else if (results.value == 0x969AE844) {
      right(255);
      delay(250);
      stops();
    }
    else if (results.value == 0x4AAFAC67) {
      stops();
    }

    irrecv.resume();
  }

}

//sketch for robot to wander around avoiding obstacles
int triggerPin = 8;
int echoPin = 7;
int AIN1 = 11;
int AIN2 = 2;
int BIN1 = 4;
int BIN2 = 12;

void setup () {
  Serial.begin(19200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);
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

void loop() {
  float inches = ping();
  Serial.println(inches);
  delay(60);
  if (inches > 7.00) {
    forward();
  }
  else if (inches > 1)  {
    stops();
    right();
    delay(250);
  }
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


