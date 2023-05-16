#include "Arduino.h"
#include "KakiGroup.h"
#include "Capit.h"
#include "SensorJarakGroup.h"
#include "Kamera.h"
#include "Sweeper.h"
#include "Kompas.h"

class Robot{
  public:
    KakiGroup kaki;
    SensorJarakGroup jarak;
    Kamera kamera;
    Sweeper sweeper;
    Capit capit;
    Kompas kompas;

    double yaw[4] = {0, 0, 0, 0}; // simpan lokasi arah robot menggunakan kompas

    /*
      yaw[0] -> depan
      yaw[1] -> kiri
      yaw[2] -> kanan
      yaw[3] -> belakang
    */
    
    Robot(){
      
    }

    void init(){
        kaki = KakiGroup();
        jarak = SensorJarakGroup();

        kamera.init();
        kompas.init();
        sweeper.init();
        delay(200);
        capit.init();
        delay(700);
        kaki.berdiri();
    }

    void berdiri(){
        kaki.berdiri();
    }

    void berdiriTinggi(){
        kaki.berdiriTinggi();
    }

    void maju(){
        kaki.jalan(MAJU);
    }

    void majuCustom(int sudut){
        kaki.jalanCustom(MAJU, sudut);
    }


    void majuTinggi(){
        kaki.jalanTinggi(MAJU);
    }

    void majuTinggiCustom(int heigth, int sudut){
        kaki.jalanTinggiCustom(MAJU, heigth, sudut);
    }

    void mundur(){
        kaki.jalan(MUNDUR);
    }

    void mundurCustom(int sudut){
        kaki.jalanCustom(MUNDUR, sudut);
    }
    
    void mundurTinggi(){
        kaki.jalanTinggi(MUNDUR);
    }

    void putarKiri(){
      for(int i = 0 ; i < 5 ; i++){
          kaki.putar(15, KIRI);
      }
    }

    void putarKanan(){
      for(int i = 0 ; i < 5 ; i++){
          kaki.putar(16, KANAN);
        }
    }   

    void checkPosition(){
      // kalo depan kosong -> (jarak jauh) langsung skip sekuens ini
      // kalo kanan kosong -> putar kanan
      // kalo kiri kosong -> putar kiri
      // kalo belakang kosong -> putar balik dari kiri / kanan sama aja

      /*
          yaw[0] -> depan
          yaw[1] -> kiri
          yaw[2] -> kanan
          yaw[3] -> belakang
      */

      if(jarak.jarakBelakang() >= 250){ // Berarti lagi ngadep belakang
        yaw[3] = kompas.getCurrent().x;
        
        if(yaw[3] < 0) yaw[0] = yaw[3] + 180;
        else if(yaw[3] > 0) yaw[0] = yaw[3] - 180;
        
        yaw[2] = yaw[3] - 90;
        yaw[1] = yaw[3] + 90;

        putarKiri();
        for(int i = 0 ; i < 2 ; i++) kaki.jalan(MAJU);
        kaki.berdiri();
        putarKiri();
        kaki.putar(14, KIRI);
        kaki.berdiri();
      }
      else if(jarak.jarakKiri() >= 245){ // Berarti lagi ngadep kanan
        yaw[2] = kompas.getCurrent().x; 
        
        if(yaw[2] < 0) yaw[1] = yaw[2] + 180;
        else if(yaw[2] > 0) yaw[1] = yaw[2] - 180;
        
        yaw[0] = yaw[2] - 90;
        yaw[3] = yaw[2] + 90;

        putarKiri();
      }
      else if(jarak.jarakKanan() >= 250){ // Berarti lagi ngadep kiri
        yaw[1] = kompas.getCurrent().x; 
        
        if(yaw[1] < 0) yaw[2] = yaw[1] + 180;
        else if(yaw[1] > 0) yaw[2] = yaw[1] - 180;
        
        yaw[3] = yaw[1] - 90;
        yaw[0] = yaw[1] + 90;

        putarKanan();
      }
      else { // Ngadep depan
        yaw[0] = kompas.getCurrent().x;
        
        if(yaw[0] < 0) yaw[3] = yaw[0] + 180;
        else if(yaw[0] > 0) yaw[3] = yaw[0] - 180;
        
        yaw[1] = yaw[0] - 90;
        yaw[2] = yaw[0] + 90;

        return;
      }
    }

