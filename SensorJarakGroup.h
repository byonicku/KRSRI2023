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
            
            depan = SensorJarak(7,6); 
            belakang = SensorJarak(13,12);
            kiri = SensorJarak(8,9);
            kanan  = SensorJarak(11,10);
        }
};