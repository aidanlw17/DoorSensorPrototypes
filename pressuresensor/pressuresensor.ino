const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStatePin = 5;
const int potPin = A0;
const int fsrPin = A1;

//int onOffSwitchState = 0;
int prevOnOffSwitchState = 0;
int directionSwitchState = 0;
int prevDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;
int stayOpen = 0;
int distance = 0;
long duration = 0;
int doorSwitch = 0;
int doorClosed = 1;
int fsrReading = 0;

void setup() {
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStatePin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW);
  Serial.begin(9600);
}

void loop() {

  //Read force on fsr
  fsrReading = analogRead(fsrPin);
  
  doorSwitch = digitalRead(onOffSwitchStatePin);
  delay(1);
  if(doorSwitch == 1){
    doorClosed = 0;
  }
  delay(100);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin)/4;

  if(directionSwitchState != prevDirectionSwitchState){
    if(directionSwitchState == HIGH){
      motorDirection = !motorDirection;
    }
  }
  if(motorDirection==1){
    digitalWrite(controlPin1,HIGH);
    digitalWrite(controlPin2, LOW);
  } else {
    digitalWrite(controlPin1,LOW);
    digitalWrite(controlPin2,HIGH);
  }
  
  Serial.print("Force: \n");
  Serial.print(fsrReading);
  Serial.print("\n");

  //Turn on motor for 2 seconds if fsrReading is != 0 and door is not closed
  if(fsrReading == 0){
    if(doorClosed == 0){
    //  analogWrite(enablePin, motorSpeed);
    //  delay(100);
     // analogWrite(enablePin, 0);
      //Set door to closed
      doorClosed = 1;
    }
  }
  
  delay(2000);
  prevDirectionSwitchState = directionSwitchState;
}
