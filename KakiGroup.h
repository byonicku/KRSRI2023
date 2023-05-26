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
    vec3_t standPoint[nStandPoint] = {
          {0, -42, 37}, //Normal 0 - 90
          {0, -33, 36}, // 10-80
          {0, -29, 35}, //15-75
          {0, -25, 34}, //20-70
          {0,-20, 32}, //25-65
          {0,-18, 32}  //Tinggi 30 - 60
        }; //Array titik berdiri 
    vec3_t tinggi[nStandPoint] = {
          {0,-20,-10}, //Normal 0 - 90
          {0,-30,-8},  // 10-80
          {0,-35,-8},  //15-75
          {0,-40,-8},  //20-70
          {0,-45,-4}, //25-65
          {0,-45,-3}  //Tinggi 30 - 60
      }; //Array tinggi default utk tiap StandPoint

  public:
    KakiGroup(){
      // Constructor utama untuk kaki, gunakan grouping yang tepat.
      LF = Kaki(1,2,3, KIRI, GRUP2, DEPAN); // Aslinya depan kanan RF
      LM = Kaki(4,5,6, KIRI, GRUP1, TENGAH); // Aslinya tengah kanan RM
      LB = Kaki(7,8,9, KIRI, GRUP2, BELAKANG); // Asllinya belakang kanan RB
      RF = Kaki(10,11,12, KANAN, GRUP1, BELAKANG); // Aslinya belakang kiri LB
      RM = Kaki(13,14,15, KANAN, GRUP2, TENGAH); // Aslinya tengah kiri LM 
      RB = Kaki(16,17,18, KANAN, GRUP1, DEPAN); // Aslinya depan kiri LF
    }
    
    void init(){
      // Set kaki ke poin 0 semua (robot akan jatuh bila tidak menumpu pada sesuatu, hati")
      LF.init();
      RF.init();
      LM.init();
      RM.init();
      LB.init();
      RB.init();
    }
    
    void berdiri(int tipeLangkah){
      // Set kaki ke poin berdiri (standpoint)
      LF.berdiri(this->standPoint[tipeLangkah]);
      RF.berdiri(this->standPoint[tipeLangkah]);
      LM.berdiri(this->standPoint[tipeLangkah]);
      RM.berdiri(this->standPoint[tipeLangkah]);
      LB.berdiri(this->standPoint[tipeLangkah]);
      RB.berdiri(this->standPoint[tipeLangkah]);
    }

    void berdiriSamping(int tipeLangkah){
      // Set kaki ke poin berdiri (standpoint)
      vec3_t sudutSampingL = {22,0,-10};
      vec3_t sudutSampingR = {-22,0,-10};
      vec3_t newStandPointL = this->standPoint[tipeLangkah] + sudutSampingL;
      vec3_t newStandPointR = this->standPoint[tipeLangkah] + sudutSampingR;
      
      LF.berdiri(newStandPointL);
      RF.berdiri(newStandPointL);
      LM.berdiri(this->standPoint[tipeLangkah]);
      RM.berdiri(this->standPoint[tipeLangkah]);
      LB.berdiri(newStandPointR);
      RB.berdiri(newStandPointR);
    }
    
    void langkah(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur, int speed = 10){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
            
        LF.langkah(tempMaju,tempMundur);
        RF.langkah(tempMaju,tempMundur);
        LM.langkah(tempMaju,tempMundur);
        RM.langkah(tempMaju,tempMundur);
        LB.langkah(tempMaju,tempMundur);
        RB.langkah(tempMaju,tempMundur);
        delay(speed);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());
    }

    void langkahPutar(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur, int speed = 10){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
            
        LF.langkahPutar(tempMaju,tempMundur);
        RF.langkahPutar(tempMaju,tempMundur);
        LM.langkahPutar(tempMaju,tempMundur);
        RM.langkahPutar(tempMaju,tempMundur);
        LB.langkahPutar(tempMaju,tempMundur);
        RB.langkahPutar(tempMaju,tempMundur);
        delay(speed);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());
    }

    void langkahSamping(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur, int speed = 10){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
        
        LF.langkahPutar(tempMaju,tempMundur);
        RF.langkahPutar(tempMaju,tempMundur);
        LM.langkahPutar(tempMaju,tempMundur);
        RM.langkahPutar(tempMaju,tempMundur);
        LB.langkahPutar(tempMaju,tempMundur);
        RB.langkahPutar(tempMaju,tempMundur);
        delay(speed);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());
    }
    
    void jalan(int dir, int tipeLangkah, float derajat, int height, int speed){
      vec3_t tinggi = this->tinggi[tipeLangkah]; // Mengatur ketinggian dari langkah
      //jika custom
      if(height > 0)
        tinggi = {0, -height, this->tinggi[tipeLangkah].z};
          
      vec3_t P1 = rotateMatrix(this->standPoint[tipeLangkah], derajat * dir);
      vec3_t P4 = rotateMatrix(this->standPoint[tipeLangkah], (-derajat) * dir);

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + this->standPoint[tipeLangkah];

      langkah(trajectory(P1,naik,P4), trajectory(P4,this->standPoint[tipeLangkah],P1), speed);
      langkah(trajectory(P4,this->standPoint[tipeLangkah],P1), trajectory(P1,naik,P4), speed);
      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    void putar(int dir, int tipeLangkah, float derajat, int height, int speed){
      vec3_t tinggi = this->tinggi[tipeLangkah]; // Mengatur ketinggian dari langkah
      //jika custom
      if(height > 0)
        tinggi = {0, -height, this->tinggi[tipeLangkah].z};

      vec3_t P1 = rotateMatrix(this->standPoint[tipeLangkah], derajat * dir);
      vec3_t P4 = rotateMatrix(this->standPoint[tipeLangkah], (-derajat) * dir);

      vec3_t naik = tinggi + this->standPoint[tipeLangkah];
      
      langkahPutar(trajectory(P1,naik,P4), trajectory(P4,this->standPoint[tipeLangkah],P1), speed);
      langkahPutar(trajectory(P4,this->standPoint[tipeLangkah],P1), trajectory(P1,naik,P4), speed);
    }

    void samping(int dir, int tipeLangkah, float derajat, int height, int speed){
      vec3_t tinggi = this->tinggi[tipeLangkah]; // Mengatur ketinggian dari langkah
      //jika custom
      if(height > 0)
        tinggi = {0, -height, this->tinggi[tipeLangkah].z};

      vec3_t sudutSampingL = {22,0,-10};
      vec3_t sudutSampingR = {-22,0,-10};
      vec3_t newStandPointL = this->standPoint[tipeLangkah] + sudutSampingL;
      vec3_t newStandPointR = this->standPoint[tipeLangkah] + sudutSampingR;
      
      vec3_t P1 = this->standPoint[tipeLangkah];
      vec3_t P4 = this->standPoint[tipeLangkah];

      vec3_t naik = tinggi + this->standPoint[tipeLangkah];
      
      langkahSamping(trajectory(P1,naik,P4), trajectory(P4,this->standPoint[tipeLangkah],P1), speed);
      langkahSamping(trajectory(P4,this->standPoint[tipeLangkah],P1), trajectory(P1,naik,P4), speed);
    }

    //Untuk keperluan testing StandPoint Baru
    void berdiriDebug(vec3_t standPoint){
      // Set kaki ke poin berdiri (standpoint)
      LF.berdiri(standPoint);
      RF.berdiri(standPoint);
      LM.berdiri(standPoint);
      RM.berdiri(standPoint);
      LB.berdiri(standPoint);
      RB.berdiri(standPoint);
    }
    
    //Untuk keperluan testing StandPoint Baru
    void jalanDebug(int dir, vec3_t standPoint, float derajat, vec3_t tinggi, int speed){
      vec3_t P1 = rotateMatrix(standPoint, derajat * dir);
      vec3_t P4 = rotateMatrix(standPoint, (-derajat) * dir);

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + standPoint;

      langkah(trajectory(P1,naik,P4), trajectory(P4,standPoint,P1), speed);
      langkah(trajectory(P4,standPoint,P1), trajectory(P1,naik,P4), speed);
      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }
};
