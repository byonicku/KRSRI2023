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
    }

    void berdiri(){
        kaki.berdiri();
    }

    void maju(){
        int lastSensor = jarak.jarakKanan();
        int nowSensor = jarak.jarakKanan();
        
        if(lastSensor - nowSensor <= 25 && nowSensor > 50){
            kaki.putar(16, KIRI);
        }

        for(int i = 0 ; i < 3 ; i++){
          kaki.jalan(MAJU);
          delay(100);
        }
    }

    void mundur(){
        for(int i = 0 ; i < 3 ; i++){
          kaki.jalan(MUNDUR);
          delay(100);
        }
    }

    void putarKiri(){
      for(int i = 0 ; i < 4 ; i++){
          kaki.putar(16, KIRI);
          delay(100);
        }

        delay(100);
        kaki.berdiri();
    }

    void putarKanan(){
      for(int i = 0 ; i < 5 ; i++){
          kaki.putar(17, KANAN);
          delay(100);
        }

        delay(100);
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
};