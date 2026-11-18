#include <Servo.h>
Servo compuerta;
const int pinTMP36 = A0;
const int ledVerde = 3;
const int ledRojo = 4;
const int pinMotor = 5;
const int pinServo = 9;
void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(pinMotor, OUTPUT);
  compuerta.attach(pinServo);
  compuerta.write(0);
  Serial.begin(9600);
}
void loop() {
  int lectura = analogRead(pinTMP36);
  float voltaje = lectura * (5.0 / 1023.0);
  float temperatura = (voltaje - 0.5) * 100.0;
  int pwmMotor;
  int anguloCompuerta;
  if (temperatura < 24.0) {
    pwmMotor = 0;
    anguloCompuerta = 0;
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledRojo, LOW);
    Serial.print("NORMAL");
  } else if (temperatura <= 30.0) {
    pwmMotor = 150;
    anguloCompuerta = 45;
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, LOW);
    Serial.print("VENTILACION MEDIA");
  } else {
    pwmMotor = 255;
    anguloCompuerta = 90;
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, HIGH);
    Serial.print("VENTILACION ALTA");
  }
  analogWrite(pinMotor, pwmMotor);
  compuerta.write(anguloCompuerta);
  Serial.print(" | Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" °C | PWM: ");
  Serial.print(pwmMotor);
  Serial.print(" | Angulo: ");
  Serial.println(anguloCompuerta);
  delay(500);
}
