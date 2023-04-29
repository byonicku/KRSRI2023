class Kaki{
  private:
    int coxaID; // ID COXA
    int fermurID; // ID FERMUR
    int thibiaID; // ID THIBIA
    int pos; // KIRI / KANAN
    int grup; // GRUP 1 / 2
    int letak; // DEPAN / TENGAH / BELAKANG
    vec3_t standPoint; // Titik berdiri semut
    vec3_t standPointSpread; // Titik berdiri laba laba

  public:    
    Kaki(){
      
    }
    
    Kaki(int coxaID,int fermurID, int thibiaID, int pos, int grup, int letak){
      // Constructor kaki untuk memasukan ID dari servo sesuai bagian kaki, posisi, group dan letak kaki

      this->coxaID = coxaID;
      this->fermurID = fermurID;
      this->thibiaID = thibiaID; 
      this->pos = pos;
      this->grup = grup;
      this->letak = letak;
      
      this->standPoint = {0,-40,30}; // Default {0,-40,30};
      
      // if(letak == DEPAN)
      //   this->standPoint = rotateMatrix(this->standPoint, 15 * KIRI * this->pos);
      // else if(letak == BELAKANG)
      //   this->standPoint = rotateMatrix(this->standPoint, 15 * KANAN * this->pos);

      // Sudah di test dan hasil lebih baik tanpa rotasi
    }

    void langkah(vec3_t pointMaju, vec3_t pointMundur){
        if(this->letak == DEPAN){
          pointMaju = rotateMatrix(pointMaju, 15);
          pointMundur = rotateMatrix(pointMundur, 15);
        }
        else if(this->letak == BELAKANG){
          pointMaju = rotateMatrix(pointMaju, -15);
          pointMundur = rotateMatrix(pointMundur, -15);
        } 

        if(this->grup == GRUP1){
          pointMaju.x *= this->pos;
          // pointMaju.y *= this->pos;
          moveToPoint(pointMaju);
        }
        else{
          pointMundur.x *= this->pos;
          // pointMundur.y *= this->pos;
          moveToPoint(pointMundur);
        }
        delay(10);
    }

    // UNTESTED
    void langkahSpread(vec3_t pointMaju, vec3_t pointMundur){
        if(this->grup == GRUP1){
          pointMaju.x *= this->pos;
          moveToPoint(pointMaju);
        }
        else{
          pointMundur.x *= this->pos;
          moveToPoint(pointMundur);
        }
        delay(20);
    }

    void moveToPoint(vec3_t target){
        vec3_t deggs = InversKinematik(target);

        ax12a.move(coxaID,mapServo(deggs.x));
        delay(10);

        ax12a.move(fermurID,mapServo(deggs.y * this->pos * -1));
        delay(10);

        ax12a.move(thibiaID,mapServo(deggs.z * this->pos));
        delay(10);

        Serial.println(deggs.x);
        Serial.println(mapServo(deggs.x));
        Serial.println(deggs.y);
        Serial.println(mapServo(deggs.y));
        Serial.println(deggs.z);
        Serial.println(mapServo(deggs.z));

        // Uncomment untuk liat X, Y, Z dari servo
    }
    
    void init(){
        // Inisialiasasi servo ke titik 0
        ax12a.move(coxaID,mapServo(0));
        ax12a.move(fermurID,mapServo(0));
        ax12a.move(thibiaID,mapServo(0));
    }
    
    void berdiri(){
        // Mini function untuk berdiri
        moveToPoint(standPoint);
    }

    // UNTESTED
    void berdiriSpread(){
        // Mini function untuk berdiri spread
        moveToPoint(standPointSpread);
    }
};