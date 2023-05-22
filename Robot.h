#include "Arduino.h"
#include "KakiGroup.h"
#include "Capit.h"
#include "SensorJarakGroup.h"
#include "Kamera.h"
#include "Sweeper.h"
#include "Kompas.h"

class Robot{
  public:
    KakiGroup kaki;
    SensorJarakGroup jarak;
    Kamera kamera;
    Sweeper sweeper;
    Capit capit;
    Kompas kompas;
    /*
        yaw[0] -> depan
        yaw[1] -> kiri
        yaw[2] -> kanan
        yaw[3] -> belakang
      */
     double yaw[4] = {0, 0, 0, 0}; // simpan lokasi arah robot menggunakan kompas

    Robot(){}

    void init(){
        kaki = KakiGroup();
        jarak = SensorJarakGroup();

        kamera.init();
        kompas.init();
        sweeper.init();
        capit.init();
        kaki.berdiri(NORMAL);
    }

    //Untuk keperluan testing StandPoint
    void berdiriDebug(vec3_t standPoint){
        kaki.berdiriDebug(standPoint);
    }
    //Untuk keperluan testing StandPoint
    void moveDebug(int action, vec3_t tinggi, float derajat, vec3_t standPoint, int speed = 10){
      //USE DEFAULT UNTUK HEIGHT BILA TIDAK MAU SPECIFY
      kaki.jalanDebug(action, standPoint, derajat, tinggi, speed);
    }
    
    void berdiri(int tipeLangkah){
        kaki.berdiri(tipeLangkah);
    }
    
    void move(int action, int height, float derajat, int tipeLangkah, int speed = 10){
      //USE DEFAULT UNTUK HEIGHT BILA TIDAK MAU SPECIFY
      kaki.jalan(action, tipeLangkah, derajat, height, speed);
    }
    
    void rotate(int action, int height, int step, float derajat, int tipeLangkah, int speed = 10){
      //DEFAULT DERAJAT (15 KIRI) (16 KANAN) 5 STEP
      for(int i = 1 ; i <= step ; i++){
          kaki.putar(action, tipeLangkah, derajat, height, speed);
      }
    }

    void checkPosition(){
      // BUGGY BISA DI COBA DULU TES KARENA SENSOR JARAK UPDATE CODE JADI PERLU DI CEK ULANG
      
      // kalo depan kosong -> (jarak jauh) langsung skip sekuens ini
      // kalo kanan kosong -> putar kanan
      // kalo kiri kosong -> putar kiri
      // kalo belakang kosong -> putar balik dari kiri / kanan sama aja

      if(jarak.jarakBelakang() >= 390){ // Berarti lagi ngadep belakang
        yaw[3] = kompas.getCurrent().x;
        
        yaw[0] = yaw[3] + 180;
        yaw[2] = yaw[3] - 90;
        yaw[1] = yaw[3] + 90;

        setPos(0, DEFAULT, 0, 2, 12, NORMAL);
      }
      else if(jarak.jarakKiri() >= 390){ // Berarti lagi ngadep kanan
        yaw[2] = kompas.getCurrent().x; 
        
        yaw[1] = yaw[2] + 180;
        yaw[0] = yaw[2] - 90;
        yaw[3] = yaw[2] + 90;

        setPos(0, DEFAULT, 0, 2, 12, NORMAL);
      }
      else if(jarak.jarakKanan() >= 390){ // Berarti lagi ngadep kiri
        yaw[1] = kompas.getCurrent().x; 
        
        yaw[2] = yaw[1] + 180;
        yaw[3] = yaw[1] - 90;
        yaw[0] = yaw[1] + 90;

        setPos(0, DEFAULT, 0, 2, 12, NORMAL);
      }
      else if(jarak.jarakDepan() >= 390){ // Ngadep depan
        yaw[0] = kompas.getCurrent().x;
        
        yaw[3] = yaw[0] + 180;
        yaw[1] = yaw[0] - 90;
        yaw[2] = yaw[0] + 90;
      }
    }

