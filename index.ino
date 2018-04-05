float cm;
const int TrigPin = 2,
          EchoPin = 3,
          PoleHeight = 200; //杆子高度
          

void setup(){
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop(){
  digitalWrite(TrigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  cm = pulseIn(EchoPin, HIGH) / 58; //将回波时间换算成cm

  cm = PoleHeight - (int(cm * 100)) / 100; //减去距离得到身高
  Serial.println(); 
  delay(1000); 
}
