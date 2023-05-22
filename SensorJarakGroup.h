#include "SensorJarak.h"

class SensorJarakGroup {
  private:
    SensorJarak depan;
    SensorJarak belakang;
    SensorJarak kiri;
    SensorJarak kanan;

  public:
    SensorJarakGroup() :
      depan(7, 6),
      belakang(13, 12),
      kiri(8, 9),
      kanan(11, 10)
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

    void printJarak() {
      Serial.print("Kiri: ");
      Serial.print(jarakKiri());
      Serial.print(", ");
      Serial.print("Kanan: ");
      Serial.print(jarakKanan());
      Serial.print(", ");
      Serial.print("Belakang: ");
      Serial.print(jarakBelakang());
      Serial.print(", ");
      Serial.print("Depan: ");
      Serial.println(jarakDepan());
    }
};
