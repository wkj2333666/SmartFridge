#define echoPin  1//连接D0引脚
#define trigPin  2//连接D1引脚
long duration;
int distance;
bool previousSignal = 0;
bool currentSignal = 0;
bool ShotSignal = 0;
int brigeHeight = 50; //冰箱高度
void setup() {
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(115200);
  Serial.println("HC-SR04 test");
}

void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = duration*0.034/2;
  if (distance<brigeHeight){
    currentSignal = 1;
  }else{
    currentSignal = 0;
  }
  if(currentSignal != previousSignal){
    ShotSignal = 1;
  }else{
    ShotSignal = 0;
  }
  if(ShotSignal == 1){
    Serial.println("shot");  //拍照程序
  }
  previousSignal = currentSignal;
  delay(100);
}
