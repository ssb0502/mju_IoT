#include <Wire.h>
#include <Servo.h>

int MPU_Address = 0x68;
int16_t Tmp;

#define servoPin 2 //D4 (D1,D2:MPU6050)
Servo servo;

void setup() {
  Wire.begin(4,5);
  Wire.beginTransmission(MPU_Address);
  Wire.write(0x6B);
  Wire.write(1);
  Wire.endTransmission(true);
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(0);
  delay(2000);

}

void loop() {   
  Tmp=0;
  float temperature=0;
  int servoval=0;
  servo.write(0);
  Wire.beginTransmission(MPU_Address);
  Wire.write(0x41);
  Wire.endTransmission();
  Wire.requestFrom(MPU_Address, 2, true);
  Tmp = Wire.read() << 8 | Wire.read();
  temperature=Tmp/340.00+36.53;
  
  if(33.0<=temperature<=38.5)
  {
   servoval=90;
  }
  else
  {
    servoval=180;
  }
  servo.write(servoval);
  Serial.printf("Temperature :%f\r\n", temperature);
  delay(6000);

}
