/* YourDuino.com Example Software Sketch
 IR Remote Kit Test
 Uses YourDuino.com IR Infrared Remote Control Kit 2
 http://arduino-direct.com/sunshop/index.php?l=product_detail&p=153
 based on code by Ken Shirriff - http://arcfn.com
 Get Library at: https://github.com/shirriff/Arduino-IRremote
 Unzip folder into Libraries. RENAME folder IRremote
 terry@yourduino.com */

/*-----( Import needed libraries )-----*/

#include "IRremote.h"

/*-----( Declare Constants )-----*/
int receiver = 11; // pin 1 of IR receiver to Arduino digital pin 11
int led = 2;
int motor2Pin1 =  5;    // One motor wire in Motor2 connected to digital pin 5
int motor2Pin2 =  6;    // One motor wire in Motor2 connected to digital pin 6
int motor1Pin1 =  9;    // One motor wire in Motor1 connected to digital pin 7
int motor1Pin2 =  10;    // One motor wire in Motor1 connected to digital pin 8


/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'
/*-----( Declare Variables )-----*/


void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Raw Data + Button Decode Test");
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led, OUTPUT);
    // initialize the digital pins as an output:
  pinMode(motor1Pin1, OUTPUT); 
  pinMode(motor1Pin2, OUTPUT);  
  pinMode(motor2Pin1, OUTPUT); 
  pinMode(motor2Pin2, OUTPUT);  


}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
  Serial.println(results.value, HEX); // UN Comment to see raw values
    translateIR(); 
    irrecv.resume(); // receive the next value
    }  
}/* --(end main loop )-- */

/*-----( Declare User-written Functions )-----*/
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
void translateIR() // takes action based on IR code received

// describing Car MP3 IR codes 

{

  switch(results.value)

  {

  case 0xFFA25D:  
    Serial.println(" CH-            "); 
    break;

  case 0xFF629D:  
    Serial.println(" CH             "); 
    break;

  case 0xFFE21D:  
    Serial.println(" CH+            "); 
    break;

  case 0xFF22DD:  
    Serial.println(" PREV           "); 
    break;

  case 0xFF02FD:  
    Serial.println(" NEXT           "); 
    break;

  case 0xFFC23D:  
    Serial.println(" PLAY/PAUSE     "); 
    break;

  case 0xFFE01F:  
    Serial.println(" VOL-           "); 
    break;

  case 0xFFA857:  
    Serial.println(" VOL+           ");
   goBackwards(350,1000); 
    break;

  case 0xFF906F:  
    Serial.println(" EQ             ");
    goStraight(350,1000); 
    break;

  case 0xFF6897:  
    Serial.println(" 0              "); 
    break;

  case 0xFF9867:  
    Serial.println(" 100+           "); 
    break;

  case 0xFFB04F:  
    Serial.println(" 200+           "); 
    break;

  case 0xFF30CF:  
    Serial.println(" 1              "); 
    break;

  case 0xFF18E7:  
    Serial.println(" 2              "); 
    break;

  case 0xFF7A85:  
    Serial.println(" 3              "); 
    break;

  case 0xFF10EF:  
    Serial.println(" 4              "); 
    break;

  case 0xFF38C7:  
    Serial.println(" 5              "); 
    break;

  case 0xFF5AA5:  
    Serial.println(" 6              "); 
    break;

  case 0xFF42BD:  
    Serial.println(" 7              "); 
    break;

  case 0xFF4AB5:  
    Serial.println(" 8              "); 
    break;

  case 0xFF52AD:  
    Serial.println(" 9              "); 
    break;

  default: 
    Serial.println(" other button   ");

  }
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);

} //END translateIR



/* ( THE END ) */

