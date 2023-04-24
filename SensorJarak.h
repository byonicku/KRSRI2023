class SensorJarak{
  private:
        int echoPin;
        int trigPin;

  public:
        SensorJarak(){

        }

        SensorJarak(int echoPin, int trigPin){
            // Membuat objek sensor jarak dengan pin dari parameter

            this->echoPin = echoPin;
            this->trigPin = trigPin;

            pinMode(trigPin, OUTPUT);
            pinMode(echoPin, INPUT);
        }

        int bacaJarak(){
            resetTrigger();
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            int jarak = pulseIn(echoPin, HIGH) * 0.034 / 2;
            // Rumus membaca jarak

            return jarak;
        }

        void resetTrigger(){
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
            // Reset trigger untuk menghindari error
        }
};
