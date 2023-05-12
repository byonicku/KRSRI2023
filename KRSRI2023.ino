#include "header.h"
#include "Robot.h"
// #include "KakiGroup.h"
// #include "SensorJarakGroup.h"
// KakiGroup kaki;
Robot KSR2023;
// SensorJarakGroup g = SensorJarakGroup();

void setup(){
    ax12a.begin(BaudRate, DirectionPin, &Serial3); // inisialisasi AX12A
    Serial3.begin(1000000);
    Serial.begin(9600);

    KSR2023.init();
    KSR2023.kaki.berdiriTinggi();
    delay(500);
    Serial.println("MAJUMAJUMAJU");
    KSR2023.kaki.jalanTinggi(MAJU);
    KSR2023.kaki.jalanTinggi(MAJU);
    KSR2023.kaki.jalanTinggi(MAJU);
    // Kaki kaki;
    // kaki.berdiriTinggi();
    Serial.println("Sel");
    // KSR2023.maju();
    // KSR2023.maju();
    // KSR2023.maju();
    // KSR2023.maju();
    // KSR2023.maju();
    // KSR2023.kaki.berdiriTinggi();
    // KSR2023.point2();
    // KSR2023.kaki.berdiriTinggi();

    // Kaki kaki;
    // kaki.berdiriTinggi();

    // KSR2023.checkPosition();
    // KSR2023.point1();

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
  // Serial.print(KSR2023.jarak.jarakKiri());
  // Serial.print(", ");
  // Serial.print(KSR2023.jarak.jarakKanan());
  // Serial.print(", ");
  // Serial.print(KSR2023.jarak.jarakBelakang());
  // Serial.print(", ");
  // Serial.println(KSR2023.jarak.jarakDepan());
}