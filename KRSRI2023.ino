#include "header.h"
#include "Robot.h"

Robot KSR2023;

void debugNewStandPoint();

void setup(){
    ax12a.begin(BaudRate, DirectionPin, &Serial3); // inisialisasi AX12A
    Serial3.begin(1000000);
    Serial.begin(9600);
    //debugNewStandPoint(); //uncomment jika ingin mencari atau testing standPoint baru

    KSR2023.init();
    delay(2000);
//    KSR2023.berdiri(SEDANG_20); //Untuk test jalan
//    delay(500);
//    for(int i = 0; i < 10; i++){
//      KSR2023.move(MAJU, DEFAULT, 15, SEDANG_20, 40);
//    }
//    delay(500);
    KSR2023.berdiri(SEDANG_20);
    KSR2023.checkPosition();
    KSR2023.point1();
    KSR2023.point2();
    KSR2023.point3();
    KSR2023.point4();
}

void loop(){
  // KSR2023.kompas.printCurrent();
   //KSR2023.jarak.printJarak();
}

void debugNewStandPoint(){
    //Untuk testing stand point
    cariStandpoint(); //untuk mencari value standPoint baru
//    vec3_t tinggiDebug = {0,-45,-4}; //tinggi maks langkah dari standPointDebug
//    vec3_t standPointDebug = {0,-20, 32}; //standPoint baru ingin ditext
//
//    //untuk test di satu kaki (gunakan untuk mencari value tinggiDebug
//    vec3_t naikDebug = tinggiDebug + standPointDebug;
//    Kaki(1,2,3, KIRI, GRUP2, DEPAN).moveToPoint(naikDebug);
//    
//    //test jalan
//    KSR2023.berdiriDebug(standPointDebug); //test berdiri
//    for(int i = 0; i < 10; i++){
//      KSR2023.moveDebug(MAJU, tinggiDebug, 10, standPointDebug, 500);
//    }
//    KSR2023.berdiriDebug(standPointDebug);
}
