//Luciano-Bot : This script controls the two motors with the dual H-Bridge
//              and digital PINS 5,6,7,8. And the ultrasonic sensor with 
//              pins 3 and 4. Current fed from batteries

//ultrasonic sensor
int UltraS_echoPin=3;  // connect digital I/O 3 to the ECHO/Rx Pin
int UltraS_trigPin=4; // connect digital I/O 4 to the TRIG/TX Pin

//motors
int motor2Pin1 =  5;    // One motor wire in Motor2 connected to digital pin 5
int motor2Pin2 =  6;    // One motor wire in Motor2 connected to digital pin 6
int motor1Pin1 =  7;    // One motor wire in Motor1 connected to digital pin 7
int motor1Pin2 =  8;    // One motor wire in Motor1 connected to digital pin 8

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digital pins for the motors as an output:
  pinMode(motor1Pin1, OUTPUT); 
  pinMode(motor1Pin2, OUTPUT);  
  pinMode(motor2Pin1, OUTPUT); 
  pinMode(motor2Pin2, OUTPUT);  
  // initialize the digital pins for the ultrasonic sensor as input andoutput
  Serial.begin(9600);
  pinMode(UltraS_echoPin, INPUT);
  pinMode(UltraS_trigPin, OUTPUT);
}

// the loop() method runs the two motors forward, backward and turns right and left
void loop()                     
{
   goStraight(350,300);
   int ditance_obstacle=meassure_distance()
   if (ditance_obstacle <15) {
     goBackwards(350,200);
     rotatefwd(250,100,1000);
   }
  //
  
  delay(500);
}

int meassure distance(){
   digitalWrite(UltraS_trigPin, LOW);  // send low pulse for 2μs
   delayMicroseconds(2);
   digitalWrite(UltraS_trigPin, HIGH); // send high pulse for 10μs
   delayMicroseconds(10);
   digitalWrite(UltraS_trigPin, LOW);  // back to low pulse
   int distance = pulseIn(UltraS_echoPin, HIGH);  // read echo value
   int distance1= distance/29/2;  // in cm
   return ditance1;
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

