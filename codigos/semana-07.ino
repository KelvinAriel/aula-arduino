// Semaforo de proximidad: el error no se interpreta como camino libre.
const int pinTrig = 9, pinEcho = 10;
const int ledVerde = 4, ledAmarillo = 5, ledRojo = 6;

float medirDistancia() {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  unsigned long duracion = pulseIn(pinEcho, HIGH, 30000);
  if (duracion == 0) return -1.0;
  return duracion * 0.0343 / 2.0;
}
void setup() {
  pinMode(pinTrig, OUTPUT); pinMode(pinEcho, INPUT);
  pinMode(ledVerde, OUTPUT); pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  float distancia = medirDistancia();
  bool valida = distancia >= 0;
  digitalWrite(ledRojo, valida && distancia <= 30 ? HIGH : LOW);
  digitalWrite(ledAmarillo, valida && distancia > 30 && distancia <= 100 ? HIGH : LOW);
  digitalWrite(ledVerde, valida && distancia > 100 ? HIGH : LOW);
  if (valida) {
    Serial.print("Distancia (cm): ");
    Serial.println(distancia, 1);
  } else {
    Serial.println("ERROR: sin eco valido");
  }
  delay(300);
}
