int led = 13;
int AIN1 = 7;
int AIN2 = 8;
int BIN1 = 4;
int BIN2 = 12;

void setup() {
  Serial.begin(19200);
  pinMode (led, OUTPUT);
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

void loop() {
  char c = Serial.read();

  if (c == 'w') {
    forward();
    Serial.println("I'm moving forward");
  }

  if (c == 's' ) {
    backward();
    Serial.println("I'm moving backward");
  }

  if (c == 't' ) {
    stops();
    Serial.println("I stopped");
  }

  if (c == 'a' ) {
    left();
    delay(2000);
    stops();
    Serial.println("I rotated left for 2 seconds");
  }

  if (c == 'd') {
    right();
    delay(2000);
    stops();
    Serial.println("I rotated right for 2 seconds");
  }
}
