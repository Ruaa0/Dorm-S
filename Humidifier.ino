#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <Servo.h>
RF24 radio(10, 9);               // 分别定义CE和CSN所连接的引脚
RF24Network network(radio);      // 在网络中添加radio
const uint8_t this_node = 02;
const uint8_t node00 = 00;// 设置节点的八进制地址
const uint8_t node02 = 02; 
int pre;
const int a=7;//继电器引脚
int pos = 0;

unsigned long incomingData;

Servo myservo; 

void setup() {
  myservo.attach(6);
  pinMode(a,OUTPUT);
  
  Serial.begin(9600);
  
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); // 信道，节点地址
  radio.setDataRate(RF24_2MBPS);
}

void loop() {
  network.update();
  Serial.println(network.available());
  while ( network.available() ) {     // 判断是否有待传入的数据
    RF24NetworkHeader header1;
    Serial.println(header1.from_node);
    network.read(header1, &incomingData, sizeof(incomingData)); // 读取传入数据
    Serial.print("00节点有数据:");
    Serial.println(incomingData);
    }

 while(incomingData==5&&pre!=incomingData){
    delayMicroseconds(2);
    digitalWrite(a,HIGH);
delay(500);
for (pos = 0; pos <= 178;pos++ ) { 
    myservo.write(pos);              
    delay(15);                       
  }
   for (pos = 178; pos >= 0;pos-- ) { 
    myservo.write(pos);              
    delay(15);                       
  }
        break;
    }
   while(incomingData==6&&pre!=incomingData){
      delayMicroseconds(2);
      digitalWrite(a,LOW);
      break;
    }
 pre=incomingData;
}                                                                                                                                                                                               
