#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Servo.h>
Servo myservo;

#define SW 2
#define LED_GREEN 3
#define LED_RED 4

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;  // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI


float gainPressure = 1010.0f;
bool flag = false;



unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;  // time to get serial running
  Serial.println(F("BME280 test"));

  unsigned status;

  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print(" ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print(" ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print(" ID of 0x60 represents a BME 280.\n");
    Serial.print(" ID of 0x61 represents a BME 680.\n");
    while (1)
      ;
  }

  Serial.println("-- Default Test --");

  myservo.attach(9);
  pinMode(SW, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);

  myservo.write(0);
}

void loop() {
  static bool isLocked = false; 

  if (!isLocked) { 
    if (digitalRead(SW) == HIGH && flag == false) {
      digitalWrite(LED_GREEN, LOW);
      flag = true;
    } else {
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_RED, HIGH);
      myservo.write(0);
      flag = false;
    }

    if (bme.readPressure() / 100.0F >= gainPressure && flag == true) {
      digitalWrite(LED_RED, LOW);
      delay(5000);
      moveServo();
      digitalWrite(LED_RED, HIGH);
      flag = false;

    
      isLocked = true;
    }
  }

  if(digitalRead(SW) == LOW){
    isLocked = false;
  }


  Serial.println(bme.readPressure() / 100.0F);
}



void moveServo() {
  myservo.write(0);
  delay(500);
  myservo.write(90);
  delay(500);
  
}



// void printValues() {
//   Serial.print("Temperature = ");
//   Serial.print(bme.readTemperature());
//   Serial.println(" *C");

//   Serial.print("Pressure = ");

//   Serial.print(bme.readPressure() / 100.0F);
//   Serial.println(" hPa");

//   Serial.print("Approx. Altitude = ");
//   Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
//   Serial.println(" m");

//   Serial.print("Humidity = ");
//   Serial.print(bme.readHumidity());
//   Serial.println(" %");

//   Serial.println();
// }