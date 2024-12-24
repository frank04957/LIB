#include <Servo.h>
Servo myservo;

#define SW 2
#define LED_GREEN 3
#define LED_RED 4

uint32_t sTime = 0;
bool flag = false;


int time = 20;
int emerTime = 5;

void setup() {
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

  if (digitalRead(SW) == LOW && flag == false) {
    digitalWrite(LED_GREEN, LOW);

    flag = true;
    sTime = millis();
  } else if (digitalRead(SW) == HIGH) {
    myservo.write(0);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    flag = false;
  }

  if (millis() - sTime >= (time * 1000) && flag == true) {
    moveServo();
    flag = false;
    digitalWrite(LED_RED, HIGH);
  } else if (millis() - sTime >= ((time * 1000) - (emerTime * 1000)) && flag == true) {
    digitalWrite(LED_RED, LOW);
  }
  Serial.println(digitalRead(SW));
  Serial.print(", ");
  Serial.println(millis() - sTime);
}

void moveServo() {
  myservo.write(0);
  delay(500);
  myservo.write(90);
  delay(500);
}