#define SENSOR_PIN 8
#define LED_PIN 13

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = digitalRead(SENSOR_PIN);
  if(sensorVal == HIGH){
    digitalWrite(LED_PIN, HIGH);
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }
}
