#include <Servo.h> // Harus ada library Servo.h

// Pin Capit sesuaikan dengan yang ada di arduino
#define pinLengan 3
#define pinCapitan 2

class Capit{
  private:
    Servo lengan;
    Servo capitan;

  public:
    Capit(){
        
    }
    
    // Inisialisasi capit langsung ke point awal (atas) dari capit
    void init(){
      lengan.attach(pinLengan);
      capitan.attach(pinCapitan);
      delay(10);
      // Bagian atas untuk attach servo ke pin

      lengan.write(0);
      capitan.write(0);
      delay(50);

      // Bagian atas untuk mengset langsung servo ke posisi awal
    }

    void tutupCapit(){
      capitan.write(0);
      // Menutup Capit dengan sudut 0 derajat
    }

    void bukaCapit(){
      capitan.write(60);
      // Membuka Capit dengan sudut 60 derajat
    }

    void naikLengan(){ 
      for(int pos = 140 ; pos >= 0 ; pos -= 5){
          lengan.write(pos);
          delay(65);
      }
      // Prosedur untuk menaikan lengan secara perlahan dengan kecepatan 5 derajat per 65ms sampai 135 derajat maksimal
    }

    void turunLengan(){
      for(int pos = 0 ; pos <= 140 ; pos += 5){
          lengan.write(pos);
          delay(65);
      }
      // Prosedur untuk menurunkan lengan secara perlahan dengan kecepatan 5 derajat per 65ms sampai 135 derajat maksimal
    }
};
