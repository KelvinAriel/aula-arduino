const int pinTMP36 = A0;
const int pinMotor = 5;

int lectura = 0;
int pwmMotor = 0;
float voltaje = 0.0;
float temperatura = 0.0;

void setup() {
  pinMode(pinMotor, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Leer el sensor y convertir la lectura a grados Celsius.
  lectura = analogRead(pinTMP36);
  voltaje = lectura * (5.0 / 1023.0);
  temperatura = (voltaje - 0.5) * 100.0;

  // Seleccionar la velocidad según la temperatura.
  if (temperatura < 25.0) {
    pwmMotor = 0;
  } else if (temperatura <= 30.0) {
    pwmMotor = 150;
  } else {
    pwmMotor = 255;
  }

  // Aplicar el valor PWM al transistor que controla el motor.
  analogWrite(pinMotor, pwmMotor);

  // Mostrar información para comprobar el sistema.
  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" °C | Estado: ");

  if (pwmMotor == 0) {
    Serial.print("apagado");
  } else if (pwmMotor == 150) {
    Serial.print("velocidad media");
  } else {
    Serial.print("velocidad alta");
  }

  Serial.print(" | PWM: ");
  Serial.println(pwmMotor);
  delay(500);
}
