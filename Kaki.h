class Kaki{
  private:
    int coxaID; // ID COXA
    int fermurID; // ID FERMUR
    int thibiaID; // ID THIBIA
    int pos; // KIRI / KANAN
    int grup; // GRUP 1 / 2
    int letak; // DEPAN / TENGAH / BELAKANG

  public:    
    Kaki(){}
    
    Kaki(int coxaID,int fermurID, int thibiaID, int pos, int grup, int letak){
      // Constructor kaki untuk memasukan ID dari servo sesuai bagian kaki, posisi, group dan letak kaki
      this->coxaID = coxaID;
      this->fermurID = fermurID;
      this->thibiaID = thibiaID; 
      this->pos = pos;
      this->grup = grup;
      this->letak = letak;
    }

    void langkah(vec3_t pointMaju, vec3_t pointMundur, int speed){
      // DEFAULT DERAJAT 10
        if(this->letak == DEPAN){
          pointMaju = rotateMatrix(pointMaju, 10);
          pointMundur = rotateMatrix(pointMundur, 10);
        }
        else if(this->letak == BELAKANG){
          pointMaju = rotateMatrix(pointMaju, -10);
          pointMundur = rotateMatrix(pointMundur, -10);
        } 

        if(this->grup == GRUP1){
          pointMaju.x *= this->pos;
          moveToPoint(pointMaju, speed);
        }
        else{
          pointMundur.x *= this->pos;
          moveToPoint(pointMundur, speed);
        }
        delayMicroseconds(10);
    }

    void langkahPutar(vec3_t pointMaju, vec3_t pointMundur, int speed){ 
      // DEFAULT DERAJAT 15
        if(this->letak == DEPAN){
          pointMaju = rotateMatrix(pointMaju, 15 * this->pos);
          pointMundur = rotateMatrix(pointMundur, 15 * this->pos);
        }
        else if(this->letak == BELAKANG){
          pointMaju = rotateMatrix(pointMaju, -15 * this->pos);
          pointMundur = rotateMatrix(pointMundur, -15 * this->pos);
        } 

        if(this->grup == GRUP1){
          moveToPoint(pointMaju, speed);
        }
        else{
          moveToPoint(pointMundur, speed);
        }
        delayMicroseconds(10);
    }

    void moveToPoint(vec3_t target, int speed = 300){
        vec3_t deggs = InversKinematik(target);
        ax12a.moveSpeed(coxaID,mapServo(deggs.x), speed);
        ax12a.moveSpeed(fermurID,mapServo(deggs.y * this->pos * -1), speed);
        ax12a.moveSpeed(thibiaID,mapServo(deggs.z * this->pos), speed);
        // Uncomment untuk liat X, Y, Z dari servo
        // Serial.println();
        // Serial.print(deggs.x);
        // Serial.print(" , ");
        // Serial.print(deggs.y);
        // Serial.print(" , ");
        // Serial.println(deggs.z);
        // Serial.print(mapServo(deggs.x));
        // Serial.print(" , ");
        // Serial.print(mapServo(deggs.y * this->pos * -1));
        // Serial.print(" , ");
        // Serial.println(mapServo(deggs.z * this->pos));
        // Serial.println();   
    }

    void moveToPointSecond(vec3_t target){
        vec3_t deggs = InversKinematikSecond(target);
        ax12a.moveSpeed(coxaID,mapServo(deggs.x), 300);
        ax12a.moveSpeed(fermurID,mapServo(deggs.y * this->pos * -1), 300);
        ax12a.moveSpeed(thibiaID,mapServo(deggs.z * this->pos), 300);   
    }
    
    void init(){
        // Inisialiasasi servo ke titik 0
        // WARNING JANGAN DIGUNAKAN SAAT KAKI SEDANG BERDIRI!!!
        ax12a.move(coxaID,mapServo(0));
        ax12a.move(fermurID,mapServo(0));
        ax12a.move(thibiaID,mapServo(0));
    }
    
    void berdiri(vec3_t standPoint){
      // Mini function untuk berdiri
      moveToPoint(standPoint);
    }
};
