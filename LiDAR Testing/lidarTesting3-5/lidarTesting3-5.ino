#include <RPLidar.h> //creates a driver instance
RPLidar lidar;
#define RPLIDAR_MOTOR 3//PWM PIN


void setup() {
  // bind the RPLIDAR driver to arduino hardware
  lidar.begin(Serial);
  Serial.begin(115200);
  //set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  //pinMode(sensor1, INPUT);// for direct serial transfer

}

void loop(){

  if(IS_OK(lidar.waitPoint())){
    float distance= lidar.getCurrentPoint().distance;//distance value in mm
    float angle =lidar.getCurrentPoint().angle; //angle value in degree
    bool startBit = lidar.getCurrentPoint().startBit; // whether this point is
    byte quality = lidar.getCurrentPoint().quality; //quaity of current
    float realdistance = distance*1000;
    delay(10);
    if(realdistance>0.15){
      delay(10);
      if(realdistance<12){
        float x;
        float y;
        //x= distance*cos(angle);
        //y= distance*sin(angle);
          //Serial.print(x);
          //Serial.print(",");
          //Serial.println(y);
          Serial.print(realdistance);
          Serial.print(",");
          Serial.println(angle);
          delay(10);
        }
      }
    }


    else{
    analogWrite(RPLIDAR_MOTOR,0);//stop the lidar motor
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))){
      lidar.startScan();

      // start motor rotating at 
      analogWrite(RPLIDAR_MOTOR, 200);
      delay(1000);
      }
    }
}