class Kompas{
    private:
        MPU6050 compass;

        uint8_t fifoBuffer[64]; // FIFO storage buffer
        Quaternion q;
        VectorFloat gravity;
        float ypr[3]; 

    public:
        Kompas(){
             
        }

        void init(){
            // Untuk menginisialisasi Kompas
            compass.initialize();
            compass.setXGyroOffset(220);
            compass.setYGyroOffset(76);
            compass.setZGyroOffset(-85);
            compass.CalibrateGyro(6);
            
        }

        bool testConnection(){
          // Test koneksi dari compass
          Serial.println("Testing device connections...");
          Serial.println(compass.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

          return compass.testConnection();
        }

        void getCurrent(){
          // Untuk mendapatkan nilai sudut dari kompas
          compass.dmpGetQuaternion(&q, fifoBuffer);
          compass.dmpGetGravity(&gravity, &q);
          compass.dmpGetYawPitchRoll(ypr, &q, &gravity);
          
          Serial.print(ypr[0] * 180/M_PI);
          Serial.print(", ");
          Serial.print(ypr[1]  * 180/M_PI);
          Serial.print(", ");
          Serial.println(ypr[2] * 180/M_PI);
        }
};