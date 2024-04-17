int batteryLevel = 0;

int requestedMotorSpeed = 0;

//Handler Functions
void handleRequestedMotorSpeed(String incomingData);
void handleRequestedServoAngle(String incomingData);

typedef void (*HandlerFunction) (String incomingData);

String inputStrings[] = {"rms", "rsa"};
HandlerFunction handlers[] = {handleRequestedMotorSpeed, handleRequestedServoAngle};

int findHandlerIndex(String inputStr) {
  int equalsIndex = inputStr.indexOf("=");
  String inputStrCode = inputStr.substring(0, equalsIndex);

  int numHandlers = sizeof(inputStrings) / sizeof(inputStrings[0]);
  for(int i = 0; i < numHandlers; i++) {
    if(inputStrCode.equals(inputStrings[i])) {
      return i;
    }
  }

  return -1;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(12, OUTPUT);
}

void handleCommand() {
  if(Serial.available()) {
    String incomingData = Serial.readStringUntil('\n');
    incomingData.toLowerCase();

    int index = findHandlerIndex(incomingData);

    if(index > -1) {
      HandlerFunction handlerFunc = handlers[index];
      handlerFunc(incomingData);
    }
  }
}

void handleRequestedMotorSpeed(String incomingData) {
  int equalsIndex = incomingData.indexOf("=");
  String valStr = incomingData.substring(equalsIndex + 1);
  int val = (int)valStr.toInt();

  Serial.print(incomingData.substring(0, equalsIndex+1));
  Serial.println(val);
  // Serial.println(incomingData);
  for(int i = 0; i < 10; i++) {
    digitalWrite(12, HIGH);
    delay(val);
    digitalWrite(12, LOW);
    delay(val);
  }
}

void handleRequestedServoAngle(String incomingData) {
  int equalsIndex = incomingData.indexOf("=");
  String valStr = incomingData.substring(equalsIndex + 1);
  int val = (int)valStr.toInt();
  
  Serial.print(incomingData.substring(0, equalsIndex+1));
  Serial.println(val);

  for(int i = 0; i < 10; i++) {
    digitalWrite(12, HIGH);
    delay(val);
    digitalWrite(12, LOW);
    delay(val);
  }
}

void loop() {
  handleCommand();
}

void sendBatteryLevel() {
  Serial.write("bl=");
  Serial.write(batteryLevel);
  Serial.write("\n");  
}
