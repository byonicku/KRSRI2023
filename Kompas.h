// Harus ada library MPU6050.h, Wire.h, I2Cdev.h
#include <MPU6050.h>
#include <Wire.h>
#include <I2Cdev.h>

class Kompas{
    private:
        MPU6050 compass;

    public:
        Kompas(){
             
        }

        void init(){
            // Untuk menginisialisasi Kompas
            compass.initialize();
        }

        bool testConnection(){
          // Test koneksi dari compass
          Serial.println("Testing device connections...");
          Serial.println(compass.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

          return compass.testConnection();
        }

        vec3_t getCurrent(){
          // Untuk mendapatkan nilai sudut dari kompas
          return {compass.getRotationX(), compass.getRotationY(), compass.getRotationZ()};
        }
};