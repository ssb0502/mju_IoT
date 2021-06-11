#include <Wire.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <AnotherIFTTTWebhook.h>

#define servoPin 2  //D4(D1,D2:MPU)
#define triggerPin 15  //D8
#define echoPin 13  //D7
#define ledPin 12

int MPU_Address = 0x68;
int16_t Tmp;
int pos;
int distance;

Servo servo;

void servofunc()
{
  for(pos=0; pos<=150; pos+=2)
  {
    servo.write(pos);
    delay(10);
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
  pinMode(triggerPin, OUTPUT);  // 트리거 핀을 출력으로 설정
  pinMode(echoPin, INPUT);      // 에코 핀을 입력으로 설정
  //pinMode(16, OUTPUT);  // 트리거 핀을 출력으로 설정
  pinMode(ledPin, OUTPUT);
    
  Serial.begin(9600);
  WiFi.begin("iPhone","19980502");
  while(1)
  {
    if(WiFi.status()!=WL_CONNECTED) delay(500);
    else break;
  }
  Serial.printf("CONNECT!\r\n");
}

void loop() {
  Tmp=0;
  float temperature=0;
  char Buffer[200];
  
  Wire.beginTransmission(MPU_Address);
  Wire.write(0x41);
  Wire.endTransmission();
  Wire.requestFrom(MPU_Address, 2, true);
  Tmp = Wire.read() << 8 | Wire.read();
  temperature=Tmp/340.00+36.53;

  // 트리거 핀으로 10 us의 펄스를 발생
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  //에코 핀 입력으로부터 거리를 cm 단위로 계산
  distance = pulseIn(echoPin, HIGH) / 58;
  Serial.println("Distance(cm) = " + String(distance));
  delay(1000);
  Serial.printf("Temperature :%f\r\n", temperature);
  //Serial.printf("pos :%f\r\n", pos);

  //30cm 이하로 거리가 측정
  if(distance<=30){
   digitalWrite(ledPin, HIGH);
   
    //정상체온일때
    if(temperature>=30.0 && temperature<=36.5)
    {
     servofunc();                   
    }

    //정상체온 아닐때
    else{ 
     snprintf(Buffer, sizeof(Buffer), "%d", temperature);
     send_webhook("Temperature", "cX8K0ynAZZJVf6_7UGgQVK",Buffer,"","");
     delay(15);
    }
     
   delay(3000);
  }
  else digitalWrite(ledPin, LOW); 
  delay(10000);
}
