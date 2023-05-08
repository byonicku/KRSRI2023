#define SIZE 4

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
            int jarak = pulseIn(echoPin, HIGH) * 0.034 / 2 * 10;
            // Rumus membaca jarak

            return jarak;
        }

        void resetTrigger(){
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
            // Reset trigger untuk menghindari error
        }

        int filter() {
            int sum = 0;
            float weightSum = 0;
            int readings[SIZE];
            float weights[SIZE] = {0.4, 0.3, 0.2, 0.1};

            // Read sensor values and compute weighted sum
            for (int i = 0; i < SIZE; i++) {
              readings[i] = bacaJarak();
              sum += readings[i] * weights[i];
              weightSum += weights[i];
            }

            // Compute weighted average
            int avg = round(sum / weightSum);

            return avg;
          }
};
