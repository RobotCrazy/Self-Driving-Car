int motorOutPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorOutPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // for(int i = 0; i < 255; i++) {
  //   analogWrite(motorOutPin, i);
  //   delay(20);
  // }
    analogWrite(motorOutPin, 128);
    // digitalWrite(motorOutPin, 0);
}
