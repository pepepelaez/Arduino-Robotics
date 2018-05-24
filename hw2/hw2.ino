//sketch for the three photo resistors

void setup () {
  Serial.begin(19200);
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  pinMode(A4, INPUT);
}

void loop() {
  int value;
  int value2;
  int value3;

  value = analogRead(A0);
  Serial.print(value);
  Serial.print(" ");
  value2 = analogRead(A2);
  Serial.print(value2);
  Serial.print(" ");
  value3 = analogRead(A4);
  Serial.println(value3);
}

//sketch piezo buzzer controled with analogRead()

void setup () {
  Serial.begin(19200);
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  int value;

  value = analogRead(A0);
  Serial.print(value);
  tone(2, value);
}
