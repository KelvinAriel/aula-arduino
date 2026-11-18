const int pinLDR = A0;
const int pinLED = 9;
int nivelLuz = 0;
int brilloLED = 0;
void setup() {
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // Leer el nivel de iluminación.
  nivelLuz = analogRead(pinLDR);
  // Convertir e invertir los intervalos.
  brilloLED = map(nivelLuz, 0, 1023, 255, 0);
  brilloLED = constrain(brilloLED, 0, 255);
  // Aplicar el brillo mediante PWM.
  analogWrite(pinLED, brilloLED);
  // Mostrar datos para verificar.
  Serial.print("LDR: ");
  Serial.print(nivelLuz);
  Serial.print(" | PWM: ");
  Serial.print(brilloLED);
  Serial.print(" | Estado: ");
  if (brilloLED > 170) {
    Serial.println("iluminacion alta");
  } else if (brilloLED > 80) {
    Serial.println("iluminacion media");
  } else {
    Serial.println("iluminacion baja");
  }
  delay(300);
}
