#include "KalmanFilter.h"

class SensorJarak {
  private:
    int echoPin;
    int trigPin;
  
  public:
    SensorJarak(int echoPin, int trigPin){
      this->echoPin = echoPin;
      this->trigPin = trigPin;

      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    float bacaJarak() {
      int jarak = getDistance();
      while(jarak == 0 || jarak > 1000){
        jarak = getDistance();
      }
      return jarak;
    }

    float getDistance(){
      resetTrigger();
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      float duration = pulseIn(echoPin, HIGH);
      return duration * 0.034 / 2 * 10;
    }
    
    void resetTrigger() {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
    }
};
