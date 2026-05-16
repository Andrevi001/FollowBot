#include <Arduino.h>

//Setup motori
// singolo standby per le due TB6612FNG
const int8_t STBY = 18;

//singolo valore PWM
const int8_t PWM = 5;

// canali A e B delle ruote anteriori
const int8_t AAIN1 = 23; //arancione
const int8_t AAIN2 = 22; //giallo

const int8_t ABIN1 = 19; //bianco
const int8_t ABIN2 = 21; //verde

//canali A e B delle ruote posteriori
const int8_t PAIN1 = 32; //nero
const int8_t PAIN2 = 33; //bianco

const int8_t PBIN1 = 14; //marroncino
const int8_t PBIN2 = 13; //viola

void Forward() {
  //ruota posteriore sinistra
  digitalWrite(PAIN1, HIGH);
  digitalWrite(PAIN2, LOW);

  //ruota posteriore destra
  digitalWrite(PBIN1, HIGH);
  digitalWrite(PBIN2, LOW);

  //ruota anteriore destra
  digitalWrite(ABIN1, HIGH);
  digitalWrite(ABIN2, LOW);

  //ruota anteriore sinistra
  digitalWrite(AAIN1, HIGH);
  digitalWrite(AAIN2, LOW);
}

void Backward() {
  //ruota anteriore sinistra
  digitalWrite(AAIN1, LOW);
  digitalWrite(AAIN2, HIGH);

  //ruota anteriore destra
  digitalWrite(ABIN1, LOW);
  digitalWrite(ABIN2, HIGH);

  //ruota posteriore sinistra
  digitalWrite(PAIN1, LOW);
  digitalWrite(PAIN2, HIGH);

  //ruota posteriore destra
  digitalWrite(PBIN1, LOW);
  digitalWrite(PBIN2, HIGH);
}

void DxRotation() {
  //ruota anteriore sinistra
  digitalWrite(AAIN1, LOW);
  digitalWrite(AAIN2, HIGH);

  //ruota anteriore destra
  digitalWrite(ABIN1, HIGH);
  digitalWrite(ABIN2, LOW);

  //ruota posteriore sinistra
  digitalWrite(PAIN1, LOW);
  digitalWrite(PAIN2, HIGH);

  //ruota posteriore destra
  digitalWrite(PBIN1, HIGH);
  digitalWrite(PBIN2, LOW);
}

void SxRotation() {
  //ruota anteriore sinistra
  digitalWrite(AAIN1, HIGH);
  digitalWrite(AAIN2, LOW);

  //ruota anteriore destra
  digitalWrite(ABIN1, LOW);
  digitalWrite(ABIN2, HIGH);

  //ruota posteriore sinistra
  digitalWrite(PAIN1, HIGH);
  digitalWrite(PAIN2, LOW);

  //ruota posteriore destra
  digitalWrite(PBIN1, LOW);
  digitalWrite(PBIN2, HIGH);
}

void Stop() {
  //ruota anteriore sinistra
  digitalWrite(AAIN1, HIGH);
  digitalWrite(AAIN2, HIGH);

  //ruota anteriore destra
  digitalWrite(ABIN1, HIGH);
  digitalWrite(ABIN2, HIGH);

  //ruota posteriore sinistra
  digitalWrite(PAIN1, HIGH);
  digitalWrite(PAIN2, HIGH);

  //ruota posteriore sinistra
  digitalWrite(PBIN1, HIGH);
  digitalWrite(PBIN2, HIGH);

  delay(100);

  //ruota posteriore destra
  digitalWrite(PBIN1, HIGH);
  digitalWrite(PBIN2, HIGH);

  //ruota anteriore sinistra
  digitalWrite(AAIN1, LOW);
  digitalWrite(AAIN2, LOW);

  //ruota anteriore destra
  digitalWrite(ABIN1, LOW);
  digitalWrite(ABIN2, LOW);

  //ruota posteriore sinistra
  digitalWrite(PAIN1, LOW);
  digitalWrite(PAIN2, LOW);

  //ruota posteriore destra
  digitalWrite(PBIN1, LOW);
  digitalWrite(PBIN2, LOW);
}

void turnRight() {
  DxRotation();
  delay(650);
  Stop();
}

void turnLeft() {
  SxRotation();
  delay(650);
  Stop();
}

