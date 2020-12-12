const int a=7;

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


unsigned long incomingData;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position


void setup() {
    myservo.attach(6);  // attaches the servo on pin 9 to the servo object

  // pinMode(b,INPUT);
  pinMode(a,OUTPUT);
  
  
  Serial.begin(9600);
  
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); // 信道，节点地址
  radio.setDataRate(RF24_2MBPS);
}

void loop() {
  //digitalWrite(5,HIGH);

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
for (pos = 0; pos <= 178;pos++ ) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
   for (pos = 178; pos >= 0;pos-- ) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
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
