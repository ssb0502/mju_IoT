int distance;
int trigger =5;
int echo=4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigger,LOW);
  digitalWrite(echo,LOW);
  delay(2);

  digitalWrite(trigger,HIGH);
  delay(10);
  digitalWrite(echo,LOW);

  distance=pulseIn(echo,HIGH)/58;
  Serial.println("Distance="+String(distance));
  Serial.printf("한해인바보");
  delay(1000);

}
