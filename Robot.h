#include "Arduino.h"
#include "KakiGroup.h"
#include "Capit.h"
#include "SensorJarakGroup.h"
#include "Kamera.h"
#include "Sweeper.h"
#include "Kompas.h"

class Robot{
  private:
    KakiGroup kaki;
    SensorJarakGroup jarak;
    Kamera kamera;
    Sweeper sweeper;
    Capit capit;
    Kompas kompas;
  public:
    //parameter robot
    int tipeLangkah = NORMAL;
    float derajatLangkah = 10;
    float derajatLangkahSetPos = 3;
    int height = DEFAULT;
    int direction = FRONT;
    int offsetDirection = 0;
    int movingType = STAY; //jenis gerakan lagi diam, gerak maju mundur, atau mutar
    int movingDirection = STAY; //arah gerakan MAJU-MUNDUR-KIRI-KANAN
    float error = 3.0;
    int speed = 10;
    bool isHoldingKorban = false;
    int kondisiTargetJarakMin[4] = {0,0,0,0}; //kondisi target dari ke-4 jarak, jika 0 abaikan
    int kondisiTargetJarakMax[4] = {0,0,0,0}; 
    int kondisiTargetRollMin = 0; //kondisi target dari roll, jika 0 abaikan
    int kondisiTargetRollMax = 0;
    int state = MANUALMODE;
    /*
     * yaw[0] -> depan
     * yaw[1] -> kiri
     * yaw[2] -> kanan
     * yaw[3] -> belakang
     */
    double yaw[4] = {0, 0, 0, 0}; // simpan lokasi arah robot menggunakan kompas
    
    Robot(){}

    void printState(){
      Serial.print("S: "); 
      Serial.print(state);
      Serial.print(" TL: "); 
      Serial.print(tipeLangkah);
      Serial.print(" DL: "); 
      Serial.print(derajatLangkah);
      Serial.print(" H: "); 
      Serial.print(height);
      Serial.print(" Arah: "); 
      Serial.print(direction);
      Serial.print(" Offset: "); 
      Serial.print(offsetDirection);
      Serial.print(" MT: "); 
      Serial.print(movingType);
      Serial.print(" MD: "); 
      Serial.print(movingDirection);
      Serial.print(" E: "); 
      Serial.print(error);
      Serial.print(" Speed: "); 
      Serial.print(speed);
      Serial.print(" korban: "); 
      Serial.print(isHoldingKorban);
      Serial.print(" MinU: "); 
      for(int i = 0; i < 4; i++){
        Serial.print(kondisiTargetJarakMin[i]);
        Serial.print(',');
      }
      Serial.print(" MaxU:  "); 
      for(int i = 0; i < 4; i++){
        Serial.print(kondisiTargetJarakMax[i]);
        Serial.print(',');
      }
      Serial.print(" MinR: "); 
      Serial.print(kondisiTargetRollMin);
      Serial.print(" MaxR: "); 
      Serial.println(kondisiTargetRollMax);
      cetakYaw();
      Serial.println("------------------------------");
    }
    
    void init(){
        kaki = KakiGroup();
        jarak = SensorJarakGroup();

        for(int i = 1 ; i <= 5 ; i++) jarak.readAllJarak();// ADD BUFFER KE JARAK

        kamera.init();
        kompas.init();
        sweeper.init();
        capit.init();
        kaki.berdiri(NORMAL);
    }

    void initManualMode(){
      yaw[FRONT] = getYaw();
        
      yaw[BACK] = yaw[FRONT] + 180;
      yaw[LEFT] = yaw[FRONT] - 90;
      yaw[RIGHT] = yaw[FRONT] + 90;
     }

    void berdiri(){
        berdiri(this->tipeLangkah);
    }
    
    void berdiri(int tipeLangkah){
        kaki.berdiri(tipeLangkah);
        //reset state
        this-> movingType = STAY;
        this-> movingDirection = STAY;
        for(int i = 0; i < 4; i++){
          this->kondisiTargetJarakMin[i] = 0;
          this->kondisiTargetJarakMax[i] = 0;
        }
        this->kondisiTargetRollMin = 0;
        this->kondisiTargetRollMax = 0;
    }
    
    void maju(){
      move(MAJU, DEFAULT, this->derajatLangkah, this->tipeLangkah, this->speed);
    }

    void mundur(){
      move(MUNDUR, DEFAULT, this->derajatLangkah, this->tipeLangkah, this->speed);
    }

    void move(){
      switch(this->movingType){
        case MOVING:{
          switch(this->movingDirection){
            case MAJU:{
              maju();
              break;
            }
            case MUNDUR:{
              mundur();
              break;
            }
          }
          break;
        }
        case ROTATING:{
          switch(this->movingDirection){
            case KIRI:{
              kiri();
              break;
            }
            case KANAN:{
              kanan();
              break;
            }
            case STAY:{
              if(this->offsetDirection != 0){
                rotateToOffSet();
              }
            }
          }
          break;
        }
      }
    }
    
