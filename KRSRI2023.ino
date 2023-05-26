#include "header.h"
#include "Robot.h"

Robot KSR2023;

void setup(){
    ax12a.begin(BaudRate, DirectionPin, &Serial3); // inisialisasi AX12A
    Serial3.begin(1000000);
    Serial.begin(115200);
    KSR2023.init();
    delay(1000);
}

void loop(){
  switch(KSR2023.state){
    //init
     case 0:{
        KSR2023.checkPosition();
        break;
     }
     //menuju korban
     case 1:{
        KSR2023.kondisiTargetJarakMin[BACK] = 450;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break; 
     }
     //hadap korban
     case 2:{
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KIRI;
        break; 
     }
     //mundur utk meluruskan
     case 3:{
        KSR2023.kondisiTargetJarakMax[BACK] = 100;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MUNDUR;
        break; 
     }
     //ambil korban
     case 4:{
        KSR2023.getKorban();
        break; 
     }
     //mundur menyesuaikan dengan jalan retak
     case 5:{
        KSR2023.kondisiTargetJarakMax[BACK] = 60;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MUNDUR;
        KSR2023.derajatLangkah = 5;
        break; 
     }
     //hadap depan
     case 6:{
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KANAN;
        KSR2023.derajatLangkah = 10; // direset kembali
        break; 
     }
     //maju sampai mentok
     case 7:{
        KSR2023.kondisiTargetJarakMin[BACK] = 530;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break; 
     }
     //maju jalan retak
     case 8:{
        KSR2023.kondisiTargetRollMax = -12;
        KSR2023.tipeLangkah = SEDANG_25;
        KSR2023.derajatLangkah = 18;
        KSR2023.speed = 150;
        KSR2023.error = 12;
        KSR2023.derajatLangkahSetPos = 10;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break; 
     }
     //masuk jalan miring
     case 9:{
        KSR2023.kondisiTargetRollMin = -3;
        KSR2023.tipeLangkah = SEDANG_15;
        KSR2023.derajatLangkah = 15;
        KSR2023.speed = 80;
        KSR2023.error = 3;
        KSR2023.derajatLangkahSetPos = 3;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break; 
     }
     //masuk jalan batu
     case 10:{
        KSR2023.kondisiTargetJarakMax[FRONT] = 100;
        KSR2023.tipeLangkah = SEDANG_10;
        KSR2023.derajatLangkah = 8;
        KSR2023.speed = 60;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break; 
     }
     //belok kanan hadap safezone
     case 11:{
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KANAN;
        break; 
     }
     //maju sampai aman untuk letakkan korban
     case 12:{
        KSR2023.kondisiTargetJarakMax[FRONT] = 180;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break;
     }
     //letakkan korban
     case 13:{
        KSR2023.letakanKorban();
        break; 
     }
     //belok kiri hadap korban
     case 14:{
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KIRI;
        break;
     }
     //maju sampai mentok
     case 15:{
        KSR2023.kondisiTargetJarakMax[BACK] = 100;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break; 
     }
     //hadap ke kelereng
     case 16:{
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KIRI;
        break;
     }
     //Masuk ke kelereng
     case 18:{
        KSR2023.tipeLangkah = SEDANG_25;
        KSR2023.derajatLangkah = 18;
        KSR2023.speed = 120;
        KSR2023.kondisiTargetJarakMin[BACK] = 430;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        KSR2023.error = 8;
        KSR2023.derajatLangkahSetPos = 10;
        break;
     }
     //hadap ke boneka
     case 19:{
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KIRI;
        break;
     }
     case 20:{
        KSR2023.tipeLangkah = NORMAL;
        KSR2023.derajatLangkah = 10;
        KSR2023.speed = 10;
        KSR2023.getKorban();
        break;
     }
     case 21:{
        KSR2023.tipeLangkah = TINGGI;
        KSR2023.derajatLangkah = 18;
        KSR2023.speed = 150;
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KANAN;
        break;
     }
     case 22:{
        KSR2023.kondisiTargetJarakMax[FRONT] = 150;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break;
     }
     //hadap miring 35 derajat ke kanan untuk letakkin boneka
     case 23:{
        KSR2023.offsetDirection = 35;
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = STAY;
        break; 
     }
     //letakkin korban
     case 24:{
        KSR2023.letakanKorban();
        KSR2023.offsetDirection = 0;
        break; 
     }
     case 25:{
        KSR2023.tipeLangkah = TINGGI;
        KSR2023.derajatLangkah = 18;
        KSR2023.speed = 150;
        KSR2023.kondisiTargetJarakMax[FRONT] = 100;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break;
     }
     case 26:{
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KIRI;
        KSR2023.offsetDirection = 15;
        break; 
     }
     //maju sampai dekat sebelum ke jalan retak 2
     case 27:{
        KSR2023.kondisiTargetJarakMin[BACK] = 400;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        KSR2023.error = 3;
        KSR2023.derajatLangkahSetPos = 3;
        break;
     }
     //miringkan dikit
     case 28:{
        KSR2023.offsetDirection = -50;
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = STAY;
     }
     //maju teruss sampai jalan retak
     case 29:{
        KSR2023.tipeLangkah = TINGGI;
        KSR2023.derajatLangkah = 18;
        KSR2023.speed = 120;
        KSR2023.kondisiTargetJarakMax[LEFT] = 80;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        KSR2023.error = 8;
        KSR2023.derajatLangkahSetPos = 8;
        break;
     }
     //luruskan kalau mentok
     case 30:{
        KSR2023.offsetDirection = 0;
        break; 
     }
     //maju ke depan sampai mentok
     case 31:{
        KSR2023.kondisiTargetJarakMax[FRONT] = 80;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break;
     }
     //putar kanan
     case 32:{
        KSR2023.tipeLangkah = SEDANG_10;
        KSR2023.derajatLangkah = 15;
        KSR2023.speed = 40;
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KANAN;
        KSR2023.error = 3;
        KSR2023.derajatLangkahSetPos = 3;
        break; 
     }
     //Maju sampai mentok
     case 33:{
        KSR2023.tipeLangkah = SEDANG_10;
        KSR2023.derajatLangkah = 10;
        KSR2023.speed = 80;
        KSR2023.error = 3;
        KSR2023.kondisiTargetJarakMax[FRONT] = 80;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break;
     }
     //putar kiri
     case 34:{
        KSR2023.movingType = ROTATING;
        KSR2023.movingDirection = KIRI;
        break; 
     }
     case 35:{
        KSR2023.kondisiTargetJarakMin[BACK] = 520;
        KSR2023.movingType = MOVING;
        KSR2023.movingDirection = MAJU;
        break;
     }
     //Mode Manual
     case MANUALMODE:{
        KSR2023.initManualMode();
        manualMod();
        break;
     }
  }
  //Print kondisi robot
  KSR2023.printCurrentYPR();
  KSR2023.printJarak();
  KSR2023.printState();
  
  if(KSR2023.movingType != STAY){
    //mengecek kondisi sudah terpenuh atau tidak
    cekKondisi();
    KSR2023.move();
  }
  KSR2023.setPos();
  //update Buffer
  KSR2023.readUltrasonic();
  //keamanan
  keamanan();
  //Manual Mode di comment aja jika tidak dipakai
  if(Serial.available() > 0){
    KSR2023.state = MANUALMODE;
    Serial.println("Manual mode actived...");
    String dump = Serial.readString();
    manualMod();
  }
}

