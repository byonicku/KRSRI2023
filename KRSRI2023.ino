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
// }

// void loop(){
//   Serial.print(pas.getCurrent().x);
//   Serial.print(", ");
//   Serial.print(pas.getCurrent().y);
//   Serial.print(", ");
//   Serial.println(pas.getCurrent().z);
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

Robot KSR2023;

void setup(){
    ax12a.begin(BaudRate, DirectionPin, &Serial3); // inisialisasi AX12A
    Serial3.begin(1000000);
    Serial.begin(9600);
    
    KSR2023.init();
    delay(1000);

    KSR2023.berdiri();
    delay(1000);

    KSR2023.maju();
    delay(1000);

    // KSR2023.ambil();
    // delay(1000);

    KSR2023.mundur();
    delay(1000);

    // KSR2023.taruh();
}

void loop(){

}