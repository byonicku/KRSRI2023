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

    double yaw[4] = {0, 0, 0, 0};
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

        kamera.init();
        kompas.init();
        sweeper.init();
        delay(1000);

        capit.init();
        delay(1000);
        
        kaki.berdiri();
        delay(1000);

        // simpan = kompas.getCurrent();
    }

    void berdiri(){
        kaki.berdiri();
    }

    void berdiriTinggi(){
        kaki.berdiriTinggi();
    }

    void maju(){
        kaki.jalan(MAJU);
    }

    void majuTinggi(){
        kaki.jalanTinggi(MAJU);
    }

    void mundur(){
        kaki.jalan(MUNDUR);
    }
    
    void mundurTinggi(){
        kaki.jalanTinggi(MUNDUR);
    }

    void putarKiri(){
      for(int i = 0 ; i < 5 ; i++){
          kaki.putar(15, KIRI);
          delayMicroseconds(10);
      }
    }

    void putarKanan(){
      for(int i = 0 ; i < 5 ; i++){
          kaki.putar(16, KANAN);
          delayMicroseconds(10);
        }

        kaki.berdiri();
    }   

    void ambil(){
        capit.turunLengan();
        delay(1000);

        capit.bukaCapit();
        delay(1000);

        capit.tutupCapit();
        delay(1000);

        capit.naikLengan();
        delay(1000);
    }

    void taruh(){
        capit.turunLengan();
        delay(1000);

        capit.bukaCapit();
        delay(1000);

        capit.naikLengan();
        delay(1000);
        
        capit.tutupCapit();
        delay(1000);        
    }

    // Debug
    void kameraPrintLocation(){
        Serial.print(kamera.getX());
        Serial.print(", ");
        Serial.print(kamera.getY());
        Serial.print(", ");
        Serial.print(kamera.getWidth());
        Serial.print(", ");
        Serial.println(kamera.getHeight());
    }

    void checkPosition(){
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

      if(jarak.jarakBelakang() >= 250){
        yaw[3] = kompas.getCurrent().x;
        
        if(yaw[3] < 0) yaw[0] = yaw[3] + 180;
        else if(yaw[3] > 0) yaw[0] = yaw[3] - 180;
        
        yaw[2] = yaw[3] - 90;
        yaw[1] = yaw[3] + 90;

        putarKiri();
        for(int i = 0 ; i < 2 ; i++) kaki.jalan(MAJU);
        kaki.berdiri();
        putarKiri();
        kaki.putar(14, KIRI);
        kaki.berdiri();
      }
      else if(jarak.jarakKiri() >= 245){
        yaw[2] = kompas.getCurrent().x; 
        
        if(yaw[2] < 0) yaw[1] = yaw[2] + 180;
        else if(yaw[2] > 0) yaw[1] = yaw[2] - 180;
        
        yaw[0] = yaw[2] - 90;
        yaw[3] = yaw[2] + 90;

        putarKiri();
      }
      else if(jarak.jarakKanan() >= 250){
        yaw[1] = kompas.getCurrent().x; 
        
        if(yaw[1] < 0) yaw[2] = yaw[1] + 180;
        else if(yaw[1] > 0) yaw[2] = yaw[1] - 180;
        
        yaw[3] = yaw[1] - 90;
        yaw[0] = yaw[1] + 90;

        putarKanan();
      }
      else {
        yaw[0] = kompas.getCurrent().x;
        
        if(yaw[0] < 0) yaw[3] = yaw[0] + 180;
        else if(yaw[0] > 0) yaw[3] = yaw[0] - 180;
        
        yaw[1] = yaw[0] - 90;
        yaw[2] = yaw[0] + 90;

        return;
      }
    }

    void getKorban(){
      int X, Y, W, H;
      X = Y = W = H = 0;

      delay(200);

      capit.turunLengan();
      capit.bukaCapit();

      while(1){
        X = kamera.getX();
        Y = kamera.getY();

        if(X >= 0 && X <= 125)
          kaki.putar(4, KANAN);
        else if (X >= 175)
          kaki.putar(3, KIRI);
        else 
          kaki.jalan(MAJU);

        W = kamera.getWidth();
        H = kamera.getHeight();

        if(W - H >= 85) break;
      }

      delay(500);
      capit.tutupCapit();
      mundur();
      delay(50);
      capit.naikLengan();
    }

    void fixPos(int index){
      double simpan = 0;

      do{
          simpan = kompas.getCurrent().x;

          if(simpan < yaw[index] - 2)
              kaki.putar(5, KANAN);
          
          if(simpan > yaw[index] + 2)
              kaki.putar(5, KIRI);
          
      }while(simpan < yaw[index] - 2 || simpan > yaw[index] + 2);
    }

    void point1(){
      int langkah = 0;

      // Langkah ke depan korban 1
      while(1){
        if(langkah % 3 == 0 && langkah != 0){
          fixPos(0);

          if(jarak.jarakBelakang() > 278)
            break;
        }

        maju();
        langkah++;
      }
      
      berdiri();

      // Putar arah korban
      putarKiri();
      fixPos(1);

      delayMicroseconds(100);

      berdiri();

      // Mundur untuk meluruskan
      while(1) {
        mundur();

        if(jarak.jarakBelakang() <= 50) break;
      }


      // Mengambil korban
      getKorban();
      
      // Mundur ke titik tertentu agar kaki dapat masuk ke area retak
      while(1) {
        mundur();

        if(jarak.jarakBelakang() <= 120) break;
      }

      berdiri();

      // Putar kanan dan luruskan
      putarKanan();
      fixPos(0);
    }

    void point2(){
      int langkah = 0;

      berdiriTinggi();
      delayMicroseconds(100);

      while(1){
        if(langkah % 3 == 0 && langkah != 0) fixPos(0);
        if(kompas.getCurrent().z < -13) break;

        majuTinggi();
        langkah++;
      }

      berdiri();
      langkah = 0;

      while(1) {
        if(langkah % 3 == 0 && langkah != 0) fixPos(0);
        if(jarak.jarakDepan() <= 90) break;
        maju();

        langkah++;
      }

      berdiriTinggi();
      langkah = 0;

      while(1) {
        if(langkah % 3 == 0 && langkah != 0) fixPos(0);
        if(jarak.jarakDepan() <= 100) break;
        majuTinggi();

        langkah++;
      }
    }

    void point3(){
      berdiri();
      int putar, temp;
      putar = temp = 0;
      while(1){
        if(jarak.jarakDepan() > 230)  kaki.putar(7, KANAN);

        if(jarak.jarakDepan() < 150) break;

        putar++;
      }
      
      while(jarak.jarakDepan() > 80) maju();
      
      taruh();

      temp = putar - 2;

      while(putar-- > 0) kaki.putar(6, KIRI);

      for(int i = 0 ; i < 2 ; i++) maju();

      while(temp-- > 0)  kaki.putar(6, KIRI);
    }

    void point4(){
      berdiriTinggi();

      while(1) {
        majuTinggi();

        if(jarak.jarakDepan() < 300) break;
      }

      putarKiri();

      berdiri();

      getKorban();

      berdiriTinggi();

      for(int i = 0 ; i < 2 ; i++) mundurTinggi();

      putarKanan();

      while(jarak.jarakDepan() > 80) majuTinggi();

      taruh();

      for(int i = 0 ; i < 2 ; i++) mundurTinggi();

      int tes = 4;

      while(tes-- > 0) kaki.putar(6, KIRI);

      while(jarak.jarakDepan() > 120) majuTinggi();

      berdiri();
    }
};