    void cetakYaw(){
       Serial.print(yaw[0]);
       Serial.print(", ");
       Serial.print(yaw[1]);
       Serial.print(", ");
       Serial.print(yaw[2]);
       Serial.print(", ");
       Serial.println(yaw[3]);
    }
    
    void getKorban(int height, float derajat, int tipeLangkah, int speed = 10){
      //USE " DEFAULT " JIKA TIDAK MAU SPECIFY HEIGHT
      //DEFAULT DERAJAT 10 NORMAL
      //DEFAULT DERAJAT 20 TINGGI

      int X, Y, W, H;
      X = Y = W = H = 0;

      delay(200);

      capit.turunLengan();
      capit.bukaCapit();

      while(1){
        X = kamera.getX();
        Y = kamera.getY();

        if(X >= 0 && X <= 125)
          rotate(KANAN, height, 1, 4, tipeLangkah, speed);
        else if (X >= 175)
          rotate(KIRI, height, 1, 3, tipeLangkah, speed);
        else
          move(MAJU, height, derajat, tipeLangkah, speed);

        W = kamera.getWidth();
        H = kamera.getHeight();

        if(W - H >= 85) break;
      }
      berdiri(NORMAL);
      delay(500);
      capit.tutupCapit();
      berdiri(TINGGI);
      capit.naikLenganDikit();
      for(int i = 0; i < 2; i++){
        move(MUNDUR, height, derajat, tipeLangkah, speed);
      }
      delay(50);
      capit.naikLenganLanjutan();
    }

    void fixPos(int index, int height, int error, float derajat, int tipeLangkah, int speed = 10){
      //DEFAULT ERROR 2 NORMAL
      //DEFAULT ERROR 3.5 TINGGI

      //DEFAULT DERAJAT 3 NORMAL
      //DEFAULT DERAJAT 5 TINGGI

      double simpan = kompas.getCurrent().x;
      double simpanNext = simpan;
      int putar = 0;

      do{
         simpanNext = kompas.getCurrent().x;
          //Jika dari putaran kanan
          if((simpan >= 270 && simpan <= 360) && (simpanNext >= 0 && simpanNext <= 90)){
            putar++;
          }
          if((simpan >= 360 && simpan <= 450) && (simpanNext >= 270 && simpanNext <= 360)){
            putar--;
          }
          //jika dari putaran kiri
          if((simpanNext >= 270 && simpanNext <= 360) && (simpan >= 0 && simpan <= 90)){
            putar--;
          }
          if((simpanNext >= 360 && simpanNext <= 450) && (simpan >= 270 && simpan <= 360)){
            putar++;
          }
          //digunakan hanya jika dia lagi menuju ke yaw yang berada diperbatasan 360
          if(yaw[index] >= 345 && yaw[index] <= 375){
            simpanNext += putar * 360;
            if(simpanNext < 90){
              putar++;
              simpanNext += putar * 360;
            }
          }
          if(simpanNext < yaw[index] - error)
              rotate(KANAN, height, 1, derajat, tipeLangkah, speed);
          if(simpanNext > yaw[index] + error)
              rotate(KIRI, height, 1, derajat, tipeLangkah, speed);
          
      }while(simpanNext < yaw[index] - error || simpanNext > yaw[index] + error);
    }

