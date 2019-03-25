
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include<Mouse.h>

#define LBUT  A0 
#define RBUT  A1 

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;

int angleToDistance(int a) {
  if (a < -80) {
    return -40;
  }
  else if (a < -65) {
    return -20;
  }
  else if (a < -50) {
    return -10;
  }
  else if (a < -15) {
    return -5;
  }
  else if (a < -5) {
    return -1;
  }
  else if (a > 80) {
    return 40;
  }
  else if (a > 65) {
    return 20;
  }
  else if (a > 15) {
    return 10;
  }
  else if (a > 5) {
    return 1;
  }
  else {
    return 0;
  }
}

void setup() {

  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
  }
}

void loop() {
  
int left = analogRead(A0);
int right = analogRead(A1);

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  int vx = map(ax, -16000, 16000, 90, -90);
  int vy = map(ay, -16000, 16000, 90, -90);
  Mouse.move(angleToDistance(vx), angleToDistance(vy));
  if (left >=350) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
      Serial.println("LEFT CLICK");
      Serial.println(left);
      delay(20);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
  if (right <=400) {
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
      Serial.println("RIGHT CLICK");
      Serial.println(right);
      delay(20);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }
  delay(20);
}
