#define coxaLength 25 // Panjang Coxa dalam milimeter
#define fermurLength 50 // Panjang Fermur dalam milimeter
#define thibiaLength 60 // Panjang Tibia dalam milimeter

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
    
    float l = sqrt(target.x * target.x + target.z * target.z);
    float x0 = l - coxaLength;
    float thetaF1 = atan2(target.y, x0);
    
    float a = sqrt(pow(x0, 2) + pow(target.y, 2));
    float thetaF2 = acos((pow(fermurLength, 2) + pow(a, 2) - pow(thibiaLength, 2) ) / (2 * a * fermurLength));
    float thetaF = (thetaF1 + thetaF2)* 180/PI;
    float thetaT = (acos((pow(fermurLength, 2) + pow(thibiaLength, 2) - pow(a, 2) )/ (2 * thibiaLength * fermurLength)) * 180/PI - 90);
    
    //normalisasi
    thetaC = 90 - thetaC;
    // thetaF = 0 - thetaF - 45; // TIDAK PERLU
    thetaT =  0 - (thetaT - 90) - 45; 

    return {thetaC,thetaF,thetaT};
}

int mapServo(int deg){
    // Mapping dari sudut ke derajat servo

    return map(deg, 0, 150, 512, 0);
}

ArduinoQueue<vec3_t> trajectory(vec3_t P1,vec3_t P2,vec3_t P3,vec3_t P4, float t){
    // Untuk trajectory

    ArduinoQueue<vec3_t> result(1/t + 3);
    float mult = t;
    
    while(t<1){
        vec3_t Pt = pow(1-t,3) * P1 + 3*t*pow(1-t,2) * P2 + 3*t*t*(1-t) * P3 + pow(t,3) * P4;
        result.enqueue(Pt);
        t += mult;
    }
    
    return result;
}

ArduinoQueue<vec3_t> bukanTrajectory(vec3_t P1,vec3_t P2,vec3_t P3){
    ArduinoQueue<vec3_t> result(3);
    
    result.enqueue(P1);
    result.enqueue(P2);
    result.enqueue(P3);

    return result;
}