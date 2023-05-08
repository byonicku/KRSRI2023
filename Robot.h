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
    
    Robot(){
      
    }

    void init(){
        kaki = KakiGroup();
        jarak = SensorJarakGroup();

        kamera.init();

        sweeper.init();
        delay(1000);

        capit.init();
        delay(1000);
        
        // kaki.berdiri();
        // delay(1000);
    }

    void berdiri(){
        kaki.berdiri();
    }

    void maju(){
        kaki.jalan(MAJU);
        delay(50);
    }

    void mundur(){
          kaki.jalan(MUNDUR);
          delay(50);
    }

    void putarKiri(){
      for(int i = 0 ; i < 7 ; i++){
          kaki.putar(14, KIRI);
          delay(50);
        }

        kaki.berdiri();
    }

    void putarKanan(){
      for(int i = 0 ; i < 6 ; i++){
          kaki.putar(22, KANAN);
          delay(50);
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

    void kameraPrintXY(){
        Serial.print(kamera.getX());
        Serial.print(", ");
        Serial.print(kamera.getY());
        Serial.print(", ");
        Serial.print(kamera.getWidth());
        Serial.print(", ");
        Serial.println(kamera.getHeight());
        //jauh W 50 - 70 H 60 - 65
        //deket 130 - 200 H 45 - 55
    }

    void checkPosition(){
      // kalo depan kosong -> (jarak jauh) langsung skip sekuens ini
      // kalo kanan kosong -> putar kanan
      // kalo kiri kosong -> putar kiri
      // kalo belakang kosong -> putar balik dari kiri / kanan sama aja
      if(jarak.jarakBelakang() >= 250){
        putarKiri();
        delay(100);
        kaki.jalan(MAJU);
        delay(50);
        kaki.jalan(MAJU);
        delay(50);
        kaki.berdiri();
        delay(50);
        putarKiri();
        kaki.putar(14, KIRI);
        kaki.berdiri();
      }
      else if(jarak.jarakKiri() >= 245){
        putarKiri();
      }
      else if(jarak.jarakKanan() >= 250){
        putarKanan();
      }
      else {
        return;
      }
    }

    void getKorban(){
      int testX = 0;
      int testY = 0;
      int testW = 0;
      int testH = 0;
      delay(200);

      capit.turunLengan();
      delay(500);
      capit.bukaCapit();

      while(1){
        // Serial.print(testX);
        // Serial.print(", ");
        // Serial.print(testY);
        // Serial.print(", ");
        // Serial.print(testW);
        // Serial.print(", ");
        // Serial.println(testH);
        testX = kamera.getX();
        testY = kamera.getY();

        if(testX >= 0 && testX <= 125)
          kaki.putar(4, KANAN);
        else if (testX >= 175)
          kaki.putar(3, KIRI);
        else 
          kaki.jalan(MAJU);

        testW = kamera.getWidth();
        testH = kamera.getHeight();

        if(testW - testH >= 85)
          break;
      }

      delay(700);
      capit.tutupCapit();
      delay(50);
      capit.naikLengan();
    }

    void point1(){
      int langkah = 0;

      while(1){
        if(langkah % 7 == 0 && langkah != 0){
          kaki.putar(7, KANAN);
          
          if(jarak.jarakBelakang() > 278)
            break;
        }

        maju();
        // berdiri();
        langkah++;
      }
      
      berdiri();
      for(int i = 0 ; i < 6 ; i++){
          kaki.putar(14, KIRI);
          delay(100);
        }

      delay(100);
      kaki.berdiri();

      delay(50);
      mundur();
      mundur();
      delay(50);

      getKorban();
      
      mundur();
      mundur();
      mundur();
      berdiri();

      putarKanan();
    }

    void point2(){
      for(int i = 0 ; i < 6 ; i++)
        kaki.jalanNendang(MAJU);
        delay(40);
    }
};