    void setPos(int index, int height, int set, int error, float derajat, int tipeLangkah, int speed = 10){
      //DEFAULT ERROR 2
      //DEFAULT ERROR 3.5 TINGGI

      //DEFAULT DERAJAT 3 NORMAL
      //DEFAULT DERAJAT 5 TINGGI
      double simpan = kompas.getCurrent().x;
      double simpanNext = simpan;
      int putar = 0;

      do{
          simpanNext = kompas.getCurrent().x;
          //Jika dari putaran kanan
          if((simpan >= 270 && simpan <= 360) && (simpanNext >= 0 && simpanNext <= 90)){
            putar++;
          }
          if((simpan >= 360 && simpan <= 450) && (simpanNext >= 270 && simpanNext <= 360)){
            putar--;
          }
          //jika dari putaran kiri
          if((simpanNext >= 270 && simpanNext <= 360) && (simpan >= 0 && simpan <= 90)){
            putar--;
          }
          if((simpanNext >= 360 && simpanNext <= 450) && (simpan >= 270 && simpan <= 360)){
            putar++;
          }
          //digunakan hanya jika dia lagi menuju ke yaw yang berada diperbatasan 360
          if(yaw[index] >= 345 && yaw[index] <= 375){
            simpanNext += putar * 360;
            if(simpanNext < 90){
              putar++;
              simpanNext += putar * 360;
            }
          }
          if(simpanNext < yaw[index] - error + set)
              rotate(KANAN, height, 1, derajat, tipeLangkah, speed);

          if(simpanNext > yaw[index] + error + set)
              rotate(KIRI, height, 1, derajat, tipeLangkah, speed);
          
          simpan = simpanNext;
      }while(simpanNext < yaw[index] - error + set || simpanNext > yaw[index] + error + set);
    }

    void point1(){
      int langkah = 0;

      // Langkah ke depan korban 1
      while(1){
        if(langkah % 3 == 0 && langkah != 0)
          fixPos(0, DEFAULT, 2, 3, NORMAL);
        
        move(MAJU, DEFAULT, 10, NORMAL);
        if(jarak.jarakBelakang() >= 490)
            break;
        langkah++;
      }
      
      berdiri(NORMAL);

      // Putar arah korban (KIRI)
      setPos(1, DEFAULT, 0, 3, 8, NORMAL);

      berdiri(NORMAL);

      // Mundur untuk meluruskan
      while(1) {
        move(MUNDUR, DEFAULT, 10, NORMAL);

        if(jarak.jarakBelakang() <= 100) 
            break;
      }

      // Mengambil korban
      getKorban(DEFAULT, 10, NORMAL);
      
      // Mundur ke titik tertentu agar kaki dapat masuk ke area retak
      langkah = 0;
      while(1) {
        if(jarak.jarakBelakang() <= 80)
            break;

        if(langkah % 3 == 0 && langkah != 0)
            fixPos(1, DEFAULT, 2, 3, NORMAL);

        move(MUNDUR, DEFAULT, 5, NORMAL);
        langkah++; 
      }

      berdiri(NORMAL);

      // Putar kanan dan luruskan (ke depan)
      setPos(0, DEFAULT, 0, 3, 8, NORMAL);

      langkah = 0;
      while(1){
        if(jarak.jarakBelakang() >= 530)
            break;

        if(langkah % 3 == 0 && langkah != 0)
          fixPos(0, DEFAULT, 2, 3, NORMAL);
      
        move(MAJU, DEFAULT, 8, NORMAL);
        langkah++;
      }

      fixPos(0, DEFAULT, 2, 3, NORMAL);
    }

    void point2(){
      int langkah = 0;

      berdiri(SEDANG_25);

      while(1){
        if(kompas.getCurrent().z < -14)
            break;

        if(langkah % 3 == 0 && langkah != 0)
            fixPos(0, DEFAULT, 8, 12, SEDANG_25, 150);
        
        move(MAJU, DEFAULT, 18, SEDANG_25, 150);
        langkah++;
      }
      
      //masuk turunan
      berdiri(SEDANG_15);
      
      langkah = 0;
      while(1) {
        if(kompas.getCurrent().z > -3) 
            break;

        if(langkah % 3 == 0 && langkah != 0) 
          fixPos(0, DEFAULT, 3.5, 15, SEDANG_15, 80);

        move(MAJU, DEFAULT, 20, SEDANG_15, 80);
        langkah++;
      }
    }

