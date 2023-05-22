#define coxaLength 26 // Panjang Coxa dalam milimeter 25
#define fermurLength 53 // Panjang Fermur dalam milimeter 50
#define thibiaLength 60 // Panjang Tibia dalam milimeter 60

vec3_t rotateMatrix(vec3_t from, float deg){
    // Fungsi rotasi matriks

    float rad = deg * PI / 180.0;

    float x = (cos(rad) * from.x) - (from.z * sin(rad));
    float z = (cos(rad) * from.z) + (from.x * sin(rad));

    from.x = x;
    from.z = z;

    return from;
}

vec3_t InversKinematik(vec3_t target){
    // Fungsi Invers Kinematik
    
    float thetaC = atan2(target.z, target.x) * 180/PI;
    
    float l = sqrt(pow(target.x, 2) + pow(target.z, 2));
    float x0 = l - coxaLength;
    float thetaF1 = atan2(target.y, x0);
    
    float a = sqrt(pow(x0, 2) + pow(target.y, 2));
    
    float thetaF2 = acos((pow(fermurLength, 2) + pow(a, 2) - pow(thibiaLength, 2) ) / (2 * a * fermurLength));
    float thetaF = (thetaF1 + thetaF2)* 180/PI;

    // float thetaT = (acos((pow(fermurLength, 2) + pow(thibiaLength, 2) - pow(a, 2) )/ (2 * thibiaLength * fermurLength)) * 180/PI - 90);
    
    // Calculate the angle between the femur and tibia links
    float thetaT = acos((pow(fermurLength, 2) + pow(thibiaLength, 2) - pow(a, 2)) / (2 * thibiaLength * fermurLength)) * 180 / PI;

    thetaT = (target.y > 0 ? thetaT - 90 : thetaT + 90) - 45;

    //normalisasi
    thetaC = 90 - thetaC;
    // thetaF = 0 - thetaF - 45; // TIDAK PERLU
    // thetaT =  0 - (thetaT - 90) - 45; // TIDAK DIPAKAI DIGANTIKAN DENGAN TERNARY OPERATOR DIATAS

    return {thetaC,thetaF,thetaT};
}

int mapServo(int deg){
    // Mapping dari sudut ke derajat servo

    return map(deg, 0, 150, 512, 0);
}

ArduinoQueue<vec3_t> trajectory(vec3_t P1,vec3_t P2,vec3_t P3){
    ArduinoQueue<vec3_t> result(3);
    
    result.enqueue(P1);
    result.enqueue(P2);
    result.enqueue(P3);

    return result;
}

 // ini dibawah sebelumnya untuk nyari standpoint yg pas :v
void cariStandpoint(){
  Serial.println("Mulai");
  for(int i = -200 ; i < 0 ; i++){
      for(int j = 0 ; j < 200 ; j++){
          vec3_t standPointTinggi = {0, i, j};
          vec3_t deggs = InversKinematik(standPointTinggi);
          /*
           * Gunakan relasi y dan z berupa y = 90 - z untuk mencari standPoint
           * Contoh: y = 30 & z = 60
          */
          if((deggs.y > 10 && deggs.y < 80) && deggs.x == 0 && (deggs.z > (90 - deggs.y - 2) && deggs.z < (90 - deggs.y + 2))){
            Serial.print("TEST "); Serial.println(i); Serial.print(" i: "); Serial.print(i); Serial.print(" j: "); Serial.print(j); Serial.println();          
            Serial.println();
            Serial.print(deggs.x);
            Serial.print(" , ");
            Serial.print(deggs.y);
            Serial.print(" , ");
            Serial.println(deggs.z);
          }
      }
  }
  Serial.println("Selesai");
}

//ArduinoQueue<vec3_t> trajectory(vec3_t P1,vec3_t P2,vec3_t P3,vec3_t P4, float t){
//    // Untuk trajectory
//
//    ArduinoQueue<vec3_t> result(1/t + 3);
//    float mult = t;
//    
//    while(t<1){
//        vec3_t Pt = pow(1-t,3) * P1 + 3*t*pow(1-t,2) * P2 + 3*t*t*(1-t) * P3 + pow(t,3) * P4;
//        result.enqueue(Pt);
//        t += mult;
//    }
//    
//    return result;
//}
