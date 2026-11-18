// Aula Arduino - seguridad y monitoreo ambiental
// RGB de catodo comun. Resistencias independientes por canal.
const int pinPIR = 4, pinTMP36 = A0;
const int ledVerde = 2, ledRojo = 7, buzzer = 8;
const int rgbRojo = 5, rgbVerde = 6, rgbAzul = 9;
unsigned long ultimoCambio = 0;
bool fase = false;

void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(ledVerde, OUTPUT); pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(rgbRojo, OUTPUT); pinMode(rgbVerde, OUTPUT);
  pinMode(rgbAzul, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool movimiento = digitalRead(pinPIR) == HIGH;
  digitalWrite(ledRojo, movimiento ? HIGH : LOW);
  digitalWrite(ledVerde, movimiento ? LOW : HIGH);
  if (movimiento) tone(buzzer, 1000);
  else noTone(buzzer);

  float voltaje = analogRead(pinTMP36) * (5.0 / 1023.0);
  float temperatura = (voltaje - 0.5) * 100.0;

  // Alternar sin bloquear las lecturas del PIR.
  unsigned long ahora = millis();
  if (ahora - ultimoCambio >= 500) {
    ultimoCambio = ahora;
    fase = !fase;
    Serial.print("Temperatura: ");
    Serial.println(temperatura, 1);
  }
  if (temperatura >= 30.0) {
    analogWrite(rgbRojo, 255);
    analogWrite(rgbVerde, fase ? 100 : 0);
    analogWrite(rgbAzul, 0);
  } else {
    analogWrite(rgbRojo, 0);
    analogWrite(rgbVerde, fase ? 255 : 0);
    analogWrite(rgbAzul, fase ? 0 : 255);
  }
}