    void move(int action, int height, float derajat, int tipeLangkah, int speed = 10){
      //USE DEFAULT UNTUK HEIGHT BILA TIDAK MAU SPECIFY
      kaki.jalan(action, tipeLangkah, derajat, height, speed);
    }
    
    void rotate(int action, int height, int step, float derajat, int tipeLangkah, int speed = 10){
      //DEFAULT DERAJAT (15 KIRI) (16 KANAN) 5 STEP
      for(int i = 0 ; i < step ; i++){
          
          kaki.putar(action, tipeLangkah, derajat, height, speed);
          Serial.print("Rotasi 1: ");
          printCurrentYPR();
      }
    }

    //Arahkan robot ke depan, dan inisialisai value Yaw
    void checkPosition(){
      // kalo depan kosong -> (jarak jauh) langsung skip sekuens ini
      // kalo kanan kosong -> putar kanan
      // kalo kiri kosong -> putar kiri
      // kalo belakang kosong -> putar balik dari kiri / kanan sama aja

      if(jarak.jarakBelakang() >= 350){ // Berarti lagi ngadep belakang
        yaw[BACK] = getYaw();
        
        yaw[FRONT] = yaw[BACK] + 180;
        yaw[RIGHT] = yaw[BACK] - 90;
        yaw[LEFT] = yaw[BACK] + 90;

        setPos(DEFAULT, DEFAULT, DEFAULT, DEFAULT,this->derajatLangkah, DEFAULT);
      }
      else if(jarak.jarakKiri() >= 350){ // Berarti lagi ngadep kanan
        yaw[RIGHT] = getYaw();
        
        yaw[LEFT] = yaw[RIGHT] + 180;
        yaw[FRONT] = yaw[RIGHT] - 90;
        yaw[BACK] = yaw[RIGHT] + 90;

        setPos(DEFAULT, DEFAULT, DEFAULT, DEFAULT,this->derajatLangkah, DEFAULT);
      }
      else if(jarak.jarakKanan() >= 350){ // Berarti lagi ngadep kiri
        yaw[LEFT] = getYaw();
        
        yaw[RIGHT] = yaw[LEFT] + 180;
        yaw[BACK] = yaw[LEFT] - 90;
        yaw[FRONT] = yaw[LEFT] + 90;

        setPos(DEFAULT, DEFAULT, DEFAULT, DEFAULT,this->derajatLangkah, DEFAULT);
      }
      else if(jarak.jarakDepan() >= 350){ // Ngadep depan
        yaw[FRONT] = getYaw();
        
        yaw[BACK] = yaw[FRONT] + 180;
        yaw[LEFT] = yaw[FRONT] - 90;
        yaw[RIGHT] = yaw[FRONT] + 90;
      }
      state++;
    }

    //Cetak value yaw dari robot 
    void cetakYaw(){
       Serial.print("Yaw Value: ");
       Serial.print("F ");
       Serial.print(yaw[0]); //depan
       Serial.print(", ");
       Serial.print("L ");
       Serial.print(yaw[1]); //kiri
       Serial.print(", ");
       Serial.print("R ");
       Serial.print(yaw[2]); //kanan
       Serial.print(", ");
       Serial.print("B ");
       Serial.println(yaw[3]); //belakang
    }

    int getYaw(){
      return kompas.getCurrent().x;
    }

    int getPitch(){
      return kompas.getCurrent().y;
    }

    int getRoll(){
      return kompas.getCurrent().z;
    }
    
    int jarakDepan(){
      return jarak.jarakDepan();
    }

    int jarakBelakang(){
      return jarak.jarakBelakang();
    }

    int jarakKiri(){
      return jarak.jarakKiri();
    }

    int jarakKanan(){
      return jarak.jarakKanan();
    }
    
    //Untuk mengupdate buffer
    void readUltrasonic(){
      jarak.readAllJarak();
    }

    void getKorban(){
      getKorban(DEFAULT, this->derajatLangkah, this->tipeLangkah, this->speed);
      this->isHoldingKorban = true;
    }
    
