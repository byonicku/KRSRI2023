class SensorJarak {
  private:
    int echoPin;
    int trigPin;
    
    float *buffer;
    int bufferSize;
    int bufferIndex;
  
  public:
    SensorJarak(int echoPin, int trigPin, int bufferSize) {
      this->echoPin = echoPin;
      this->trigPin = trigPin;
      this->bufferSize = bufferSize;
      
      buffer = new float[bufferSize];
      bufferIndex = 0;

      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    float bacaJarak() {
      resetTrigger();
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      float duration = pulseIn(echoPin, HIGH);
      int jarak = duration * 0.034 / 2 * 10;

      // Add reading to buffer and calculate moving average
      buffer[bufferIndex] = jarak;
      bufferIndex = (bufferIndex + 1) % bufferSize;
      float average = 0;

      for (int i = 0; i < bufferSize; i++) 
        average += buffer[i];
      
      average /= bufferSize;

      return average;
    }

    void resetTrigger() {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
    }
};