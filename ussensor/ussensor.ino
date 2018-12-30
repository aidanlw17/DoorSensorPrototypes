const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStatePin = 5;
const int potPin = A0;
const int trigPin = 7;
const int echoPin = 8;

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

void setup() {
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStatePin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(enablePin, LOW);
  Serial.begin(9600);
}

void loop() {
  
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
  if(motorDirection==0){
    digitalWrite(controlPin1,HIGH);
    digitalWrite(controlPin2, LOW);
  } else {
    digitalWrite(controlPin1,LOW);
    digitalWrite(controlPin2,HIGH);
  }
  
  //Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //Turns trigPin on for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //Reads duration and calculates distance (sound travelling  at 340m/s)
  duration = pulseIn(echoPin,HIGH);
  distance = duration*0.034/2;
  Serial.print("Distance: \n");
  Serial.print(distance);
  Serial.print("\n");
  Serial.print("Durration: \n");
  Serial.print(duration);

  //Turn on motor for 2 seconds if object is more than 0.1m away
  if(distance > 10){
    if(doorClosed == 0){
      //analogWrite(enablePin, motorSpeed);
      //delay(400);
      //analogWrite(enablePin, 0);
      //Set door to closed
      //doorClosed = 1;
    }
  }
  
//  if(onOffSwitchState != prevOnOffSwitchState){
//    if(onOffSwitchState == HIGH){
//      motorEnabled = !motorEnabled;
//    }
//  }

//  if(motorEnabled == 1){
//    analogWrite(enablePin, motorSpeed);  
//  } else {
//    analogWrite(enablePin, 0);
//  }
  delay(3000);
  prevDirectionSwitchState = directionSwitchState;
//  prevOnOffSwitchState = onOffSwitchState;  
}
