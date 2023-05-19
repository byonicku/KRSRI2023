#include "SensorJarak.h"

class SensorJarakGroup {
  private:
    SensorJarak depan;
    SensorJarak belakang;
    SensorJarak kiri;
    SensorJarak kanan;

  public:
    SensorJarakGroup() :
      depan(7, 6, 10),
      belakang(13, 12, 10),
      kiri(8, 9, 10),
      kanan(11, 10, 10)
    {}

    int jarakKiri() {
      return kiri.bacaJarak();
    }
    
    int jarakKanan() {
      return kanan.bacaJarak();
    }

    int jarakDepan() {
      return depan.bacaJarak();
    }

    int jarakBelakang() {
      return belakang.bacaJarak();
    }

    void init(){
      // Digunakan untuk mendapatkan 10 data awal sensor jarak sebagai patokan kedepannya
      for(int i = 0 ; i < 10 ; i++){
        jarakKanan();
        jarakKiri();
        jarakDepan();
        jarakBelakang();
      }
    }

    void printJarak() {
      Serial.print(jarakKiri());
      Serial.print(", ");
      Serial.print(jarakKanan());
      Serial.print(", ");
      Serial.print(jarakBelakang());
      Serial.print(", ");
      Serial.println(jarakDepan());
    }
};