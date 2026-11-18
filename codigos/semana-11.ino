#include <Servo.h>
Servo puerta;
const int pinPIR = 2;
const int ledVerde = 3;
const int ledRojo = 4;
const int pinMotor = 5;
const int pinBuzzer = 7;
const int pinServo = 9;
const int pinTMP36 = A0;
int movimiento = LOW;
int lecturaTemperatura = 0;
int pwmMotor = 0;
float voltaje = 0.0;
float temperatura = 0.0;
void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(pinMotor, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  puerta.attach(pinServo);
  puerta.write(0);
  Serial.begin(9600);
}
void loop() {
  // ENTRADAS
  movimiento = digitalRead(pinPIR);
  lecturaTemperatura = analogRead(pinTMP36);
  voltaje = lecturaTemperatura * (5.0 / 1023.0);
  temperatura = (voltaje - 0.5) * 100.0;
  // SUBSISTEMA DE SEGURIDAD
  if (movimiento == HIGH) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, HIGH);
    tone(pinBuzzer, 1000);
    puerta.write(90);
  } else {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledRojo, LOW);
    noTone(pinBuzzer);
    puerta.write(0);
  }
  // SUBSISTEMA AMBIENTAL
  if (temperatura < 25.0) {
    pwmMotor = 0;
  } else if (temperatura <= 30.0) {
    pwmMotor = 150;
  } else {
    pwmMotor = 255;
  }
  analogWrite(pinMotor, pwmMotor);
  // INFORMACIÓN PARA LAS PRUEBAS
  Serial.print("PIR: ");
  Serial.print(movimiento);
  Serial.print(" | Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" °C | PWM motor: ");
  Serial.println(pwmMotor);
  delay(500);
}
