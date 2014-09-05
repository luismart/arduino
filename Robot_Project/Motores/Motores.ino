//Robot-Luciano : This script controls the two motors with the dual H-Bridge
//                and digital PINS 5,6,7,8. Current fed from batteries

int motor2Pin1 =  5;    // One motor wire in Motor2 connected to digital pin 5
int motor2Pin2 =  6;    // One motor wire in Motor2 connected to digital pin 6
int motor1Pin1 =  7;    // One motor wire in Motor1 connected to digital pin 7
int motor1Pin2 =  8;    // One motor wire in Motor1 connected to digital pin 8

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digital pins as an output:
  pinMode(motor1Pin1, OUTPUT); 
  pinMode(motor1Pin2, OUTPUT);  
  pinMode(motor2Pin1, OUTPUT); 
  pinMode(motor2Pin2, OUTPUT);  
}

// the loop() method runs the two motors forward, backward and turns right and left
void loop()                     
{
   goStraight(350,1000);
  //goBackwards(350,1000);
  rotate(250,100,1000);
  delay(500);
}

void goStraight(int speedOfRotate, int length){
  digitalWrite(motor1Pin1, HIGH); //rotates motor1 fprward
  //analogWrite(motor1Pin1, speedofRotate);
  digitalWrite(motor1Pin2, LOW);    
 
  
  digitalWrite(motor2Pin1, HIGH); //rotates motor2 foward
  //analogWrite(motor2Pin1, speedofRotate);
  digitalWrite(motor2Pin2, LOW);    
  
  delay(length); //waits
  digitalWrite(motor1Pin1, LOW);    // stop motor1
  digitalWrite(motor2Pin1, LOW);    // stop motor2
}

void goBackwards(int speedOfRotate, int length){
  digitalWrite(motor1Pin1, LOW); //rotates motor1 backwards
  digitalWrite(motor1Pin2, HIGH);    
  //analogWrite(motor1Pin2, speedofRotate);
  
  digitalWrite(motor2Pin1, LOW); //rotates motor2 backwards
  digitalWrite(motor2Pin2, HIGH);
  //analogWrite(motor2Pin2, speedofRotate);
  
  delay(length); //waits
  digitalWrite(motor1Pin2, LOW);    // stop motor1
  digitalWrite(motor2Pin2, LOW);    // stop motor2
}

void rotatefwd(int speedOfRotate1,int speedOfRotate2, int length){
  analogWrite(motor1Pin1, speedOfRotate1); //rotates motor1 and motor2 forward at different speeds
  digitalWrite(motor1Pin2, LOW);    // 
  
  analogWrite(motor2Pin1, speedOfRotate2); 
  digitalWrite(motor2Pin2, LOW);    
  
  delay(length); //waits
  digitalWrite(motor1Pin1, LOW);    // stop motor1
  digitalWrite(motor2Pin1, LOW);    // stop motor2
}

void rotatebkwd(int speedOfRotate1,int speedOfRotate2, int length){
  analogWrite(motor1Pin2, speedOfRotate1); //rotates motor1 and motor2 backwards at different speeds
  digitalWrite(motor1Pin1, LOW);    
  
  analogWrite(motor2Pin2, speedOfRotate2);
  digitalWrite(motor2Pin1, LOW);
  
  delay(length); //waits
  digitalWrite(motor1Pin2, LOW);    // stop motor1
  digitalWrite(motor2Pin2, LOW);    // stop motor2
}

