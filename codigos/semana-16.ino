const int pinTrig = 9;
const int pinEcho = 10;
const int ledVerde = 4;
const int ledAmarillo = 5;
const int ledRojo = 6;
const int buzzer = 8;
void activarLuces(int verde, int amarillo, int rojo);
void setup() {
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  long duracion = pulseIn(pinEcho, HIGH, 30000);
  float distancia;
  if (duracion == 0) {
    activarLuces(LOW, LOW, LOW);
    tone(buzzer, 300);
    Serial.println("ERROR: sin eco valido");
    delay(300);
    return;
  }
  distancia = duracion * 0.0343 / 2.0;
  if (distancia <= 30.0) {
    activarLuces(LOW, LOW, HIGH);
    tone(buzzer, 1200);
    Serial.print("PELIGRO");
    delay(150);
    noTone(buzzer);
    delay(150);
  } else if (distancia <= 100.0) {
    activarLuces(LOW, HIGH, LOW);
    tone(buzzer, 700);
    Serial.print("PRECAUCION");
    delay(100);
    noTone(buzzer);
    delay(500);
  } else {
    activarLuces(HIGH, LOW, LOW);
    noTone(buzzer);
    Serial.print("ZONA SEGURA");
    delay(300);
  }
  Serial.print(" | Distancia: ");
  Serial.print(distancia, 1);
  Serial.println(" cm");
}
void activarLuces(int verde, int amarillo, int rojo) {
  digitalWrite(ledVerde, verde);
  digitalWrite(ledAmarillo, amarillo);
  digitalWrite(ledRojo, rojo);
}
