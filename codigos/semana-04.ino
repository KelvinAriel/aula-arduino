// Divisor: 5V -> LDR -> nodo A0 -> 10 kohm -> GND
const int pinLDR = A0, pinLED = 9;
const int umbral = 500; // Ajustar tras observar luz y oscuridad.
void setup() {
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int luz = analogRead(pinLDR);
  digitalWrite(pinLED, luz < umbral ? HIGH : LOW);
  Serial.print("LDR: "); Serial.println(luz);
  delay(200);
}