void keamanan(){
  if(KSR2023.movingType == MOVING && KSR2023.movingDirection == MAJU && KSR2023.jarakDepan() <= 20){
    KSR2023.berdiri();
    KSR2023.state = 404;
  }
  if(KSR2023.movingType == MOVING && KSR2023.movingDirection == MUNDUR && KSR2023.jarakBelakang() <= 20){
    KSR2023.berdiri();
    KSR2023.state = 404;
  }
}

void cekKondisi(){
  if(KSR2023.kondisiTargetJarakMin[FRONT] != 0 && KSR2023.jarakDepan() >= KSR2023.kondisiTargetJarakMin[FRONT]){
      KSR2023.berdiri();
      KSR2023.state++;
    }
    if(KSR2023.kondisiTargetJarakMin[BACK] != 0 && KSR2023.jarakBelakang() >= KSR2023.kondisiTargetJarakMin[BACK]){
      KSR2023.berdiri();
      KSR2023.state++;
    }
    if(KSR2023.kondisiTargetJarakMin[LEFT] != 0 && KSR2023.jarakKiri() >= KSR2023.kondisiTargetJarakMin[LEFT]){
      KSR2023.berdiri();
      KSR2023.state++;
    }
    if(KSR2023.kondisiTargetJarakMin[RIGHT] != 0 && KSR2023.jarakKanan() >= KSR2023.kondisiTargetJarakMin[RIGHT]){
      KSR2023.berdiri();
      KSR2023.state++;
    }
    if(KSR2023.kondisiTargetJarakMax[FRONT] != 0 && KSR2023.jarakDepan() <= KSR2023.kondisiTargetJarakMax[FRONT]){
      KSR2023.berdiri();
      KSR2023.state++;
    }
    if(KSR2023.kondisiTargetJarakMax[BACK] != 0 && KSR2023.jarakBelakang() <= KSR2023.kondisiTargetJarakMax[BACK]){
      KSR2023.berdiri();
      KSR2023.state++;
    }
    if(KSR2023.kondisiTargetJarakMax[LEFT] != 0 && KSR2023.jarakKiri() <= KSR2023.kondisiTargetJarakMax[LEFT]){
      KSR2023.berdiri();
      KSR2023.state++;
    }
    if(KSR2023.kondisiTargetRollMin != 0 && KSR2023.getRoll() >= KSR2023.kondisiTargetRollMin){
      KSR2023.berdiri();
      KSR2023.state++;
    }
    if(KSR2023.kondisiTargetRollMax != 0 && KSR2023.getRoll() <= KSR2023.kondisiTargetRollMax){
      KSR2023.berdiri();
      KSR2023.state++;
    }
}

