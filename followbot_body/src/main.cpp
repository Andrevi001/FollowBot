#include <servos.h>
#include <motori.h>
#include <comunicazioneEsp.h>

SerialTransfer busEsp;
Pan_Tilt pt;

void centerBody();
void decideFwBw(uint8_t distance);

void setup(){

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  busEsp.begin(Serial2);
  
  
  servoPan.attach(PAN);
  servoTilt.attach(TILT);
  
  pt.centerFov();

  //pin logica di controllo per le ruote
  pinMode(STBY, OUTPUT);
  pinMode(AAIN1,OUTPUT);
  pinMode(AAIN2,OUTPUT);
  pinMode(ABIN1,OUTPUT);
  pinMode(ABIN2,OUTPUT);
  pinMode(PAIN1,OUTPUT);
  pinMode(PAIN2,OUTPUT);
  pinMode(PBIN1,OUTPUT);
  pinMode(PBIN2,OUTPUT);

  //pin regolamento della velocità(PWM)
  ledcSetup(6, 20000, 8);
  ledcAttachPin(PWM, 6);
  ledcWrite(6, 150);

  //APSTBY sempre HIGH (non va mai in standby)
  digitalWrite(STBY, HIGH);
}

void loop() {
  if (busEsp.available()) {
    busEsp.rxObj(dati);
    if ((uint8_t)dati.header == 0x80) {
      pt.updateServos(dati.pan_sum, dati.tilt_sum);
      if (pt.getPan() > 170) {
        turnLeft();
        pt.centerFov();
      } else if (pt.getPan() < 10) {
        turnRight();
        pt.centerFov();
      }
    }
    decideFwBw(dati.distance);
  }
}


void centerBody() {
  if (pt.getPan() <= 10) {
    turnRight();
    pt.centerFov();
  } else if (pt.getPan() >= 170) {
    turnLeft();
    pt.centerFov();
  }
}

void decideFwBw(uint8_t distance) {
  if (distance > 170 ) {
    Forward();
  } else if (distance < 100 ) {
    Backward();
  } else {
    Stop();
  }
}