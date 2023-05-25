class SensorJarak {
  private:
    int echoPin;
    int trigPin;
    
    float *buffer;
    int bufferSize = 5;
    int bufferIndex;
  
  public:
    float jarak;
    
    SensorJarak(int echoPin, int trigPin) {
      this->echoPin = echoPin;
      this->trigPin = trigPin;
      
      buffer = new float[bufferSize];
      bufferIndex = 0;
      jarak = 0;
      
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    void bacaJarak() {
      resetTrigger();
      float duration = pulseIn(echoPin, HIGH);
      int d = duration * 0.034 / 2 * 10;

      // Add reading to buffer and calculate moving average
      buffer[bufferIndex] = d;
      bufferIndex = (bufferIndex + 1) % bufferSize;

      float average = 0;

      for (int i = 0; i < bufferSize; i++) 
        average += buffer[i];

      average += d;
      
      average /= bufferSize + 1;
      this->jarak = average;
    }

    void resetTrigger() {
      digitalWrite(trigPin, LOW);
    }

    void highTrigger(){
      digitalWrite(trigPin, HIGH);
    }
};
