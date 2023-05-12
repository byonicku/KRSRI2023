#include "header.h"
#include "Robot.h"

Robot KSR2023;

void setup(){
    ax12a.begin(BaudRate, DirectionPin, &Serial3); // inisialisasi AX12A
    Serial3.begin(1000000);
    Serial.begin(9600);

    KSR2023.init();
    delay(1000);
    KSR2023.checkPosition();
    KSR2023.point1();
    KSR2023.point2();
    // KSR2023.point3();

    // for(int i = 0 ; i < 5 ; i++){
    //   int lastSensor = KSR2023.jarak.jarakKanan();
    //   int nowSensor = KSR2023.jarak.jarakKanan();

    //   if(lastSensor - nowSensor <= 25 && nowSensor > 50){
    //       KSR2023.kaki.putar(5, KIRI);
    //   }

    //   KSR2023.maju();
    //   Serial.println(testX++);
    // }
}

void loop(){
  // KSR2023.kompas.printCurrent();
  // KSR2023.simpan = KSR2023.kompas.getCurrent();
  //           Serial.print(KSR2023.simpan.x);
  //           Serial.print(", ");
  //           Serial.print(KSR2023.simpan.y);
  //           Serial.print(", ");
  //           Serial.println(KSR2023.simpan.z);

  // Serial.print(KSR2023.jarak.jarakKiri());
  // Serial.print(", ");
  // Serial.print(KSR2023.jarak.jarakKanan());
  // Serial.print(", ");
  // Serial.print(KSR2023.jarak.jarakBelakang());
  // Serial.print(", ");
  // Serial.println(KSR2023.jarak.jarakDepan());
}