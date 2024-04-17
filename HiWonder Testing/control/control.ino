#include <Wire.h>

#define I2C_ADDR        0x34

#define GET_LOW_BYTE(A) (uint8_t)((A))
//宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
//宏函数 获得A的高八位
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
//宏函数 以A为高八位 B为低八位 合并为16位整形

#define ADC_BAT_ADDR                  0
#define MOTOR_TYPE_ADDR               20 //编码电机类型设置
#define MOTOR_ENCODER_POLARITY_ADDR   21 //设置编码方向极性，
//如果发现电机转速根本不受控制，要么最快速度转动，要么停止。可以将此地址的值重新设置一下
//范围0或1，默认0
#define MOTOR_FIXED_PWM_ADDR      31 //固定PWM控制，属于开环控制,范围（-100~100）
//#define SERVOS_ADDR_CMD 40        
#define MOTOR_FIXED_SPEED_ADDR    51 //固定转速控制，属于闭环控制，
//单位：脉冲数每10毫秒，范围（根据具体的编码电机来，受编码线数，电压大小，负载大小等影响，一般在±50左右）

#define MOTOR_ENCODER_TOTAL_ADDR  60 //4个编码电机各自的总脉冲值
//如果已知电机每转一圈的脉冲数为U，又已知轮子的直径D，那么就可以通过脉冲计数的方式得知每个轮子行进的距离
//比如读到电机1的脉冲总数为P，那么行进的距离为(P/U) * (3.14159*D)
//对于不同的电机可以自行测试每圈的脉冲数U，可以手动旋转10圈读出脉冲数，然后取平均值得出


//电机类型具体值
#define MOTOR_TYPE_WITHOUT_ENCODER        0
#define MOTOR_TYPE_TT                     1
#define MOTOR_TYPE_N20                    2
#define MOTOR_TYPE_JGB37_520_12V_110RPM   3 //磁环每转是44个脉冲   减速比:90  默认

int servopin=12;    //使用12号口模拟PWM信号
int pulsewidth;     //占空比
void servo(int myangle)
{
  pulsewidth=map(myangle,0,180,500,2500);   //将0°- 180°范围映射到500 - 2500范围（即角度到占空比的转换）
  digitalWrite(servopin,HIGH);    //输出高电平
  delayMicroseconds(pulsewidth);  //模拟占空比输出高电平信号
  digitalWrite(servopin,LOW);     //输出低电平
  delay(20-pulsewidth/1000);    //延时     
}

u8 data[20];
bool WireWriteByte(uint8_t val)   //通过I2C发送字节数据
{
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(val);
    if( Wire.endTransmission() != 0 ) {
        return false;
    }
    return true;
}
bool WireWriteDataArray(  uint8_t reg,uint8_t *val,unsigned int len)    //通过I2C发送数据
{
    unsigned int i;

    Wire.beginTransmission(I2C_ADDR);   //设置任务开始地址
    Wire.write(reg);    //头地址内容写入
    for(i = 0; i < len; i++) {
        Wire.write(val[i]);   //传入的内容写入I2C
    }
    if( Wire.endTransmission() != 0 ) {     //写入是否联通荣判断
        return false;
    }

    return true;
}

uint8_t MotorType = MOTOR_TYPE_JGB37_520_12V_110RPM;    //电机模式设置
uint8_t MotorEncoderPolarity = 0;     //电机极性设置
void setup()
{
  Wire.begin();
  pinMode(servopin,OUTPUT);
  delay(200);
  WireWriteDataArray(MOTOR_TYPE_ADDR,&MotorType,1);
  delay(5);
  WireWriteDataArray(MOTOR_ENCODER_POLARITY_ADDR,&MotorEncoderPolarity,1);
  servo(90);

}
int8_t car_forward[4]={-16,0,16,0};   //前进
int8_t car_retreat[4]={16,0,-16,0};   //后退
int8_t car_stop[4]={0,0,0,0};

void loop()
{
  /* 小车前进 */
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_forward,4);
  delay(4000);
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_stop,4);
  delay(1000);
  /* 小车后退 */
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_retreat,4);
  delay(4000);
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_stop,4);
  delay(1000);
  servo(45);  //转动到90度    
  /* 小车向左前方行驶，4秒后转向不变，回到起点。 */
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_forward,4);
  delay(4000);
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_stop,4);
  delay(1000); 
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_retreat,4);
  delay(4000);
  servo(90);
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_stop,4);
  delay(1000);
  servo(145);
  /* 小车向右前方行驶，4秒后转向不变，回到起点。 */
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_forward,4);
  delay(4000);
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_stop,4);
  delay(1000);
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_retreat,4);
  delay(4000);
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,car_stop,4);
  servo(90);
  delay(1000); 
  
  while(1);
  
}
