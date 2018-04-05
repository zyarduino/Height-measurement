float cm;
String RetString, Strname;
int TrigPin = 2,
    EchoPin = 3,
    StrSeg,
    PoleHeight, //杆子高度
    DelayTime; //延时时间
      

void setup(){
  Serial.begin(9600);
  Serial.println("begin");
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
 while (true){
    RetString = Serial.readString(); 
    StrSeg = RetString.indexOf(':');
    if (StrSeg != "-1"){
      Serial.println(StrSeg);
      Strname = RetString.substring(0, StrSeg);
      Serial.println(RetString);
      Serial.println(Strname);
      if(Strname == "Height"){
          PoleHeight  =  RetString.substring(StrSeg + 1, -1).toInt();
          Serial.println("Height Setted: " + String(PoleHeight) + "cm");
      }
       if(Strname == "DelayTime"){
          DelayTime  =  RetString.substring(StrSeg + 1, -1).toInt();
          Serial.println("DelayTime Setted: " + String(DelayTime) + "ms");
       }
    }
    if (PoleHeight != 0 && DelayTime != 0) {
      Serial.println("Data has Setted! PoleHeight is " + String(PoleHeight) + "cm and DelayTime is " + String(DelayTime) + "ms");  
      break;
    }
    delay(50);
  }
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
  delay(DelayTime); 
}
