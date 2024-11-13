#include <Servo.h>
#define BLINKER_WIFI
#define BLINKER_MIOT_OUTLET
#include <Blinker.h>

char auth[] = "c12dd1583b17";  //点灯Key
char ssid[] = "真男人的秘密基地";      //wifi名称
char pswd[] = "lsw12345678";     //wifi密码

Servo myservo;
// 新建组件对象
BlinkerButton Button1("btn-max");   //最大值按钮
BlinkerButton Button2("btn-min");   //最小值按钮
BlinkerButton Button3("btn-set");   //复位-90°
BlinkerButton Button4("btn-switch");   //门锁按钮
BlinkerSlider Slider3("ser-num");   //滑块


int servo_max,servo_min,servo_set,ser_num,time_num;

void button1_callback(const String & state) {    //最大值按钮功能
    BLINKER_LOG("get button state: ", servo_max);
    myservo.write(servo_max);
    Blinker.vibrate();
}

void button2_callback(const String & state) {   //最小值按钮功能
    BLINKER_LOG("get button state: ", servo_min);
    myservo.write(servo_min);
    Blinker.vibrate();
}

void button3_callback(const String & state) {   //重置按钮功能
    BLINKER_LOG("get button state: ", 666);
    myservo.write(servo_set);
    Blinker.vibrate();
}


void button4_callback(const String & state) {   //重置按钮功能
    BLINKER_LOG("get button state: ", servo_set);
    myservo.write(servo_max);
    Blinker.delay(500);
    myservo.write(servo_min);
    Blinker.vibrate();
}


void slider3_callback(int32_t value) //滑块功能
{
    ser_num = value;
    myservo.write(ser_num);
    Blinker.delay(500);
    BLINKER_LOG("get slider value: ", value);
}

void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        myservo.write(servo_max);
        Blinker.delay(500);
        myservo.write(servo_min);
        
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        myservo.write(servo_max);
        Blinker.delay(500);
        myservo.write(servo_min);

        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}

void setup() {
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();
    
    Blinker.begin(auth, ssid, pswd);

    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
    Button4.attach(button4_callback);
    Slider3.attach(slider3_callback);
    myservo.attach(D6); //servo.attach():设置舵机数据引脚
    myservo.write(90);

    BlinkerMIOT.attachPowerState(miotPowerState);
    servo_max=160;
    servo_min=40;
    servo_set=90;
    time_num=2000;
}

void loop() {
  Blinker.run(); 
}
