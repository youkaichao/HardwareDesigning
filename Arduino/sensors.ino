/*
 * @author:Yifan, Peng
 * @email:youkaichao@126.com
 * @date:2017/7/8
 */

#include <SoftwareSerial.h>
#define pin 2
#define intenpin 4
#define TrigPin 5
#define EchoPin 3
#define voicepin 8
int temp;//温度
int humi;//湿度
int inten;//光照
int voi;//声音
float distance; //距离
int intdistance;//距离的100倍
SoftwareSerial BT(12, 9); // RX, TX
unsigned int loopCnt;
int chr[40] = {0};//创建数字数组，用来存放40个bit
unsigned long time;
char h_str[5];
char t_str[5];
char i_str[5];
char s_str[5];
char d_str[10];

void setup() 
{
        // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) 
  {
  ;     // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT); 
  pinMode(voicepin, INPUT);

  Serial.println(F("Welcome to Bluetooth console!:)"));
  Serial.println(F("\nUsage:"));
  Serial.println(F("1.Send\"AT+ADDR\\r\\n\" to show local address"));
  Serial.println(F("2.Send\"AT+BIND=XXXX,XX,XXXXXX(your client's address)\\r\\n\" to bind to a client"));
  Serial.println(F("Send\"AT+ROLE=1\\r\\n\" to become host"));
  Serial.println(F("Send\"AT+PSWD=XXXX\\r\\n\" to set password"));
  Serial.print(F("Checking Bluetooth connection..."));
        // set the data rate for the SoftwareSerial port
  BT.begin(9600);
//BT.println("AT");

}

void loop() 
{ 
  bgn:
  delay(2000);
    //设置2号接口模式为：输出
    //输出低电平20ms（>18ms）
    //输出高电平40μs
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
  delay(20);
  digitalWrite(pin,HIGH);
  delayMicroseconds(40);
  digitalWrite(pin,LOW);
    //设置2号接口模式：输入
  pinMode(pin,INPUT);
    //高电平响应信号
  loopCnt=10000;
  while(digitalRead(pin) != HIGH)
  {
    if(loopCnt-- == 0)
    {
    //如果长时间不返回高电平，输出个提示，重头开始。
     // Serial.println("HIGH");
      goto bgn;
    }
  }
    //低电平响应信号
  loopCnt=30000;
  while(digitalRead(pin) != LOW)
  {
    if(loopCnt-- == 0)
    {
    //如果长时间不返回低电平，输出个提示，重头开始。
     // Serial.println("LOW");
      goto bgn;
    }
  }
    //开始读取bit1-40的数值  
    for(int i=0;i<40;i++)
  {
    while(digitalRead(pin) == LOW)
    {}
    //当出现高电平时，记下时间“time”
    time = micros();
    while(digitalRead(pin) == HIGH)
    {}
    //当出现低电平，记下时间，再减去刚才储存的time
    //得出的值若大于50μs，则为‘1’，否则为‘0’
    //并储存到数组里去
    if (micros() - time >50)
    {
      chr[i]=1;
    }else{
      chr[i]=0;
    }
  }
//湿度，8位的bit，转换为数值
  humi=chr[0]*128+chr[1]*64+chr[2]*32+chr[3]*16+chr[4]*8+chr[5]*4+chr[6]*2+chr[7];
//温度，8位的bit，转换为数值
  temp=chr[16]*128+chr[17]*64+chr[18]*32+chr[19]*16+chr[20]*8+chr[21]*4+chr[22]*2+chr[23];
//光照，亮为0，暗为1
  inten=digitalRead(intenpin);
//测距
      // 产生一个10us的高脉冲去触发TrigPin 
        digitalWrite(TrigPin, LOW); 
        delayMicroseconds(2); 
        digitalWrite(TrigPin, HIGH); 
        delayMicroseconds(10);
        digitalWrite(TrigPin, LOW); 
      // 检测脉冲宽度，并计算出距离
        distance = pulseIn(EchoPin, HIGH) / 58.00;
        intdistance=(int)distance;
//声音，吵闹为0，安静为1
  voi = digitalRead(voicepin);

  Serial.print("#S|HUMIDITY|[");
  Serial.print(itoa(humi,h_str,10));
  Serial.println("]#");
  Serial.print("#S|TEMPERA|[");
  Serial.print(itoa(temp,t_str,10));
  Serial.println("]#");
  Serial.print("#S|INTES|[");
  Serial.print(itoa(inten,i_str,10));
  Serial.println("]#");
  Serial.print("#S|SOUND|[");
  Serial.print(itoa(voi,s_str,10));
  Serial.println("]#");
  Serial.print("#S|DISTANCE|[");
  Serial.print(itoa(intdistance,d_str,10));
  Serial.println("]#");

  BT.write((byte)temp);
 
/*
  if (BT.available()) 
  {
    Serial.write(BT.read());
  }
  if (Serial.available()) 
  {
    BT.write(Serial.read());
  }
*/
}