    void getKorban(){
      int X, Y, W, H;
      X = Y = W = H = 0;

      delay(200);

      capit.turunLengan();
      capit.bukaCapit();

      while(1){
        X = kamera.getX();
        Y = kamera.getY();

        if(X >= 0 && X <= 125)
          kaki.putar(4, KANAN);
        else if (X >= 175)
          kaki.putar(3, KIRI);
        else 
          kaki.jalan(MAJU);

        W = kamera.getWidth();
        H = kamera.getHeight();

        if(W - H >= 85) break;
      }

      delay(500);
      capit.tutupCapit();
      capit.naikLenganDikit();
      mundur();
      delay(50);
      capit.naikLenganLanjutan();
    }

    void getKorbanTinggi(){
      int X, Y, W, H;
      X = Y = W = H = 0;

      delay(200);

      capit.turunLengan();
      capit.bukaCapit();

      while(1){
        X = kamera.getX();
        Y = kamera.getY();

        if(X >= 0 && X <= 125)
          kaki.putarTinggi(4, KANAN);
        else if (X >= 175)
          kaki.putarTinggi(3, KIRI);
        else 
          kaki.jalanTinggi(MAJU);

        W = kamera.getWidth();
        H = kamera.getHeight();

        if(W - H >= 85) break;
      }
      
      berdiri();
      delay(500);
      capit.tutupCapit();
      berdiriTinggi();
      mundurTinggi();
      delay(50);
      capit.naikLengan();
    }

    void fixPos(int index){
      double simpan = 0;

      do{
          simpan = kompas.getCurrent().x;

          if(simpan < yaw[index] - 2)
              kaki.putar(3, KANAN);
          
          if(simpan > yaw[index] + 2)
              kaki.putar(3, KIRI);
          
      }while(simpan < yaw[index] - 2 || simpan > yaw[index] + 2);
    }

    void fixPosCustom(int index, int custom){
      double simpan = 0;

      do{
          simpan = kompas.getCurrent().x;

          if(simpan < yaw[index] - custom)
              kaki.putar(3, KANAN);
          
          if(simpan > yaw[index] + custom)
              kaki.putar(3, KIRI);
          
      }while(simpan < yaw[index] - custom || simpan > yaw[index] + custom);
    }

    void setPos(int index, int custom){
      double simpan = 0;

      do{
          simpan = kompas.getCurrent().x;

          if(simpan < yaw[index] - 2 + custom)
              kaki.putar(6, KANAN);
          
          if(simpan > yaw[index] + 2 + custom)
              kaki.putar(7, KIRI);
          
      }while(simpan < yaw[index] - 2 + custom || simpan > yaw[index] + 2 + custom);
    }

    void fixPosTinggi(int index){
      double simpan = 0;

      do{
          simpan = kompas.getCurrent().x;

          if(simpan < yaw[index] - 3.5)
              kaki.putarTinggi(4, KANAN);
          
          if(simpan > yaw[index] + 3.5)
              kaki.putarTinggi(5, KIRI);
          
      }while(simpan < yaw[index] - 3.5 || simpan > yaw[index] + 3.5);
    }

    void fixPosTinggiCustom(int index, int custom){
      double simpan = 0;

      do{
          simpan = kompas.getCurrent().x;

          if(simpan < yaw[index] - custom)
              kaki.putarTinggi(6, KANAN);
          
          if(simpan > yaw[index] + custom)
              kaki.putarTinggi(7, KIRI);
          
      }while(simpan < yaw[index] - custom || simpan > yaw[index] + custom);
    }

