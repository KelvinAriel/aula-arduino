// TMP36: revisar las etiquetas de alimentacion, salida y GND.
const int pinTMP36 = A0, pinLED = 4, buzzer = 8;
const float umbral = 30.0;
void setup() {
  pinMode(pinLED, OUTPUT); pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int lectura = analogRead(pinTMP36);
  float voltaje = lectura * (5.0 / 1023.0);
  float temperatura = (voltaje - 0.5) * 100.0;
  bool alerta = temperatura >= umbral;
  digitalWrite(pinLED, alerta ? HIGH : LOW);
  if (alerta) tone(buzzer, 1000);
  else noTone(buzzer);
  Serial.print("Temperatura (C): ");
  Serial.println(temperatura, 1);
  delay(300);
}
