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
        for(int i = 0 ; i < 10 ; i++){
          kaki.jalan(MAJU);
          delay(20);
        }
    }

    void mundur(){
        for(int i = 0 ; i < 10 ; i++){
          kaki.jalan(MUNDUR);
          delay(20);
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

        capit.naikLengan();
        delay(1000);
        
        capit.tutupCapit();
        delay(1000);        
    }
};