//Mode Manual robot
void manualMod(){
  Serial.println("Fetching current robot state...");
  KSR2023.printCurrentYPR();
  KSR2023.printJarak();
  KSR2023.printState();
  do{
      
      if(Serial.available() > 0){
        int step = 1;
        String input = Serial.readString();
        if(input.startsWith("END")){
          KSR2023.state = 0;
          printData();
          return;
        }
        if(input.startsWith("MAJU")){
          step = getValue(input, '-',1).toInt();
          for(int i = 0; i < step; i++){
            KSR2023.maju();
            KSR2023.setPos();
          }
          printData();
          continue;
        }
        if(input.startsWith("MUNDUR")){
          step = getValue(input, '-',1).toInt();
          for(int i = 0; i < step; i++){
            KSR2023.mundur();
            KSR2023.setPos();
          }
          printData();
          continue;
        }
        if(input.startsWith("KIRI")){
          KSR2023.kiri();
          KSR2023.setPos();
          printData();
          continue;
        }
        if(input.startsWith("KANAN")){
          KSR2023.kanan();
          KSR2023.setPos();
          printData();
          continue;
        }
        if(input.startsWith("GET")){
          KSR2023.getKorban();
          printData();
          continue;
        }
        if(input.startsWith("PUT")){
          KSR2023.letakanKorban();
          printData();
          continue;
        }

        //konversi parameter
        /*  FORMAT set parameter
         *  tipeLangkah-derajatLangkah-height-offsetDirection-direction-speed-error
         *  tipeLangkah: 0-5 (6 abaikan)
         *  derajatLangkah: 1-18 (0 abaikan)
         *  height: 0 <= (0 DEFAULT) //Sebaiknya tidak diubah
         *  offsetDirection: 0 <= (0 DEFAULT)
         *  direction: 0-3 (4 abaikan)
         *  speed: 0 <= (0 DEFAULT)
         *  error: 1 <= (0 abaikan)
         */
        int tipeLangkah = getValue(input, '-',0).toInt();
        int derajatLangkah = getValue(input, '-',1).toInt();
        int height = getValue(input, '-',2).toInt();
        int offsetDirection = getValue(input, '-',3).toInt();;
        int direction = getValue(input, '-',4).toInt();
        int speed = getValue(input, '-',5).toInt();
        int error = getValue(input, '-',6).toInt();
        
        if(tipeLangkah <= 5){
          KSR2023.tipeLangkah = tipeLangkah;
          KSR2023.berdiri();
          printData();
        }
        if(derajatLangkah > 0 && derajatLangkah <= 18){
          KSR2023.derajatLangkah = derajatLangkah;
          printData();
        }
        if(height >= 0){
          KSR2023.height = height;
          printData();
        }
        if(offsetDirection >= 0){
          KSR2023.offsetDirection = offsetDirection;
          printData();
        }
        if(direction >= 0 && direction <= 3){
          KSR2023.direction = direction;
          printData();
        }
        if(speed >= 0){
          KSR2023.speed = speed;
          printData();
        }
        if(error > 0){
          KSR2023.error = error;
          printData();
        }
        KSR2023.setPos();
      }
    }while(1);
}

