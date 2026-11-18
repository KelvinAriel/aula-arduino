// Potenciometro: extremos a 5V y GND, cursor a A0.
const int pinPot = A0, pinLED = 9;
void setup() {
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int lectura = analogRead(pinPot);
  int brillo = map(lectura, 0, 1023, 0, 255);
  analogWrite(pinLED, brillo);
  Serial.print("Entrada: "); Serial.print(lectura);
  Serial.print(" | PWM: "); Serial.println(brillo);
  delay(100);
}
