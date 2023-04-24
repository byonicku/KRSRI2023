#include "Kaki.h"

float t = 0.3; // Mengatur banyak langkah dari kaki

class KakiGroup{
  private:
    Kaki LF; // Kiri Depan
    Kaki LM; // Kiri Tengah
    Kaki LB; // Kiri Belakang
    Kaki RF; // Kanan Depan
    Kaki RM; // Kanan Tengah
    Kaki RB; // Kanan Belakang
    vec3_t standPoint; // Titik Berdiri Semut

  public:
    KakiGroup(){
      LF = Kaki(1,2,3, KIRI, GRUP2, DEPAN);
      LM = Kaki(4,5,6, KIRI, GRUP1, TENGAH);
      LB = Kaki(7,8,9, KIRI, GRUP2, BELAKANG);
      RF = Kaki(10,11,12, KANAN, GRUP1, BELAKANG);
      RM = Kaki(13,14,15, KANAN, GRUP2, TENGAH);
      RB = Kaki(16,17,18, KANAN, GRUP1, DEPAN);
      // Constructor utama untuk kaki, gunakan grouping yang tepat.

      this->standPoint = {0,-40,30}; // Titik berdiri utama
    }
    
    void init(){
      LF.init();
      LM.init();
      LB.init();
      RF.init();
      RM.init();
      RB.init();

      // Set kaki ke poin 0 semua (robot akan jatuh bila tidak menumpu pada sesuatu, hati")
    }
    
    void berdiri(){
      LF.berdiri();
      LM.berdiri();
      LB.berdiri();
      RF.berdiri();
      RM.berdiri();
      RB.berdiri();

      // Set kaki ke poin berdiri (standpoint)
    }

    void langkah(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
            
        LF.langkah(tempMaju,tempMundur);
        RM.langkah(tempMaju,tempMundur);
        LB.langkah(tempMaju,tempMundur);
        RF.langkah(tempMaju,tempMundur);
        LM.langkah(tempMaju,tempMundur);
        RB.langkah(tempMaju,tempMundur);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());

      // Queue berjalan untuk kaki
    }

    void jalan(int dir){
      vec3_t tinggi = {0,-25,0}; // Mengatur ketinggian dari langkah

      vec3_t P1 = {-5,0,0}; //-5 aga ok // before -10
      vec3_t P4 = {5,0,0}; //5 aga ok // before 10

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar

      P1 = standPoint + P1 * dir;
      P4 = standPoint + P4 * dir;
  
      vec3_t P2 = tinggi + P1;
      vec3_t P3 = tinggi + P4;

      langkah(trajectory(P1,P2,P3,P4,t), trajectory(P4,P4,P1,P1,t));
      langkah(trajectory(P4,P4,P1,P1,t), trajectory(P1,P2,P3,P4,t));

      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    // UNTESTED
    void jalanSamping(int dir){
        vec3_t tinggi = {0,1,0}; // Mengatur ketinggian dari langkah

        vec3_t P1 = {0,0,1};
        vec3_t P4 = {0,0,-1};
        
        // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar

        P1 = standPoint + P1 * dir;
        P4 = standPoint + P4 * dir;

        vec3_t P2 = tinggi + P1;
        vec3_t P3 = tinggi + P4;
        
        langkah(trajectory(P1,P2,P3,P4,t), trajectory(P4,P4,P1,P1,t));
        langkah(trajectory(P4,P4,P1,P1,t), trajectory(P1,P2,P3,P4,t));

        // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    // UNTESTED
    void putar(float deg,int dir){
      vec3_t target = standPoint;
      vec3_t P1 = rotateMatrix(target, deg * dir);
      vec3_t P4 = rotateMatrix(target, deg *-1 * dir);
      vec3_t tinggi = {0,3,0};
      vec3_t titikBantu = {0,3,target.z-target.z};

      langkah(trajectory(P1,P1 + titikBantu + tinggi,P4 + titikBantu + tinggi,P4,t), trajectory(P4,P4 + titikBantu,P1 + titikBantu,P1,t));
      langkah(trajectory(P4,P4 + titikBantu,P1 + titikBantu,P1,t), trajectory(P1,P1 + titikBantu + tinggi,P4 + titikBantu + tinggi,P4,t));
    }
};