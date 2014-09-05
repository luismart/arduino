//Robot-Luciano : This script controls the two motors with the dual H-Bridge
//                and digital PINS 5,6,7,8. Current fed from batteries

int motor2Pin1 =  5;    // One motor wire in Motor2 connected to digital pin 5
int motor2Pin2 =  6;    // One motor wire in Motor2 connected to digital pin 6
int motor1Pin1 =  9;    // One motor wire in Motor1 connected to digital pin 7
int motor1Pin2 =  10;    // One motor wire in Motor1 connected to digital pin 8

int UltraS_echoPin=4;  // connect digital I/O 3 to the ECHO/Rx Pin
int UltraS_trigPin=3; // connect digital I/O 4 to the TRIG/TX Pin
int Master=1;
// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digital pins as an output:
  Serial.begin(9600);
  pinMode(motor1Pin1, OUTPUT); 
  pinMode(motor1Pin2, OUTPUT);  
  pinMode(motor2Pin1, OUTPUT); 
  pinMode(motor2Pin2, OUTPUT);  
  
  pinMode(UltraS_echoPin, INPUT);
  pinMode(UltraS_trigPin, OUTPUT);
}

// the loop() method runs the two motors forward, backward and turns right and left
void loop()                     
{
   digitalWrite(UltraS_trigPin, LOW);  // send low pulse for 2μs
   delayMicroseconds(2);
   digitalWrite(UltraS_trigPin, HIGH); // send high pulse for 10μs
   delayMicroseconds(10);
   digitalWrite(UltraS_trigPin, LOW);  // back to low pulse
   int distance = pulseIn(UltraS_echoPin, HIGH);  // read echo value
   int distance1= distance/29/2;  // in cm
   Serial.println(distance1); 
  
  if (distance1 > 20) {
      goStraight(250,5000);
      //digitalWrite(motor1Pin1, HIGH); //rotates motor1 fprward
      //digitalWrite(motor1Pin2, LOW);        
      //digitalWrite(motor2Pin1, HIGH); //rotates motor1 fprward
      //digitalWrite(motor2Pin2, LOW);     
      
      }else{
      rotatefwd(50,0,2500);
      //digitalWrite(motor1Pin2, HIGH); //rotates motor1 fprward
      //digitalWrite(motor1Pin1, LOW);      
      //digitalWrite(motor2Pin2, HIGH); //rotates motor1 fprward
      //digitalWrite(motor2Pin1, LOW);      
      //delay(500);
      //digitalWrite(motor1Pin2, LOW);
      //digitalWrite(motor2Pin2, LOW);
  }
}

void goStraight(int speedOfRotate, int length){
  
  if (Master==1) {
  //digitalWrite(motor1Pin1, HIGH); //rotates motor1 fprward
  analogWrite(motor1Pin1, speedOfRotate);
  digitalWrite(motor1Pin2, LOW);      
 
 //digitalWrite(motor2Pin1, HIGH); //rotates motor2 foward
  analogWrite(motor2Pin1, speedOfRotate);
  digitalWrite(motor2Pin2, LOW);
  Master=0;  
  }
  else {
  //digitalWrite(motor2Pin1, HIGH); //rotates motor2 foward
  analogWrite(motor2Pin1, speedOfRotate);
  digitalWrite(motor2Pin2, LOW);
  
  //digitalWrite(motor1Pin1, HIGH); //rotates motor1 fprward
  analogWrite(motor1Pin1, speedOfRotate);
  digitalWrite(motor1Pin2, LOW);  
  Master=1;  
 }
  //delay(length); //waits
  //digitalWrite(motor1Pin1, LOW);    // stop motor1
  //digitalWrite(motor2Pin1, LOW);    // stop motor2
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

