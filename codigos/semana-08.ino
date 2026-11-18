// PIR: VCC a 5V, GND a GND, OUT a D2.
const int pinPIR = 2, pinLED = 4, buzzer = 8;
void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(pinLED, OUTPUT); pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int movimiento = digitalRead(pinPIR);
  digitalWrite(pinLED, movimiento);
  if (movimiento == HIGH) tone(buzzer, 1000);
  else noTone(buzzer);
  Serial.println(movimiento == HIGH ? "MOVIMIENTO" : "SIN MOVIMIENTO");
  delay(100);
}
