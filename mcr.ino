#include <Servo.h>
Servo myservo;

#define SW 2
#define LED_GREEN 3
#define LED_RED 4
#define MCR_SW 5

bool isMove = false;
bool flex = false;
int counter = 0;

int mcrFailureCount = 0;
unsigned long startTime = 0;
bool mcrStatus = digitalRead(MCR_SW);


uint32_t gainTime = 5000;
int gainCounter = 10;


void setup() {

  Serial.begin(115200);
  myservo.attach(9);
  pinMode(MCR_SW, INPUT);
  pinMode(SW, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);

  myservo.write(0);
}

void loop() {
  if (digitalRead(SW) == HIGH) {
    digitalWrite(LED_GREEN, LOW);
  } else {
    digitalWrite(LED_GREEN, HIGH);
    myservo.write(0);
  }

  run();
  Serial.println(digitalRead(MCR_SW));
  
}
void run() {
  if (digitalRead(SW) == HIGH) {
    bool mcrStatus = digitalRead(MCR_SW);

    if (mcrStatus == LOW) {
      if (isMove == false) {
        startTime = millis(); 
        isMove = true;        
        counter = 0;       
      }

      if (flex == false) {
        counter++;         
        flex = true;      
      }
    } else {
      flex = false;      
    }

    if (isMove == true && millis() - startTime >= gainTime) {
      moveServo();        
      isMove = false;     
    }

    if (isMove == true && counter >= gainCounter) {
      moveServo();         
      isMove = false;
    }
  }
}


void moveServo() {
  myservo.write(0);
  delay(500);
  myservo.write(90);
  delay(500);
  
}
