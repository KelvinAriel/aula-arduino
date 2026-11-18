const int pinPIR = 2;
const int pinBoton = 3;
const int ledVerde = 4;
const int ledRojo = 5;
const int pinBuzzer = 8;
bool alarmaArmada = false;
int estadoAnteriorBoton = HIGH;
void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(pinBoton, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int estadoBoton = digitalRead(pinBoton);
  int movimiento = digitalRead(pinPIR);
  // Cambiar el estado una sola vez al comenzar cada pulsación.
  if (estadoBoton == LOW && estadoAnteriorBoton == HIGH) {
    if (alarmaArmada == true) {
      alarmaArmada = false;
    } else {
      alarmaArmada = true;
    }
    delay(50);
  }
  estadoAnteriorBoton = estadoBoton;
  // Seleccionar uno de los tres estados del sistema.
  if (alarmaArmada == false) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, LOW);
    noTone(pinBuzzer);
    Serial.println("DESARMADA");
  } else if (movimiento == HIGH) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, HIGH);
    tone(pinBuzzer, 1000);
    Serial.println("ALERTA: movimiento detectado");
  } else {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledRojo, LOW);
    noTone(pinBuzzer);
    Serial.println("ARMADA: vigilancia activa");
  }
  delay(100);
}
