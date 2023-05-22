class KalmanFilter {
private:
  float Q; // Process noise covariance
  float R; // Measurement noise covariance
  float P; // Estimate error covariance
  float K; // Kalman gain
  float x; // Estimated value

public:
  KalmanFilter(float processNoise, float measurementNoise, float estimateError) {
    Q = processNoise;
    R = measurementNoise;
    P = estimateError;
    x = 0; // Initial estimate is set to 0
  }

  float updateEstimate(float measurement) {
    // Prediction step
    float predictedX = x;
    float predictedP = P + Q;

    // Update step
    K = predictedP / (predictedP + R);
    x = predictedX + K * (measurement - predictedX);
    P = (1 - K) * predictedP;

    return x;
  }
};
