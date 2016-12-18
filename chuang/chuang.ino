#include <avr/sleep.h>
#include <avr/power.h>
#include <Adafruit_NeoPixel.h>//引用头文件
#define PIN 6   /*定义了控制LED的引脚，6表示Microduino的D6引脚，可通过Hub转接出来，用户可以更改 */
#define PIN_NUM 2 //定义允许接的led灯的个数
#include <IRremote.h>
#include <U8glib.h>
#define INTERVAL_LCD             20             //定义OLED刷新时间间隔  
int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long lcd_time = millis();                 //OLED刷新时间计时器
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);     //设置OLED型号  
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_7x13)
#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
#define setFont_SS u8g.setFont(u8g_font_fub25n)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800); //该函数第一个参数控制串联灯的个数，第二个是控制用哪个pin脚输出，第三个显示颜色和变化闪烁频率
int pin2 = 2;
 
long previousMillis = 0;        // 存储LED最后一次的更新
long interval = 8000;           // 闪烁的时间间隔（毫秒）
unsigned long currentMillis=0;
void pin2Interrupt(void) {
    /* 中断唤醒 */
 
    /*当中断引脚为低电平时关闭中断*/
    Serial.println("wake up!!!");
    detachInterrupt(0);
}
void enterSleep(void) {
    attachInterrupt(0, pin2Interrupt, LOW);
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
}

int numberofbutton=16;
char * mystring[]={
  "press on off",
  "press A",
  "press B",
  "press C",
  "press D",
  "press up", 
  "press E", 
  "press left",
  "press OK",
  "press right",
  "press back",
  "press down",
  "press volume up",
  "press pause/start", 
  "press scilence",
  "press volume down"
};

int decimalkey[16]={33441975,// on off button
33456255,// button A
33439935,// button B
33472575,// button C
33431775,//button D
33464415,//button up
33448095,//button E
33480735,//button left
33427695,//button OK
33460335,//button right
33444015,//button back
33478695,//button down
33486855,//buttion voice up
33435855,//button pause
33468495,// button science
33452175//button voice down
};


void setup() {
    Serial.begin(9600);    
    irrecv.enableIRIn(); // Start the receiver
    Serial.println("Initialisation complete.");
    strip.begin();   //准备对灯珠进行数据发送
    pinMode(pin2, INPUT);
}

//void loop() {
//  if (irrecv.decode(&results)) {
//    Serial.println(results.value, HEX);
//    u8g.firstPage();
//    do {
//        setFont_L;
//        u8g.setPrintPos(4, 16);
//        u8g.print(results.value,HEX);
//        strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
//        strip.show();   //LED显示
//    }while( u8g.nextPage() );
//    irrecv.resume(); // Receive the next value
//    delay(1000);
//  }
//}

void loop() {
    currentMillis = millis();
    Serial.print("Awake for ");
    Serial.print(currentMillis - previousMillis, DEC);
    Serial.println(" second");
    delay(1000);
  strip.setPixelColor(0, strip.Color(0, 0, 0));//不发光
  strip.show();   //LED显示
  u8g.firstPage();
    do {
        setFont_L;
        u8g.setPrintPos(4, 16);
        u8g.print("Input a password");
    }while( u8g.nextPage() );
  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    Serial.println(results.value, HEX);
    switch(results.value){
      case 33441975:// on off button
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[0]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value      
      delay(1000);
      break;
      
      case 33456255:// button A
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[1]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33439935:// button B
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[2]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);      
      break;
      
      case 33472575:// button C
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[3]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case  33431775://button D
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[4]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33464415://button up
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[5]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33448095://button E
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[6]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33480735://button left
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[7]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33427695://button OK
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[8]);
             strip.setPixelColor(0, strip.Color(0, 255, 0));//绿光
             strip.show();   //LED显示
             delay(1000);
             setFont_L;
             u8g.setPrintPos(4, 32);
             u8g.print("Correct! Welcome");
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33460335://button right
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[9]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33444015://button back
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[10]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33478695://button down
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[11]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33486855://buttion voice up
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[12]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33435855://button pause
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[13]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33468495:// button science
         u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[14]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      case 33452175://button voice down
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print(mystring[15]);
             strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
             strip.show();   //LED显示
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      break;
      
      default:
        u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print("Default");
         }while( u8g.nextPage() );
      irrecv.resume(); // Receive the next value
      delay(1000);
      }
      previousMillis = currentMillis;
  }
      if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis; 
      Serial.println("Entering sleep");
      u8g.firstPage();
        do {
             setFont_L;
             u8g.setPrintPos(4, 16);
             u8g.print("Please touch");
             u8g.setPrintPos(4, 32);
             u8g.print("the button");
         }while( u8g.nextPage() );
      enterSleep();
    }
  if(currentMillis<previousMillis)
    previousMillis=currentMillis=0;
}

