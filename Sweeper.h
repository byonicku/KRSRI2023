#include <Servo.h> // Harus ada library Servo.h

// Pin Sweeper sesuaikan dengan yang ada di arduino
#define sweepKiri 5
#define sweekKanan 4

class Sweeper{
    private:
        Servo kiri;
        Servo kanan;

    public:
        Sweeper(){
            
        }

        // Inisialisasi servo langsung ke point awal (atas) dari sweeper
        void init(){
            kiri.attach(sweepKiri);
            kanan.attach(sweekKanan);
            // Bagian atas untuk attach servo ke pin

            delay(10);
            kiri.write(160);
            kanan.write(20);
            delay(200);

            // Bagian atas untuk mengset langsung servo ke posisi awal
        }

        void sweepNaik(){
            // Prosedur untuk menaikan sweeper kiri dan kanan secara bersamaan
            // Dengan delay 25ms dan posisi max 160 derajat
            for(int pos = 0; pos <= 160; pos += 1) { 
                kiri.write(pos);
                kanan.write(180 - pos);
                delay(25);
            }
        }

        void sweepTurun(){
            // Prosedur untuk menurunkan sweeper kiri dan kanan secara bersamaan
            // Dengan delay 25ms dan posisi max 160 derajat
            for(int pos = 160; pos >= 0; pos -= 1) {
                kiri.write(pos);
                kanan.write(180 - pos);
                delay(25);
            }
        }
};
