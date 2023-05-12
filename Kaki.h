class Kaki{
  private:
    int coxaID; // ID COXA
    int fermurID; // ID FERMUR
    int thibiaID; // ID THIBIA
    int pos; // KIRI / KANAN
    int grup; // GRUP 1 / 2
    int letak; // DEPAN / TENGAH / BELAKANG
    vec3_t standPoint; // Titik berdiri semut
    vec3_t standPointTinggi; // Titik berdiri cuma untuk jalan nendang

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
      
      this->standPoint = {0,-43,33}; // Default {0,-40,30};
      this->standPointTinggi = {0, -32, 38}; // -37, 43 //-40 30
      
      // if(letak == DEPAN)
      //   this->standPoint = rotateMatrix(this->standPoint, 15 * KIRI * this->pos);
      // else if(letak == BELAKANG)
      //   this->standPoint = rotateMatrix(this->standPoint, 15 * KANAN * this->pos);

      // Sudah di test dan hasil lebih baik tanpa rotasi
    }

    void langkah(vec3_t pointMaju, vec3_t pointMundur){
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
          // pointMaju.y *= this->pos;
          moveToPoint(pointMaju);
        }
        else{
          pointMundur.x *= this->pos;
          // pointMundur.y *= this->pos;
          moveToPoint(pointMundur);
        }
        delayMicroseconds(10);
    }

    void langkahTinggi(vec3_t pointMaju, vec3_t pointMundur){
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
          // pointMaju.y *= this->pos;
          moveToPointTinggi\(pointMaju);
        }
        else{
          pointMundur.x *= this->pos;
          // pointMundur.y *= this->pos;
          moveToPointTinggi\(pointMundur);
        }
        delayMicroseconds(10);
    }

    void langkahPutar(vec3_t pointMaju, vec3_t pointMundur){
        if(this->letak == DEPAN){
          pointMaju = rotateMatrix(pointMaju, 15 * this->pos);
          pointMundur = rotateMatrix(pointMundur, 15 * this->pos);
        }
        else if(this->letak == BELAKANG){
          pointMaju = rotateMatrix(pointMaju, -15 * this->pos );
          pointMundur = rotateMatrix(pointMundur, -15 * this->pos);
        } 

        if(this->grup == GRUP1){
          moveToPoint(pointMaju);
        }
        else{
          moveToPoint(pointMundur);
        }

        delayMicroseconds(10); // default 10
    }

    void moveToPoint(vec3_t target){
        vec3_t deggs = InversKinematik(target);

        ax12a.moveSpeed(coxaID,mapServo(deggs.x), 300);
        ax12a.moveSpeed(fermurID,mapServo(deggs.y * this->pos * -1), 300);
        ax12a.moveSpeed(thibiaID,mapServo(deggs.z * this->pos), 300);
        
        // Serial.println();
        // Serial.print(deggs.x);
        // Serial.print(" , ");
        // Serial.print(deggs.y);
        // Serial.print(" , ");
        // Serial.println(deggs.z);
        // Serial.print(mapServo(deggs.x));
        // Serial.print(" , ");
        // Serial.print(mapServo(deggs.y));
        // Serial.print(" , ");
        // Serial.println(mapServo(deggs.z));
        // Serial.println();
        
        // Uncomment untuk liat X, Y, Z dari servo
    }

    void moveToPointTinggi(vec3_t target){
        // vec3_t deggs = InversKinematikTinggi(target);
        vec3_t deggs = InversKinematik(target);

        ax12a.moveSpeed(coxaID,mapServo(deggs.x), 300);
        ax12a.moveSpeed(fermurID,mapServo(deggs.y * this->pos * -1), 300);
        ax12a.moveSpeed(thibiaID,mapServo(deggs.z * this->pos), 300);
        
        // Serial.println();
        // Serial.print(deggs.x);
        // Serial.print(" , ");
        // Serial.print(deggs.y);
        // Serial.print(" , ");
        // Serial.println(deggs.z);
        // Serial.print(mapServo(deggs.x));
        // Serial.print(" , ");
        // Serial.print(mapServo(deggs.y  * this->pos * -1));
        // Serial.print(" , ");
        // Serial.println(mapServo(deggs.z * this->pos));
        // Serial.println();
        
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

    void berdiriTinggi(){
      // Mini function untuk berdiri jinjit
      moveToPointTinggi(standPointTinggi);
    }

    // ini dibawah sebelumnya untuk nyari standpoint yg pas :v
    void cariStandpointPas(){
      for(int i = -70 ; i < 70 ; i++){
          for(int j = -70 ; j < 70 ; j++){
              this->standPointTinggi = {0, i, j};
              vec3_t deggs = InversKinematik(this->standPointTinggi);
              if((deggs.y > 20 && deggs.y < 23) && deggs.x == 0 && (deggs.z > 79 && deggs.z < 81)){
                Serial.print("TEST "); Serial.println(i); Serial.print(" i: "); Serial.print(i); Serial.print(" j: "); Serial.print(j); Serial.println();          
                Serial.println();
                Serial.print(deggs.x);
                Serial.print(" , ");
                Serial.print(deggs.y);
                Serial.print(" , ");
                Serial.println(deggs.z);
                Serial.print(mapServo(deggs.x));
                Serial.print(" , ");
                Serial.print(mapServo(deggs.y * this->pos * -1));
                Serial.print(" , ");
                Serial.println(mapServo(deggs.z * this->pos));
                Serial.println();
              }
          }
      }
    }
};