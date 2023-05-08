// #include "header.h"
// #include "Kaki.h"
// #include "Robot.h"
// #include "Kompas.h"
// #include "KakiGroup.h"
// // #include "SensorJarakGroup.h"
// #include "Capit.h"
// #include "Sweeper.h"
// #include "Kamera.h"

// Kaki kaki = Kaki(13,14,15, KANAN, GRUP2, TENGAH);

// Kamera kam;
// // SensorJarakGroup coba;
// Capit capit;
// KakiGroup coba;
// Sweeper sweep;
// Kompas pas;

// void setup(){
//   Serial.begin(9600);
//   pas.init();
//   pas.testConnection();
// }

// void loop(){
//   pas.getCurrent();
//   delay(1000);
// }

//     ax12a.begin(BaudRate, DirectionPin, &Serial3);
    
//     Serial3.begin(1000000);
//     Serial.begin(9600);
//     kaki.berdiri();
// }
//     // kam.init();
//     // delay(50);
//     coba = KakiGroup();

//     delay(1000);
//     capit.init();
//     delay(1000);
//     sweep.init();
//     delay(2000);
//     coba.berdiri();
//     delay(2000);
//     // delay(2000);
//     // sweep.sweepTurun();
//     // delay(2000);
//     // sweep.sweepNaik();
// void loop(){}
//     // coba = SensorJarakGroup();
//     // Serial.println("Init");
//     // coba.init();
//     // delay(2000);
//     // Serial.println("berdiri");
//     // coba.berdiri();
//     // delay(2000);

//     // delay(1000);
//     // capit.turunLengan();
//     // delay(1000);

//     // capit.bukaCapit();
//     // delay(2000);

//     // capit.tutupCapit();
//     // delay(2000);

//     // capit.naikLengan();
//     // delay(1000);
    
//     // //taro
//     // capit.turunLengan();
//     // delay(1000);

//     // capit.bukaCapit();
//     // delay(1000);

//     // capit.naikLengan();
//     // delay(1000);

//     // capit.tutupCapit();
//     // delay(1000);
// }

// void loop(){
    
//       // kam.getLocation();
//       // Serial.println(pas.getCurrent().x);
//       // Serial.println(pas.getCurrent().y);
//       // Serial.println(pas.getCurrent().z);
//       // Serial.println();
//       // delay(100);
//     // if(coba.depan.bacaJarak() > 5){
//     //     capit.turun();
//     //     delay(500);
//     // }

//     // if(coba.depan.bacaJarak() < 5){
//     //     capit.naik();
//     //     delay(500);
//     // }
//     // Serial.print("Kiri : ");
//     // Serial.println(coba.kiri.bacaJarak());
//     // delay(10);
//     // Serial.print("Kanan : ");
//     // Serial.println(coba.kanan.bacaJarak());
//     // delay(10);
//     // Serial.print("Depan : ");
//     // Serial.println(coba.depan.bacaJarak());
//     // delay(10);
//     // Serial.print("Belakang : ");
//     // Serial.println(coba.belakang.bacaJarak());
//     // delay(10);

//     // Serial.println();
    
//     // delay(1000);
//     // for(int i = 0 ; i < 10 ; i++){
//     //   coba.jalan(MAJU);
//     //   delay(80);
//     // }
    
//     // delay(2000);

//     // for(int i = 0 ; i < 10 ; i++){
//     //   coba.jalan(MUNDUR);
//     //   delay(80);
//     // }
    
//     // delay(2000);

    
    
//     // Serial.println("putar kiri 10 derajat 3 kali");
//     // for(int i = 0; i < 3; i++)
//     // coba.putar(10,KIRI);
//     // delay(1000);
    
//     // Serial.println("putar kanan 10 derajat 3 kali");
//     // for(int i = 0; i < 3; i++)
//     // coba.putar(10,KANAN);
//     // delay(1000);
    
//     // Serial.println("samping kiri");
//     // for(int i = 0; i < 3; i++)
//     // coba.jalanSamping(KIRI);
//     // delay(1000);
    
//     // Serial.println("samping kanan");
//     // for(int i = 0; i < 3; i++)
//     // coba.jalanSamping(KANAN);
//     // delay(1000);
// }

// TEST KESELURUHAN
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

    // kaki.berdiri();
    // kaki.jalan(MAJU);

    // KSR2023.kamera.init();
    // KSR2023.capit.init();
    // KSR2023.capit.turunLengan();
    // KSR2023.capit.bukaCapit();
    // KSR2023.kaki.berdiri();

    // while(true){
    //     testX = KSR2023.kamera.getX();
    //     Serial.println(testX);

    //     if(testX <= 130 || testX >= 180)
    //       KSR2023.kaki.putar(5, KIRI);

    //     if(testX >= 130 && testX <= 180) 
    //       break;
    // }
    

    KSR2023.init();
    delay(1000);
    KakiGroup kaki;
    kaki.berdiriNendang();
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

    // testX = 0;
    // delay(50);
    // KSR2023.berdiri();

    // for(int i = 0 ; i < 2 ; i++){
    //   KSR2023.mundur();
    //   Serial.println(testX++);
    // }
    
    

    // Serial.println(testX);
    // Serial.println(testY);

    // KSR2023.capit.init();
    // delay(1000);
    // KSR2023.capit.turunLengan();
    // delay(1000);
    // KSR2023.capit.bukaCapit();
    // KSR2023.maju();

    // KSR2023.kameraPrintXY();

    // KSR2023.mundur();

    // KSR2023.kameraPrintXY();
    
}

void loop(){
  // KSR2023.kameraPrintXY();
  // Serial.print(KSR2023.jarak.jarakKiri());
  // Serial.print(", ");
  // Serial.print(KSR2023.jarak.jarakKanan());
  // Serial.print(", ");
  // Serial.print(KSR2023.jarak.jarakBelakang());
  // Serial.print(", ");
  // Serial.println(KSR2023.jarak.jarakDepan());
  // kalo depan kosong -> (jarak jauh) langsung skip sekuens ini
  // kalo kanan kosong -> putar kanan
  // kalo kiri kosong -> putar kiri
  // kalo belakang kosong -> putar balik dari kiri / kanan sama aja
}