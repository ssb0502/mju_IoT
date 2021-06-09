#include <Wire.h>
#include <Servo.h>

int MPU_Address = 0x68;
int16_t Tmp;
int pos;
 
#define servoPin 2 //D4 (D1,D2:MPU6050)
Servo servo;

void servofun(){
  
for (pos = 0; pos <= 180; pos += 2) { 
    servo.write(pos);              
    delay(15);                       
  }
servo.write(0);
  
  }
void setup() {
  Wire.begin(4,5);
  Wire.beginTransmission(MPU_Address);
  Wire.write(0x6B);
  Wire.write(1);
  Wire.endTransmission(true);
  Serial.begin(9600);
  servo.attach(servoPin);
  
  delay(2000);

}

void loop() {   
  Tmp=0;
  float temperature=0;
  
  Wire.beginTransmission(MPU_Address);
  Wire.write(0x41);
  Wire.endTransmission();
  Wire.requestFrom(MPU_Address, 2, true);
  Tmp = Wire.read() << 8 | Wire.read();
  temperature=Tmp/340.00+36.53;

  Serial.printf("Temperature :%f\r\n", temperature);
  //Serial.printf("pos :%f\r\n", pos);

  
  if(temperature>=30.0 && temperature<=32.0)
  {
   servofun();                   
  }
  
  else
  {    
    delay(15);                      
  }
  
  delay(6000);

}