    void point3(){
      fixPos(0, DEFAULT, 3, 3, SEDANG_15, 60);
      berdiri(SEDANG_15);

      int langkah = 0;
      while(1) {
        if(langkah % 3 == 0 && langkah != 0){
          fixPos(0, DEFAULT, 8, 3.5, SEDANG_15, 60);
          if(jarak.jarakDepan() <= 250) 
            break;
        }
        
        move(MAJU, 40, 8, SEDANG_15, 60);
        langkah++;
      }
      //hadap 25 derajat miring dari depan
      setPos(0, DEFAULT, 25, 3.5, 5, SEDANG_15, 60);

      berdiri(SEDANG_15);
      
      capit.turunLengan(); 
      capit.bukaCapit();
      for(int i = 0; i < 2; i++){
          move(MUNDUR, 40, 8, SEDANG_15, 60);
        }
      capit.naikLengan();
      capit.tutupCapit();
      
      //menuju ke depan daerah kelereng
      //hadap kiri
      setPos(1, DEFAULT, 0, 3.5, 8, SEDANG_15, 60);
      //maju sampai mentok
      langkah = 0;
      while(1) {
        if(langkah % 3 == 0 && langkah != 0){
          fixPos(0, DEFAULT, 2, 3, SEDANG_15, 60);
          if(jarak.jarakBelakang() >= 170) 
            break;
        }
        
        move(MAJU, DEFAULT, 8, SEDANG_15, 60);
        langkah++;
      }
      if(jarak.jarakKanan() > 110){
        //hadap depan
        setPos(0, DEFAULT, 0, 3.5, 10, SEDANG_15, 60);
        //maju sampai mentok
        langkah = 0;
        while(1) {
          if(langkah % 3 == 0 && langkah != 0){
            fixPos(0, DEFAULT, 2, 3, SEDANG_15, 60);
            if(jarak.jarakDepan() <= 80) 
              break;
          }
          
          move(MAJU, DEFAULT, 8, SEDANG_15, 60);
          langkah++;
        }
      }
      //hadap ke kiri
      setPos(1, DEFAULT, 0, 3.5, 8, SEDANG_15, 60);
    }

    void point4(){
      berdiri(SEDANG_20);

      int langkah = 0;

      while(1) {
        if(langkah % 3 == 0 && langkah != 0){
          fixPos(1, DEFAULT, 5, 12, SEDANG_20, 50);
        }
        if(jarak.jarakBelakang() >= 440 && jarak.jarakDepan() >= 440)
            break;
        
        move(MAJU, DEFAULT, 15, SEDANG_20, 50);
        langkah++;
      }

      //hadap ke korban (belakang)
      setPos(3, DEFAULT, 0, 3.5, 18, SEDANG_20, 50);

      berdiri(SEDANG_20);

      getKorban(DEFAULT, 10, NORMAL);

      berdiri(SEDANG_20);
      
      //hadap ke kiri 
      setPos(1, DEFAULT, 0, 3.5, 12, SEDANG_20, 50);

      langkah = 0;
      while(1) {
        if(langkah % 3 == 0 && langkah != 0){
          fixPos(0, DEFAULT, 3.5, 8, TINGGI, 50);
          if(jarak.jarakDepan() <= 300) 
            break;
        }
        
        move(MAJU, DEFAULT, 12, SEDANG_20, 50);
        langkah++;
      }
      //hadap 65 derajat miring dari kiri
      setPos(1, DEFAULT, 65, 3.5, 8, TINGGI, 50);

      berdiri(NORMAL);
      
      capit.turunLengan(); 
      capit.bukaCapit();
      for(int i = 0; i < 2; i++){
          move(MUNDUR, 40, 8, SEDANG_20, 50);
        }
      capit.naikLengan();
      capit.tutupCapit();

      berdiri(SEDANG_20);

      setPos(3, DEFAULT, 0, 3.5, 10, SEDANG_20, 50);
    }
};
