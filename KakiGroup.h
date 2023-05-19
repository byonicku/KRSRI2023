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
    vec3_t standPointTinggi; // Titik berdiri cuma untuk jalan nendang

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
      this->standPointTinggi = {0,-32, 38}; //-37 43 //-40 30
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
    
    void berdiri(int tipeLangkah){
      LF.berdiri(tipeLangkah);
      RF.berdiri(tipeLangkah);
      LM.berdiri(tipeLangkah);
      RM.berdiri(tipeLangkah);
      LB.berdiri(tipeLangkah);
      RB.berdiri(tipeLangkah);

      // Set kaki ke poin berdiri (standpoint)
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

    void jalan(int dir, int tipeLangkah, float derajat, int height){
      //DEFAULT JALAN NORMAL DERAJAT 10
      //DEFAULT JALAN TINGGI DERAJAT 20

<<<<<<< HEAD
      vec3_t tinggi; // Mengatur ketinggian dari langkah
      vec3_t currStandPoint; // Set current standpoint
      
      if(tipeLangkah == NORMAL) {
        tinggi = {0,-25,0};
        currStandPoint = this->standPoint;
      }
      else {
        tinggi = {0,-46,0};
        currStandPoint = this->standPointTinggi;
      }

      if(height > 0)
        tinggi = {0, -height, 0};
          
      vec3_t P1 = rotateMatrix(currStandPoint, derajat * dir);
      vec3_t P4 = rotateMatrix(currStandPoint, (-derajat) * dir);
=======
      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + this->standPoint;

      langkah(bukanTrajectory(P1,naik,P4), bukanTrajectory(P4,this->standPoint,P1));
      langkah(bukanTrajectory(P4,this->standPoint,P1), bukanTrajectory(P1,naik,P4));

      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    void jalanCustom(int dir, int sudut){
      vec3_t tinggi = {0,-25,0}; // Mengatur ketinggian dari langkah

      vec3_t P1 = rotateMatrix(this->standPoint, sudut * dir);
      vec3_t P4 = rotateMatrix(this->standPoint, -1 * sudut* dir); 

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + this->standPoint;

      langkah(bukanTrajectory(P1,naik,P4), bukanTrajectory(P4,this->standPoint,P1));
      langkah(bukanTrajectory(P4,this->standPoint,P1), bukanTrajectory(P1,naik,P4));

      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    void jalanTinggi(int dir){
      vec3_t tinggi = {0,-46,0}; // Mengatur ketinggian dari langkah

      vec3_t P1 = rotateMatrix(this->standPointTinggi, 20 * dir);
      vec3_t P4 = rotateMatrix(this->standPointTinggi, -20 * dir);

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + this->standPointTinggi;

      langkahTinggi(bukanTrajectory(P1,naik,P4), bukanTrajectory(P4,this->standPointTinggi,P1));
      langkahTinggi(bukanTrajectory(P4,this->standPointTinggi,P1), bukanTrajectory(P1,naik,P4));

      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    void jalanTinggiCustom(int dir, int heigth, int sudut){
      vec3_t tinggi = {0,-1 * heigth,0}; // Mengatur ketinggian dari langkah

      vec3_t P1 = rotateMatrix(this->standPointTinggi, sudut * dir);
      vec3_t P4 = rotateMatrix(this->standPointTinggi, -1 * sudut * dir);
>>>>>>> master

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + currStandPoint;

      langkah(bukanTrajectory(P1,naik,P4), bukanTrajectory(P4,currStandPoint,P1));
      langkah(bukanTrajectory(P4,currStandPoint,P1), bukanTrajectory(P1,naik,P4));

      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    void putar(int dir, int tipeLangkah, float derajat, int height){
      vec3_t tinggi; // Mengatur ketinggian dari langkah
      vec3_t currStandPoint; // Set current standpoint

      if(tipeLangkah == NORMAL) {
        tinggi = {0,-25,0};
        currStandPoint = this->standPoint;
      }
      else {
        tinggi = {0,-48,0};
        currStandPoint = this->standPointTinggi;
      }

      if(height > 0)
        tinggi = {0, -height, 0};

      vec3_t P1 = rotateMatrix(currStandPoint, derajat * dir);
      vec3_t P4 = rotateMatrix(currStandPoint, (-derajat) * dir);

      vec3_t naik = tinggi + currStandPoint;
      
      langkahPutar(bukanTrajectory(P1,naik,P4), bukanTrajectory(P4,currStandPoint,P1));
      langkahPutar(bukanTrajectory(P4,currStandPoint,P1), bukanTrajectory(P1,naik,P4));
    }
};