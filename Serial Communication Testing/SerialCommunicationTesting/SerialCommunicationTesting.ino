int batteryLevel = 0;

int requestedMotorSpeed = 0;

// char* receiveCommands[] = {"rms", ""}

//Handler Functions
void handleRequestedMotorSpeed(String incomingData);


char* inputStrings[] = {"RMS"};
void* handlers[] = {handleRequestedMotorSpeed};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(12, OUTPUT);
}

void findHandlerIndex(char* inputStr) {
  int numHandlers = sizeof(inputStrings) / sizeof(inputStrings[0]);
  for(int i = 0; i < numHandlers; i++) {
    if(strcmp(inputStr, inputStrings[i]) == 0) {
      return i;
    }
  }
}

void handleCommand() {
  if(Serial.available()) {
    String incomingData = Serial.readStringUntil('\n');

    if(incomingData.indexOf("RMS=") > -1) {
      handleRequestedMotorSpeed(incomingData);
    }
  }
}

void handleRequestedMotorSpeed(String incomingData) {
  int equalsIndex = incomingData.indexOf("=");
  int motorSpeed = incomingData.substring(equalsIndex+1).toInt();
  requestedMotorSpeed = motorSpeed;
  Serial.print("RMS=");
  Serial.println(requestedMotorSpeed);
}

// void respondBatteryLevel() {
//   if(Serial.available()) {

//   }
// }

void loop() {
char RxedBytes[2];

 if (Serial.available()) 
    {
      String incomingData = Serial.readStringUntil("\n");
      incomingData.toLowerCase();
      if(incomingData.indexOf("rms=") > -1) {
        int equalsIndex = incomingData.indexOf("=");
        String valStr = incomingData.substring(equalsIndex + 1);
        int val = (int)valStr.toInt();
        for(int i = 0; i < 10; i++) {
          digitalWrite(12, HIGH);
          delay(val);
          digitalWrite(12, LOW);
          delay(val);
        }
        Serial.println(incomingData);
      }
      // int numBytesReceieved = Serial.readBytesUntil('\n', RxedBytes, 2);    
       
      // if(RxedBytes[0] == 'A' && RxedBytes[1] == 'B') {
      //   digitalWrite(12,HIGH);
      //   delay(1000);
      //   digitalWrite(12,LOW);
      // }
      // switch(RxedByte)
      // {
      //   case 'A':  digitalWrite(12,HIGH);
      //              delay(1000);
      //              digitalWrite(12,LOW);
      //              break;

      //   case 'B': //your code
      //             digitalWrite(12,HIGH);
      //             delay(200);
      //             digitalWrite(12,LOW);
      //             delay(200);
      //             digitalWrite(12,HIGH);
      //             delay(200);
      //             digitalWrite(12,LOW);
      //             delay(200);
      //             digitalWrite(12,HIGH);
      //             delay(200);
      //             digitalWrite(12,LOW);
      //             delay(200);
      //             digitalWrite(12,HIGH);
      //             delay(200);
      //             digitalWrite(12,LOW);
      //             break;
      //   default:
      //              break;
      // }//end of switch()
    }//endof if 

  // if(Serial.available() > 0) {
  //   char *incomingData;
  //   int length = Serial.readBytesUntil('\n', incomingData, 7);
  //   Serial.println(incomingData);
  // }
  // handleCommand();

  // Serial.println("Arduino says hi 123");
  // sendBatteryLevel();
  // readMotorSpeed();
  // Serial.write("I am talking to you Mr.Jetson\n");
  // put your main code here, to run repeatedly:
  // int numReadBytes = Serial.available();
  // if(numReadBytes > 0) {
  //   String incomingData = Serial.readStringUntil('\n');
  //   // String incomingData = "Hello";

  //   Serial.print("I have received the message: ");
  //   Serial.println(incomingData);
  // }

  // handleSerialRead();
}

void handleSerialRead() {
  // if(Serial.avaiable()) {
  //   String incomingData = Serial.readStringUntil('\n');
  //   if(incomingData.equalsIgnoreCase("ms")) {
  //     Serial.println("Setting motor speed");      
  //   }
  //   else if(incomingData.equalsIgnoreCase("ss")) {
  //     Serial.println("Setting servo speed");
  //   }
  // }
}

void sendBatteryLevel() {
  Serial.write("bl=");
  Serial.write(batteryLevel);
  Serial.write("\n");  
}

void readMotorSpeed() {
  if(Serial.available()) {
    String motorSpeedStr = Serial.readStringUntil('\n');
    // Serial.print("ms=");
    Serial.println(motorSpeedStr);
    // Serial.print("\n");
  }
}
