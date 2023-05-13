#include "SensorJarak.h"

class SensorJarakGroup{
    public:
        SensorJarak depan;
        SensorJarak belakang;
        SensorJarak kiri;
        SensorJarak kanan;

        SensorJarakGroup(){
            // Constructor untuk Grouping Sensor Jarak, gunakan pin yang sama untuk trigger dan echo
            // Urutan parameter (echo, trigger)
            
            depan =  SensorJarak(7,6);
            belakang = SensorJarak(13,12);
            kiri = SensorJarak(8,9);
            kanan  = SensorJarak(11,10);
        }

        int jarakKiri(){
          return kiri.filter();
        }
        
        int jarakKanan(){
          return kanan.filter();
        }

        int jarakDepan(){
          return depan.filter();
        }

        int jarakBelakang(){
          return belakang.filter();
        }

        void printJarak(){
            Serial.print(jarakKiri());
            Serial.print(", ");
            Serial.print(jarakKanan());
            Serial.print(", ");
            Serial.print(jarakBelakang());
            Serial.print(", ");
            Serial.println(jarakDepan());
        }
};