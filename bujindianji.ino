//棕色，蓝色：正（5v），负；黑色：输出；
//记得霍尔元件三裸露导线别挨着！！！！
int dir=4;
int stp=5;
int en=6;

#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
RF24 radio(10, 9);               // 分别定义CE和CSN所连接的引脚
RF24Network network(radio);      // 在网络中添加radio
const uint8_t this_node = 03;
const uint8_t node00 = 00;// 设置节点的八进制地址
const uint8_t node02 = 02; 
int pre;
int STOPleft=0;
int STOPright=0;
unsigned long incomingData;
void setup() {
  pinMode(dir,OUTPUT);
  pinMode(stp,OUTPUT);
  pinMode(en,OUTPUT);
  digitalWrite(en,LOW);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  
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
    
    while(incomingData==1&&pre!=incomingData&&STOPleft!=1){
      
      delayMicroseconds(2);
      int hleft=digitalRead(7);//霍尔元件接口
/*******************
 若磁铁靠近，8脚输入高电频，步进电机停转。
 */
      if(hleft == HIGH)
        {
          STOPleft=1;
        }
      else
        {
        digitalWrite(dir,LOW);
        digitalWrite(stp,LOW);
        delayMicroseconds(0);
        digitalWrite(stp,HIGH);
        delayMicroseconds(1500);
        }
        break;
    }
    STOPleft=0;
    
    while(incomingData==2&&pre!=incomingData&&STOPright!=1){
      
      delayMicroseconds(2);
      digitalWrite(dir,LOW);
      int hright=digitalRead(8);//霍尔元件接口
/*******************
 若磁铁靠近，9脚输入高电频，步进电机停转。
 */
      if(hright == HIGH)
        {
          STOPright=1;
        }
      else
        {
        digitalWrite(dir,HIGH);
        digitalWrite(stp,LOW);
        delayMicroseconds(0);
        digitalWrite(stp,HIGH);
        delayMicroseconds(1500);
        }
        break;
    }
    STOPright=0;
       /* while(incomingData==10&&pre!=incomingData&&STOPleft!=1){
      delayMicroseconds(2);
      int hleft=digitalRead(7);//霍尔元件接口
/*******************
 若磁铁靠近，8脚输入高电频，步进电机停转。
 */
     /* if(hleft == HIGH)
        {
          STOPleft=1;
        }
      else
        {
        digitalWrite(dir,LOW);
        digitalWrite(stp,LOW);
        delayMicroseconds(0);
        digitalWrite(stp,LOW);
        delayMicroseconds(1500);
        }
            break;
    }*/
}
