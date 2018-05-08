int latchPin = 2; // pinn 12 on 595
int dataPin = 3; // pin 14 on 595
int clockPin = 4; // pin 11 on 595

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // write 0
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 63);
  digitalWrite(latchPin,HIGH);
  delay(1000);

  // write 1
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 6);
  digitalWrite(latchPin,HIGH);
  delay(1000);

  // write 2
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 91);
  digitalWrite(latchPin,HIGH);
  delay(1000);  


  // write 3
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 79);
  digitalWrite(latchPin,HIGH);
  delay(1000);  


  // write 4
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 102);
  digitalWrite(latchPin,HIGH);
  delay(1000);    

  // write 5
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 109);
  digitalWrite(latchPin,HIGH);
  delay(1000);

  // write 6
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 125);
  digitalWrite(latchPin,HIGH);
  delay(1000);

  // write 7
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 7);
  digitalWrite(latchPin,HIGH);
  delay(1000);  


  // write 8
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 127);
  digitalWrite(latchPin,HIGH);
  delay(1000);  


  // write 9
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 103);
  //shiftOut(dataPin, clockPin, MSBFIRST, 111);
  digitalWrite(latchPin,HIGH);
  delay(1000);    

  // write a
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 95);
  digitalWrite(latchPin,HIGH);
  delay(1000);    

  // write b
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 124);
  digitalWrite(latchPin,HIGH);
  delay(1000);

  // write c
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 57);
  digitalWrite(latchPin,HIGH);
  delay(1000);        

  // write d
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 94);
  digitalWrite(latchPin,HIGH);
  delay(1000);    

  // write e
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 123);
  digitalWrite(latchPin,HIGH);
  delay(1000);

  // write f
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 113);
  digitalWrite(latchPin,HIGH);
  delay(1000);

 
}