    void getKorban(int height, float derajat, int tipeLangkah, int speed = 10){
      //USE " DEFAULT " JIKA TIDAK MAU SPECIFY HEIGHT
      //DEFAULT DERAJAT 10 NORMAL
      //DEFAULT DERAJAT 20 TINGGI

      int X, Y, W, H;
      X = Y = W = H = 0;

      delay(200);

      capit.turunLengan();
      capit.bukaCapit();

      while(1){
        X = kamera.getX();
        Y = kamera.getY();

        if(X >= 0 && X <= 125)
          rotate(KANAN, height, 1, 4, tipeLangkah, speed);
        else if (X >= 175)
          rotate(KIRI, height, 1, 3, tipeLangkah, speed);
        else
          move(MAJU, height, derajat, tipeLangkah, speed);

        W = kamera.getWidth();
        H = kamera.getHeight();

        if(W - H >= 85) break;
      }
      berdiri(NORMAL);
      delay(500);
      capit.tutupCapit();
      berdiri(tipeLangkah);
      capit.naikLenganDikit();
      for(int i = 0; i < 2; i++){
        move(MUNDUR, height, derajat, tipeLangkah, speed);
      }
      delay(50);
      capit.naikLenganLanjutan();
      state++;
    }
    void letakanKorban(){
      capit.turunLengan();
      capit.bukaCapit();
      for(int i = 0; i < 2; i++){
          move(MUNDUR, DEFAULT, this->derajatLangkah, this->tipeLangkah, this->speed);
      }
      capit.naikLengan();
      capit.tutupCapit();
      this->isHoldingKorban = false;
      state++;
    }

    void rotateToOffSet(){
      setPos();
      berdiri();
      state++;
    }
    
    void kiri(){
      rotate(KIRI, DEFAULT, 5, 11, this->tipeLangkah, this->speed);
      switch(this->direction){
        case FRONT:{
          this->direction = LEFT;
          break;
        }
        case LEFT:{
          this->direction = BACK;
          break;
        }
        case RIGHT:{
          this->direction = FRONT;
          break;
        }
        case BACK:{
          this->direction = BACK;
          break;
        }
      }
      berdiri();
      state++;
    }

    void kanan(){
      rotate(KANAN, DEFAULT, 5, 11, this->tipeLangkah, this->speed);
      switch(this->direction){
        case FRONT:{
          this->direction = RIGHT;
          break;
        }
        case LEFT:{
          this->direction = FRONT;
          break;
        }
        case RIGHT:{
          this->direction = BACK;
          break;
        }
        case BACK:{
          this->direction = LEFT;
          break;
        }
      }
      berdiri();
      state++;
    }
    
    void setPos(){
      setPos(this->direction, DEFAULT, this->offsetDirection, this->error,this->derajatLangkahSetPos, this->tipeLangkah, this->speed);
    }
    /*
     * Untuk rotasi sesuai arah atau penyearah robot sesuai kompas
     * Set DEFAULT utk index, height, set, error, tipelangkah jika tidak dicustom
     * Default VALUE
     * index = 0 Depan
     * height -> tinggi default sesuai tipeLangkah
     * set 0
     * error = 2
     * tipeLangkah -> NORMAL
     * Speed = 10, tidak perlu diberi value jika tidak ingin diubah
     */
    void setPos(int index, int height, int set, int error,float derajat, int tipeLangkah, int speed = 10){
      
      //DEFAULT value utk error
      if(error == 0) error = 2;
      
      int simpan = getYaw();
      int simpanNext = simpan;
      int putar = 0;

      while(simpanNext < yaw[index] - error + set || simpanNext > yaw[index] + error + set){
          simpanNext = getYaw();
          //Jika dari putaran kanan
          if((simpan >= 270 && simpan <= 360) && (simpanNext >= 0 && simpanNext <= 90)){
            putar++;
          }
          if((simpan >= 360 && simpan <= 450) && (simpanNext >= 270 && simpanNext <= 360)){
            putar--;
          }
          //jika dari putaran kiri
          if((simpanNext >= 270 && simpanNext <= 360) && (simpan >= 0 && simpan <= 90)){
            putar--;
          }
          if((simpanNext >= 360 && simpanNext <= 450) && (simpan >= 270 && simpan <= 360)){
            putar++;
          }
          //digunakan hanya jika dia lagi menuju ke yaw yang berada diperbatasan 360
          if(yaw[index] >= 345 && yaw[index] <= 375){
            simpanNext += putar * 360;
            if(simpanNext < 90){
              putar++;
              simpanNext += putar * 360;
            }
          }
          
          if(simpanNext < yaw[index] - error + set)
              rotate(KANAN, height, 1, derajat, tipeLangkah);

          if(simpanNext > yaw[index] + error + set)
              rotate(KIRI, height, 1, derajat, tipeLangkah);
          
          simpan = simpanNext;
      }
      //update state robot
      this->direction = index;
      this->offsetDirection = set;
    }

     //Untuk keperluan testing StandPoint
    void berdiriDebug(vec3_t standPoint){
        kaki.berdiriDebug(standPoint);
    }
    //Untuk keperluan testing StandPoint
    void moveDebug(int action, vec3_t tinggi, float derajat, vec3_t standPoint, int speed = 10){
      //USE DEFAULT UNTUK HEIGHT BILA TIDAK MAU SPECIFY
      kaki.jalanDebug(action, standPoint, derajat, tinggi, speed);
    }
    //Print kompas
    void printCurrentYPR(){
      kompas.printCurrent();
    }
    //print ultrasonic
    void printJarak(){
      jarak.printJarak();
    }
};
