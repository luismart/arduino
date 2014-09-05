#include <Servo.h>
Servo myServo;  // create servo object to control a servo 
void setup() 
{ 
  myServo.attach(2);  // attaches the servo on pin 2 to the servo object and 5v to red and GND to black see http://www.hobbytronics.co.uk/arduino-tutorial2-servos
    myServo.write(0);
} 
void loop() 
{ 
  myServo.write(0);
  delay(2000);  // waits for the servo to get there 
  myServo.write(135);
  delay(1000);  // waits for the servo to get there 
  myServo.write(0);
  delay(2000);  // waits for the servo to get there 
  //myServo.write(45);
  //delay(1000);  // waits for the servo to get there 
  //myServo.write(180);
  //delay(2000);  // waits for the servo to get there 
} 

