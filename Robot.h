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
        delay(500);
        capit.init();
        delay(500);
        kaki.berdiri();
        delay(500);
    }

    void berdiri(){
        kaki.berdiri();
    }

    void maju(){
        for(int i = 0 ; i < 10 ; i++){
          coba.jalan(MAJU);
          delay(80);
        }
    }

    void mundur(){
        for(int i = 0 ; i < 10 ; i++){
          coba.jalan(MUNDUR);
          delay(80);
        }
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

        capit.tutupCapit();
        delay(1000);

        capit.naikLengan();
        delay(1000);
    }
};