//Vector
#include <vector_type.h>

//Arduino
#include <Arduino.h>
#include <math.h> 
#include <ArduinoQueue.h>

// Invers Kinematik
#include "InversKinematik.h"

//Kamera
#include <Pixy2.h>

// Kompas dan Gyro
#include <MPU6050.h>
#include <Wire.h>
#include <I2Cdev.h>

// Servo Biasa
#include <Servo.h>

// AX12A Servo
#include <SoftwareSerial.h>
#include "AX12A.h"
#define DirectionPin   (10u)
#define BaudRate      (1000000ul)
#define ID (1u)

//Movement
#define MAJU 1
#define MUNDUR -1

#define KANAN 1
#define KIRI -1

#define GRUP1 1
#define GRUP2 -1

#define DEPAN 1
#define TENGAH 2
#define BELAKANG 3

#define ORANGE 1
#define PUTIH 2