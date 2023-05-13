#include "header.h"
#include "Robot.h"

Robot KSR2023;

void setup(){
    ax12a.begin(BaudRate, DirectionPin, &Serial3); // inisialisasi AX12A
    Serial3.begin(1000000);
    Serial.begin(9600);

    KSR2023.init();
    KSR2023.checkPosition();
    // KSR2023.point1();
    // KSR2023.point2();
    KSR2023.point3();
}

void loop(){
  // KSR2023.kompas.printCurrent();

  KSR2023.jarak.printJarak();
}