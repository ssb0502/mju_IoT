// 초음파(SR04 모듈) 거리 센서 측정 
int distance;
int triggerPin = 5;
int echoPin = 4;
int ledpin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);  // 트리거 핀을 출력으로 설정
  pinMode(echoPin, INPUT);      // 에코 핀을 입력으로 설정
  //pinMode(16, OUTPUT);  // 트리거 핀을 출력으로 설정
  pinMode(ledpin, OUTPUT);

}

void loop() {
  // 트리거 핀으로 10 us의 펄스를 발생
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  //에코 핀 입력으로부터 거리를 cm 단위로 계산
  distance = pulseIn(echoPin, HIGH) / 58;
  Serial.println("Distance(cm) = " + String(distance));
  delay(1000);

 if(distance<=30){
   digitalWrite(ledpin, HIGH);
   delay(3000);
  }
  else digitalWrite(ledpin, LOW);

  delay(1000);
  
}
