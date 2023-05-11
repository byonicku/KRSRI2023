#include "Kaki.h"

static float t = 0.3; // Mengatur banyak langkah dari kaki

class KakiGroup{
  private:
    Kaki LF; // Kiri Depan
    Kaki LM; // Kiri Tengah
    Kaki LB; // Kiri Belakang
    Kaki RF; // Kanan Depan
    Kaki RM; // Kanan Tengah
    Kaki RB; // Kanan Belakang
    vec3_t standPoint; // Titik Berdiri Semut
    vec3_t standPointNendang; // Titik berdiri cuma untuk jalan nendang

  public:
    KakiGroup(){
      LF = Kaki(1,2,3, KIRI, GRUP2, DEPAN); // Aslinya depan kanan RF
      LM = Kaki(4,5,6, KIRI, GRUP1, TENGAH); // Aslinya tengah kanan RM
      LB = Kaki(7,8,9, KIRI, GRUP2, BELAKANG); // Asllinya belakang kanan RB
      RF = Kaki(10,11,12, KANAN, GRUP1, BELAKANG); // Aslinya belakang kiri LB
      RM = Kaki(13,14,15, KANAN, GRUP2, TENGAH); // Aslinya tengah kiri LM 
      RB = Kaki(16,17,18, KANAN, GRUP1, DEPAN); // Aslinya depan kiri LF
      
      // Constructor utama untuk kaki, gunakan grouping yang tepat.

      this->standPoint = {0,-43,33}; // Titik berdiri utama default : {0, -40, -30};
      this->standPointNendang = {0,-32, 38}; //-37 43 //-40 30
    }
    
    void init(){
      LF.init();
      RF.init();
      LM.init();
      RM.init();
      LB.init();
      RB.init();

      // Set kaki ke poin 0 semua (robot akan jatuh bila tidak menumpu pada sesuatu, hati")
    }
    
    void berdiri(){
      LF.berdiri();
      RF.berdiri();
      LM.berdiri();
      RM.berdiri();
      LB.berdiri();
      RB.berdiri();

      // Set kaki ke poin berdiri (standpoint)
    }

    void berdiriNendang(){
      LF.berdiriNendang();
      RF.berdiriNendang();
      LM.berdiriNendang();
      RM.berdiriNendang();
      LB.berdiriNendang();
      RB.berdiriNendang();

      // Set kaki ke poin berdiri (standpointNendang)
    }

    void langkah(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
            
        LF.langkah(tempMaju,tempMundur);
        RF.langkah(tempMaju,tempMundur);
        LM.langkah(tempMaju,tempMundur);
        RM.langkah(tempMaju,tempMundur);
        LB.langkah(tempMaju,tempMundur);
        RB.langkah(tempMaju,tempMundur);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());

      // Queue berjalan untuk kaki
    }

    void langkahNendang(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
            
        LF.langkahNendang(tempMaju,tempMundur);
        RF.langkahNendang(tempMaju,tempMundur);
        LM.langkahNendang(tempMaju,tempMundur);
        RM.langkahNendang(tempMaju,tempMundur);
        LB.langkahNendang(tempMaju,tempMundur);
        RB.langkahNendang(tempMaju,tempMundur);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());

      // Queue berjalan untuk kaki nendang
    }

    void langkahPutar(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
            
        LF.langkahPutar(tempMaju,tempMundur);
        RF.langkahPutar(tempMaju,tempMundur);
        LM.langkahPutar(tempMaju,tempMundur);
        RM.langkahPutar(tempMaju,tempMundur);
        LB.langkahPutar(tempMaju,tempMundur);
        RB.langkahPutar(tempMaju,tempMundur);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());
      // Queue berjalan untuk kaki
    }

    void jalan(int dir){
      vec3_t tinggi = {0,-25,0}; // Mengatur ketinggian dari langkah

      vec3_t P1 = rotateMatrix(this->standPoint, 10 * dir);
      vec3_t P4 = rotateMatrix(this->standPoint, -10 * dir); 

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + this->standPoint;

      langkah(bukanTrajectory(P1,naik,P4), bukanTrajectory(P4,this->standPoint,P1));
      langkah(bukanTrajectory(P4,this->standPoint,P1), bukanTrajectory(P1,naik,P4));

      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    void jalanNendang(int dir){
      vec3_t tinggi = {0,0,0}; // Mengatur ketinggian dari langkah

      vec3_t P1 = rotateMatrix(this->standPointNendang, 10 * dir);
      vec3_t P4 = rotateMatrix(this->standPointNendang, -10 * dir);

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + this->standPointNendang;

      langkahNendang(bukanTrajectory(P1,naik,P4), bukanTrajectory(P4,this->standPointNendang,P1));
      langkahNendang(bukanTrajectory(P4,this->standPointNendang,P1), bukanTrajectory(P1,naik,P4));

      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    void putar(float deg,int dir){
      vec3_t tinggi = {0,-25,0}; // Mengatur ketinggian dari langkah

      vec3_t P1 = rotateMatrix(this->standPoint, deg * dir);
      vec3_t P4 = rotateMatrix(this->standPoint, deg *-1 * dir);

      vec3_t naik = tinggi + this->standPoint;
      
      langkahPutar(bukanTrajectory(P1,naik,P4), bukanTrajectory(P4,this->standPoint,P1));
      langkahPutar(bukanTrajectory(P4,this->standPoint,P1), bukanTrajectory(P1,naik,P4));
    }
};