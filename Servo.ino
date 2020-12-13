#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <Servo.h>


RF24 radio(10, 9);               // 分别定义CE和CSN所连接的引脚
RF24Network network(radio);      // 在网络中添加radio
const uint8_t this_node = 01;
const uint8_t node00 = 00;// 设置节点的八进制地址
const uint8_t node02 = 02; 
int pre;
int pos = 0;
unsigned long incomingData;

Servo servoUp;
Servo servoDown;

void setup() {
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  
  Serial.begin(9600);
  
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); // 信道，节点地址
  radio.setDataRate(RF24_2MBPS);

  servoUp.attach(4);//Up
  servoDown.attach(5);//Down

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
    //开灯
    while(incomingData==3&&pre!=incomingData){
        for (pos = 180 ; pos >= 0 ; pos--) { 
        servoUp.write(pos);
        delay(5);
        servoDown.write(180-pos);
        delay(5);       
        }
        servoUp.write(180);//舵机动作后释放，便于用户手动操作
        servoDown.write(180);             
        break;
    }

    //关灯
    while(incomingData==4&&pre!=incomingData){
        for (pos = 180 ; pos >= 0 ; pos--) { 
        servoUp.write(180-pos);
        delay(5);
        servoDown.write(pos);
        delay(5);       
        }
        servoUp.write(180);//舵机动作后释放，便于用户手动操作
        servoDown.write(180);
        break;
    }
    pre=incomingData;
}
