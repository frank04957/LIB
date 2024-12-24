#include "MPU9250.h"
#include <Servo.h>

#define SW 2
#define LED_GREEN 3
#define LED_RED 4

MPU9250 mpu = MPU9250();
Servo myservo;
float x, y, z, Gdata;
unsigned long previousTime = 0;
float previousGdata = 0;



bool flag = false;

void setup(void) {
  uint8_t temp = mpu.begin();

  Serial.begin(115200);
  myservo.attach(9);
  pinMode(SW, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);

  myservo.write(0);
}
void loop() {
  // อ่านค่า Accel
  mpu.set_accel_range(RANGE_4G);
  mpu.get_accel_g();

  if (digitalRead(SW) == HIGH) {
    digitalWrite(LED_GREEN, LOW);
    flag = true;
  } else {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    myservo.write(0);
    flag = false;
  }

  x = mpu.x_g;
  y = mpu.y_g;
  z = mpu.z_g;

  Gdata = sqrt((x * x) + (y * y) + (z * z));

  if (flag == true) {

    if (Gdata <= 0.5) {
      digitalWrite(LED_RED, LOW);
      delay(5000);
      moveServo();
      digitalWrite(LED_RED, HIGH);
    }
  }

  Serial.print("Gdata: ");
  Serial.println(Gdata);

}

void moveServo() {
  myservo.write(0);
  delay(500);
  myservo.write(90);
  delay(500);
}