    void setPosTinggi(int index, int custom){
      double simpan = 0;

      do{
          simpan = kompas.getCurrent().x;

          if(simpan < yaw[index] - 3.2 + custom)
              kaki.putarTinggi(6, KANAN);
          
          if(simpan > yaw[index] + 3.2 + custom)
              kaki.putarTinggi(7, KIRI);
          
      }while(simpan < yaw[index] - 3.2 + custom|| simpan > yaw[index] + 3.2 + custom);
    }

    void point1(){
      int langkah = 0;

      // Langkah ke depan korban 1
      while(1){
        if(jarak.jarakBelakang() >= 400)
            break;

        if(langkah % 3 == 0 && langkah != 0)
          fixPos(0);
        
        maju();
        langkah++;
      }
      
      berdiri();

      // Putar arah korban
      putarKiri();
      fixPos(1);

      berdiri();

      // Mundur untuk meluruskan
      while(1) {
        mundur();
        if(jarak.jarakBelakang() <= 380) 
            break;
      }

      // Mengambil korban
      getKorban();
      
      // Mundur ke titik tertentu agar kaki dapat masuk ke area retak
      langkah = 0;
      while(1) {
        
        if(jarak.jarakBelakang() <= 410)
            break;
        if(langkah % 3 == 0 && langkah != 0)
            fixPos(1);
         mundurCustom(5);   
        langkah++; 
      }

      berdiri();

      // Putar kanan dan luruskan
      putarKanan();
      fixPos(0);

      langkah = 0;

      while(1){
        if(jarak.jarakBelakang() >= 430)
            break;

        if(langkah % 3 == 0 && langkah != 0)
          fixPos(0);
      
        majuCustom(5);
        langkah++;
      }
      fixPos(0);
    }

    void point2(){
      int langkah = 0;

      berdiriTinggi();
      delayMicroseconds(100);

      while(1){
        if(kompas.getCurrent().z < -13.5)
            break;
        if(langkah % 3 == 0 && langkah != 0){
            fixPosTinggiCustom(0, 15);
        }
        
        majuTinggiCustom(45, 17);
        langkah++;
      }

      berdiri();
      langkah = 0;

      while(1) {
        if(kompas.getCurrent().z > -1.5) 
            break;
        if(langkah % 3 == 0 && langkah != 0) 
          fixPos(0);

        maju();
        langkah++;
      }
    }

    void point3(){
      berdiriTinggi();
      fixPosTinggi(0);
      berdiriTinggi();

      int langkah = 0;

      // while(1) {
      //   if(jarak.jarakKiri() >= 60) 
      //     break;

      //   if(langkah % 3 == 0 && langkah != 0) 
      //     fixPosTinggi(0);

      //   majuTinggi();
      //   langkah++;
      // }
      
      // langkah = 0;

      while(1) {
        if(langkah % 3 == 0 && langkah != 0){
          fixPosTinggi(0);
          if(jarak.jarakDepan() <= 180) 
            break;
        }
        
        majuTinggiCustom(40, 5);
        langkah++;
      }
    
      setPosTinggi(0, 25);

      berdiriTinggi();
      
      capit.turunLengan(); 
      capit.bukaCapit();
      delay(200);

      capit.naikLengan();
      capit.tutupCapit();
      
      setPosTinggi(1, 0);
    }

    void point4(){
      berdiriTinggi();

      int langkah = 0;
      while(1) {
        if(langkah % 3 == 0 && langkah != 0){
          fixPosTinggi(0);
          if(jarak.jarakDepan() <= 200) 
            break;
        }
        
        majuTinggiCustom(40, 12);
        langkah++;
      }

      putarKiri();

      berdiriTinggi();

      getKorbanTinggi();

      berdiriTinggi();

      for(int i = 0 ; i < 2 ; i++) mundurTinggi();

      putarKanan();

      while(jarak.jarakDepan() > 80) majuTinggi();

      // algo taruh

      for(int i = 0 ; i < 2 ; i++) mundurTinggi();

      int tes = 4;

      while(tes-- > 0) kaki.putar(6, KIRI);

      while(jarak.jarakDepan() > 120) majuTinggi();

      berdiri();
    }
};