void printData(){
  //update Buffer
  KSR2023.readUltrasonic();
  KSR2023.printCurrentYPR();
  KSR2023.printJarak();
  KSR2023.printState();
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//Panggil di setup untuk mengetes langkah
void testJalanStandPoint(int tipeLangkah){
  KSR2023.init();
  delay(2000);
  KSR2023.berdiri(tipeLangkah); //Untuk test jalan
  delay(500);
  for(int i = 0; i < 10; i++){
    KSR2023.move(MAJU, DEFAULT, 15, tipeLangkah, 40);
  }
  delay(500);
  KSR2023.berdiri(tipeLangkah);
}

//Panggil di setup jika ingin mencari standPoint baru
void debugNewStandPoint(){
    //Untuk testing stand point
    //cariStandpoint(); //untuk mencari value standPoint baru
    vec3_t tinggiDebug = {12,0,-6}; //tinggi maks langkah dari standPointDebug
    vec3_t standPointDebug = {0, -28, 18}; //standPoint baru ingin ditext
    vec3_t masuk = {-2,2,-4};
    vec3_t naik = {0,-20,-10};
    vec3_t geser = {-30,-10,-30};
//    KSR2023.init();
//    KSR2023.kaki.berdiriSamping(NORMAL);
    //untuk test di satu kaki (gunakan untuk mencari value tinggiDebug
    vec3_t naikDebug = tinggiDebug + standPointDebug + masuk;
    Kaki(1,2,3, KIRI, GRUP2, DEPAN).moveToPointSecond(naikDebug);
    
    //test jalan
//    KSR2023.berdiriDebug(standPointDebug); //test berdiri
//    for(int i = 0; i < 10; i++){
//      KSR2023.moveDebug(MAJU, tinggiDebug, 10, standPointDebug, 500);
//    }
//    KSR2023.berdiriDebug(standPointDebug);
}

// ini dibawah sebelumnya untuk nyari standpoint yg pas :v
void cariStandpoint(){
  Serial.println("Mulai");
  for(int i = -200 ; i < 200 ; i++){
      for(int j = -200 ; j < 200 ; j++){
        for(int k = -200; k < 200; k++){
          vec3_t miring = {22,0,-10}; //tinggi maks langkah dari standPointDebug
          vec3_t standPointDebug = {0, -42, 37}; //standPoint baru ingin ditext
          vec3_t standPointTinggi = {i, j, k};
          vec3_t result = miring + standPointDebug + standPointTinggi;
          vec3_t deggs = InversKinematik(result);
          /*
           * Gunakan relasi y dan z berupa y = 90 - z untuk mencari standPoint
           * Contoh: y = 30 & z = 60
          */
          if((deggs.y > -1 && deggs.y < 1) && (deggs.x > 39 && deggs.x < 41) && (deggs.z < -50 && deggs.z > -70) ){
            Serial.print("TEST "); Serial.println(i); Serial.print(" i: "); Serial.print(i); Serial.print(" j: "); Serial.print(j); Serial.print(" k: "); Serial.print(k);Serial.println();          
            Serial.println();
            Serial.print(deggs.x);
            Serial.print(" , ");
            Serial.print(deggs.y);
            Serial.print(" , ");
            Serial.println(deggs.z);
          }
        }
      }
  }
  Serial.println("Selesai");
}
