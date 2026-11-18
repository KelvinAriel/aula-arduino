#include <Servo.h>
const int pinLdr = A0;
const int pinTmp = A1;
const int pinPir = 2;
const int pinLed = 3;
const int pinMotor = 5;
const int pinServo = 9;
Servo puerta;
void setup() {
  pinMode(pinPir, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinMotor, OUTPUT);
  puerta.attach(pinServo);
  puerta.write(0);
  Serial.begin(9600);
}
void loop() {
  // Subsistema de iluminación
  int luz = analogRead(pinLdr);
  int brilloLed = map(luz, 0, 1023, 255, 0);
  brilloLed = constrain(brilloLed, 0, 255);
  analogWrite(pinLed, brilloLed);
  // Subsistema de ventilación
  int lecturaTmp = analogRead(pinTmp);
  float voltaje = lecturaTmp * (5.0 / 1023.0);
  float temperatura = (voltaje - 0.5) * 100.0;
  int velocidadMotor;
  if (temperatura < 25.0) {
    velocidadMotor = 0;
  } else if (temperatura <= 30.0) {
    velocidadMotor = 150;
  } else {
    velocidadMotor = 255;
  }
  analogWrite(pinMotor, velocidadMotor);
  // Subsistema de acceso
  int presencia = digitalRead(pinPir);
  if (presencia == HIGH) {
    puerta.write(90);
  } else {
    puerta.write(0);
  }
  // Información para comprobar y depurar
  Serial.print("Luz: ");
  Serial.print(luz);
  Serial.print(" | Brillo: ");
  Serial.print(brilloLed);
  Serial.print(" | Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" C | Motor: ");
  Serial.print(velocidadMotor);
  Serial.print(" | Presencia: ");
  Serial.println(presencia);
  delay(300);
}
