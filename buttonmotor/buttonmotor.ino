const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStatePin = 5;
const int potPin = A0;

int onOffSwitchState = 0;
int prevOnOffSwitchState = 0;
int directionSwitchState = 0;
int prevDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 0;

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
  
  onOffSwitchState = digitalRead(onOffSwitchStatePin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin)/4;

  if(directionSwitchState != prevDirectionSwitchState){
    if(directionSwitchState == HIGH){
      motorDirection = !motorDirection;
    }
  }
  if(motorDirection==0){
    digitalWrite(controlPin1,HIGH);
    digitalWrite(controlPin2, LOW);
  } else {
    digitalWrite(controlPin1,LOW);
    digitalWrite(controlPin2,HIGH);
  }
  
  //Turn on motor for 2 seconds if object is more than 0.1m away
  if(distance > 10){
    if(doorClosed == 0){
      analogWrite(enablePin, motorSpeed);
      delay(400);
      analogWrite(enablePin, 0);
      //Set door to closed
      doorClosed = 1;
    }
  }
  
  if(onOffSwitchState != prevOnOffSwitchState){
    if(onOffSwitchState == HIGH){
      motorEnabled = !motorEnabled;
    }
  }

  if(motorEnabled == 1){
    analogWrite(enablePin, 25);  
    delay(400);
    analogWrite(enablePin, 0);
  } else {
    analogWrite(enablePin, 0);
  }
  delay(100);
  motorEnabled = 0;
  prevDirectionSwitchState = directionSwitchState;
  prevOnOffSwitchState = onOffSwitchState;  
}
