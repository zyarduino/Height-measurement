float cm, Height;
String RetString, Strname, PoleHeight_String;
int TrigPin = 2,
    EchoPin = 3,
    StrSeg,
    PoleHeight, //杆子高度
    DelayTime; //延时时间
      

void setup(){
  Serial.begin(9600);
  printinfo("begin");
  pinMode(TrigPin, OUTPUT); //设置Pin口模式
  pinMode(EchoPin, INPUT);
 while (true){
    RetString = Serial.readString(); 
    StrSeg = RetString.indexOf(':'); //找到 ":" 的位置
    if (StrSeg != "-1"){  // 也就是有这玩意儿的时候

      Strname = RetString.substring(0, StrSeg); //获取位置0到:间的字符串

      if(Strname == "Height"){

        PoleHeight_String  =  RetString.substring(StrSeg + 1, -1); //由于这玩意儿没法赋值给string，暂时瞎开一个变量凑合着用

        if (PoleHeight_String == "auto"){ //自动模式时取5次当前位置的高度
          printinfo("Height Auto Mode Started.");

          for(int count = 1;count<=5;count++){
              MeasureHeight();
              Height += cm;
              printinfo("Count(" + String(count) + "): " + String(cm) + "cm Added");
              delay(50);
          }

          PoleHeight = Height / 5;  
        }else {
          PoleHeight = PoleHeight_String.toInt(); //int != string，要转换一波
        }
          printinfo("Height Setted: " + String(PoleHeight) + "cm");
      }


       if(Strname == "DelayTime"){
          DelayTime  =  RetString.substring(StrSeg + 1, -1).toInt();
          printinfo("DelayTime Setted: " + String(DelayTime) + "ms");
       }

    }
//    if (PoleHeight != 0 && DelayTime != 0) {
      if(Strname == "finish"){
        printinfo("Data has Setted! PoleHeight is " + String(PoleHeight) + "cm and DelayTime is " + String(DelayTime) + "ms");  
        break;
      }
      
    delay(50);
  }
}

void loop(){
  MeasureHeight();
  cm = PoleHeight - (int(cm * 100)) / 100; //减去距离得到身高
  Serial.println("Height is: " +  String(cm) + "cm"); 
  delay(DelayTime); 
}

void MeasureHeight(){
  digitalWrite(TrigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  cm = pulseIn(EchoPin, HIGH) / 58; //将回波时间换算成cm

  return cm;
}

void printinfo(String str){
  Serial.println("[INFO] " + str);
}

