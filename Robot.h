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

    double yaw[4] = {0, 0, 0, 0}; // simpan lokasi arah robot menggunakan kompas

    /*
      yaw[0] -> depan
      yaw[1] -> kiri
      yaw[2] -> kanan
      yaw[3] -> belakang
    */
    
    Robot(){
      
    }

    void init(){
        kaki = KakiGroup();
        jarak = SensorJarakGroup();
        
        for(int i = 1 ; i <= 10 ; i++) jarak.printJarak(); // ADD BUFFER KE JARAK

        kamera.init();
        kompas.init();
        sweeper.init();
        delay(200);
        capit.init();
        delay(700);
        kaki.berdiri(NORMAL);
    }

    void berdiri(int tipeLangkah){
        kaki.berdiri(tipeLangkah);
    }

    void move(int action, int height, float derajat, int tipeLangkah){
      //USE DEFAULT UNTUK HEIGHT BILA TIDAK MAU SPECIFY

      kaki.jalan(action, tipeLangkah, derajat, height);
    }

    void rotate(int action, int height, int step, float derajat, int tipeLangkah){
      //DEFAULT DERAJAT (15 KIRI) (16 KANAN) 5 STEP

      for(int i = 1 ; i <= step ; i++){
          kaki.putar(action, tipeLangkah, derajat, height);
      }
    }

    void checkPosition(){
      // BUGGY BISA DI COBA DULU TES KARENA SENSOR JARAK UPDATE CODE JADI PERLU DI CEK ULANG
      
      // kalo depan kosong -> (jarak jauh) langsung skip sekuens ini
      // kalo kanan kosong -> putar kanan
      // kalo kiri kosong -> putar kiri
      // kalo belakang kosong -> putar balik dari kiri / kanan sama aja

      /*
          yaw[0] -> depan
          yaw[1] -> kiri
          yaw[2] -> kanan
          yaw[3] -> belakang
      */

      if(jarak.jarakBelakang() >= 390){ // Berarti lagi ngadep belakang
        yaw[3] = kompas.getCurrent().x;
        
        yaw[0] = yaw[3] + 180;
        yaw[2] = yaw[3] - 90;
        yaw[1] = yaw[3] + 90;

        setPos(0, DEFAULT, 0, 2, 15, NORMAL);
      }
      else if(jarak.jarakKiri() >= 390){ // Berarti lagi ngadep kanan
        yaw[2] = kompas.getCurrent().x; 
        
        yaw[1] = yaw[2] + 180;
        yaw[0] = yaw[2] - 90;
        yaw[3] = yaw[2] + 90;

        setPos(0, DEFAULT, 0, 2, 15, NORMAL);
      }
      else if(jarak.jarakKanan() >= 390){ // Berarti lagi ngadep kiri
        yaw[1] = kompas.getCurrent().x; 
        
        yaw[2] = yaw[1] + 180;
        yaw[3] = yaw[1] - 90;
        yaw[0] = yaw[1] + 90;

        setPos(0, DEFAULT, 0, 2, 15, NORMAL);
      }
      else if(jarak.jarakDepan() >= 390){ // Ngadep depan
        yaw[0] = kompas.getCurrent().x;
        
        yaw[3] = yaw[0] + 180;
        yaw[1] = yaw[0] - 90;
        yaw[2] = yaw[0] + 90;
      }

      // Serial.print(yaw[0]);
      // Serial.print(", ");
      // Serial.print(yaw[1]);
      // Serial.print(", ");
      // Serial.print(yaw[2]);
      // Serial.print(", ");
      // Serial.println(yaw[3]);
    }

    void getKorban(int height, float derajat, int tipeLangkah){
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
          rotate(KANAN, height, 1, 4, tipeLangkah);
        else if (X >= 175)
          rotate(KIRI, height, 1, 3, tipeLangkah);
        else
          move(MAJU, height, derajat, tipeLangkah);

        W = kamera.getWidth();
        H = kamera.getHeight();

        if(W - H >= 85) break;
      }

      if(tipeLangkah == NORMAL){
        delay(500);
        capit.tutupCapit();
        capit.naikLenganDikit();
        move(MUNDUR, height, derajat, tipeLangkah);
        delay(50);
        capit.naikLenganLanjutan();
      }
      else{
        berdiri(NORMAL);
        delay(500);
        capit.tutupCapit();
        berdiri(TINGGI);
        capit.naikLenganDikit();
        move(MUNDUR, height, derajat, tipeLangkah);
        delay(50);
        capit.naikLenganLanjutan();
      }
    }

    void fixPos(int index, int height, int error, float derajat, int tipeLangkah){
      //DEFAULT ERROR 2 NORMAL
      //DEFAULT ERROR 3.5 TINGGI

      //DEFAULT DERAJAT 3 NORMAL
      //DEFAULT DERAJAT 5 TINGGI

      double simpan = 0;

      do{
          simpan = kompas.getCurrent().x;

          if(simpan < yaw[index] - error)
              rotate(KANAN, height, 1, derajat, tipeLangkah);
          if(simpan > yaw[index] + error)
              rotate(KIRI, height, 1, derajat, tipeLangkah);
          
      }while(simpan < yaw[index] - error || simpan > yaw[index] + error);
    }

    void setPos(int index, int height, int set, int error, float derajat, int tipeLangkah){
      //DEFAULT ERROR 2
      //DEFAULT ERROR 3.5 TINGGI

      //DEFAULT DERAJAT 3 NORMAL
      //DEFAULT DERAJAT 5 TINGGI
      double simpan = kompas.getCurrent().x;
      double simpanNext = 0;
      int putar = 0;

      do{
          simpanNext = kompas.getCurrent().x;
        
          if((simpan >= 270 && simpan <= 360) && (simpanNext >= 0 && simpanNext <= 90)){
            putar++;
          }
          
          simpanNext += putar * 360;

          Serial.println(simpanNext);

          if(simpanNext < yaw[index] - error + set)
              rotate(KANAN, height, 1, derajat, tipeLangkah);

          if(simpanNext > yaw[index] + error + set)
              rotate(KIRI, height, 1, derajat, tipeLangkah);
          
          simpan = simpanNext;
      }while(simpanNext < yaw[index] - error + set || simpanNext > yaw[index] + error + set);
    }

    void point1(){
      int langkah = 0;

      // Langkah ke depan korban 1
      while(1){
        if(jarak.jarakBelakang() >= 400)
            break;

        if(langkah % 3 == 0 && langkah != 0)
          fixPos(0, DEFAULT, 2, 3, NORMAL);
        
        move(MAJU, DEFAULT, 10, NORMAL);
        langkah++;
      }
      
      berdiri(NORMAL);

      // Putar arah korban
      rotate(KIRI, DEFAULT, 5, 15, NORMAL);
      fixPos(1, DEFAULT, 2, 3, NORMAL);

      berdiri(NORMAL);

      // Mundur untuk meluruskan
      while(1) {
        move(MUNDUR, DEFAULT, 10, NORMAL);

        if(jarak.jarakBelakang() <= 380) 
            break;
      }

      // Mengambil korban
      getKorban(DEFAULT, 10, NORMAL);
      
      // Mundur ke titik tertentu agar kaki dapat masuk ke area retak
      langkah = 0;
      while(1) {
        if(jarak.jarakBelakang() <= 410)
            break;

        if(langkah % 3 == 0 && langkah != 0)
            fixPos(1, DEFAULT, 2, 3, NORMAL);

        move(MUNDUR, DEFAULT, 5, NORMAL);
        langkah++; 
      }

      berdiri(NORMAL);

      // Putar kanan dan luruskan
      rotate(KANAN, DEFAULT, 5, 16, NORMAL);
      fixPos(0, DEFAULT, 2, 3, NORMAL);

      langkah = 0;

      while(1){
        if(jarak.jarakBelakang() >= 430)
            break;

        if(langkah % 3 == 0 && langkah != 0)
          fixPos(0, DEFAULT, 2, 3, NORMAL);
      
        move(MAJU, DEFAULT, 5, NORMAL);
        langkah++;
      }

      fixPos(0, DEFAULT, 2, 3, NORMAL);
    }

    void point2(){
      int langkah = 0;

      berdiri(NORMAL);
      delayMicroseconds(100);

      while(1){
        if(kompas.getCurrent().z < -13.5)
            break;

        if(langkah % 3 == 0 && langkah != 0)
            fixPos(0, 45, 15, 3.5, TINGGI);
        
        move(MAJU, 45, 17, TINGGI);
        langkah++;
      }

      berdiri(NORMAL);
      langkah = 0;

      while(1) {
        if(kompas.getCurrent().z > -3) 
            break;

        if(langkah % 3 == 0 && langkah != 0) 
          fixPos(0, DEFAULT, 2, 3, NORMAL);

        move(MAJU, DEFAULT, 10, NORMAL);
        langkah++;
      }
    }

    void point3(){
      berdiri(TINGGI);
      fixPos(0, DEFAULT, 5, 3.5, TINGGI);
      berdiri(TINGGI);

      int langkah = 0;

      while(1) {
        if(langkah % 3 == 0 && langkah != 0){
          fixPos(0, 40, 5, 3.5, TINGGI);
          
          if(jarak.jarakDepan() <= 180) 
            break;
        }
        
        move(MAJU, 40, 5, TINGGI);
        langkah++;
      }
    
      setPos(0, DEFAULT, 25, 3.5, 5, TINGGI);

      berdiri(TINGGI);
      
      capit.turunLengan(); 
      capit.bukaCapit();
      delay(200);

      capit.naikLengan();
      capit.tutupCapit();
      
      setPos(1, DEFAULT, 0, 3.5, 5, TINGGI);
    }

    void point4(){
      berdiri(TINGGI);

      int langkah = 0;

      while(1) {
        if(langkah % 3 == 0 && langkah != 0){
          fixPos(0, 40, 5, 3.5, TINGGI);

          if(jarak.jarakDepan() <= 200)
            break;
        }
        
        move(MAJU, 40, 12, TINGGI);
        langkah++;
      }

      rotate(KIRI, DEFAULT, 5, 15, NORMAL);

      berdiri(TINGGI);

      getKorban(DEFAULT, 10, NORMAL);

      berdiri(TINGGI);

      for(int i = 0 ; i < 2 ; i++) move(MUNDUR, DEFAULT, 20, TINGGI);

      rotate(KANAN, DEFAULT, 5, 16, NORMAL);

      while(jarak.jarakDepan() > 80) move(MAJU, DEFAULT, 20, TINGGI);

      // algo taruh

      for(int i = 0 ; i < 2 ; i++) move(MUNDUR, DEFAULT, 20, TINGGI);

      int tes = 4;

      while(tes-- > 0) rotate(KIRI, DEFAULT, 1, 6, NORMAL);

      while(jarak.jarakDepan() > 120) move(MAJU, DEFAULT, 20, TINGGI);

      berdiri(NORMAL);
    }
};