#include <Adafruit_NeoPixel.h>//灯带库函数
#define PIN 1//定义引脚

#define NUMPIXELS 7//定义led灯数量

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);//定义灯带（确定灯长，输出口，输出规则）

int delayval2 =100; 
void setup(){
  pixels.setBrightness(25);               //设置灯带亮度
  pixels.begin();                        //NeoPixel输出准备数据引脚
}
void loop() {
  uint32_t light2c = pixels.Color(100,100,100);//设置灯带RGB颜色
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,light2c);//设置第i盏灯为light2c色）
    pixels.show();//更新灯带
  }//*/
    /*  pixels.setPixelColor(0,light2c);//设置第i盏灯为light2c色）
    pixels.setPixelColor(0,light2c);//设置第i盏灯为light2c色）
    pixels.setPixelColor(0,light2c);//设置第i盏灯为light2c色）
    pixels.setPixelColor(0,light2c);//设置第i盏灯为light2c色）
    pixels.setPixelColor(0,light2c);//设置第i盏灯为light2c色）
    pixels.setPixelColor(0,light2c);//设置第i盏灯为light2c色）

  /*while(true){
    light2bright+=10;
    pixels.setBrightness(light2bright);//设置灯带亮度
    pixels.show();
    delay(delayval2);
    if(light2bright>=200)
      break;
  }
  while(true){
    light2bright-=10;
    pixels.setBrightness(light2bright);
    pixels.show();
    delay(delayval2);
    if(light2bright<=10)
      break;
  }*/
}
