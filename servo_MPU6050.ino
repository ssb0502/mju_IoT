#include <Wire.h>
#include <Servo.h>

int MPU_Address = 0x68;
int16_t Tmp, temperature;

#define servoPin 2 //D4 (D1,D2:MPU6050)
#define LedPin 16
Servo servo;

void setup() {
  Wire.begin(4,5);
  Wire.beginTransmission(MPU_Address);
  Wire.write(0x6B);
  Wire.write(1);
  Wire.endTransmission(true);
  Serial.begin(115200);
  
  //pinMode(servoPin,OUTPUT);
  servo.attach(servoPin);
  servo.write(0);
  pinMode(LedPin,OUTPUT);
  digitalWrite(LedPin,LOW);
  delay(2000);

}

void loop() {   
  Tmp=0;
  temperature=0;
  servo.write(0);
  Wire.beginTransmission(MPU_Address);
  Wire.write(0x41);
  Wire.endTransmission();
  Wire.requestFrom(MPU_Address, 2, true);
  Tmp = Wire.read() << 8 | Wire.read();
  temperature=Tmp/340.00+36.53;
  
  Serial.printf("Temperature :%d\r\n", temperature);
  
  if(33<=temperature<=38)
  {
   servo.write(120);
   delay(10000);
   servo.write(0);
  }
  else
  {
    digitalWrite(LedPin,HIGH);
    delay(2000);
    digitalWrite(LedPin,LOW);
    delay(500);
  }
  delay(5000);

}
