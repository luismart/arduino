//Robot-Luciano : This script controls the ultrasonic distance sensor
//                

int UltraS_echoPin=3;  // connect digital I/O 3 to the ECHO/Rx Pin
int UltraS_trigPin=4; // connect digital I/O 4 to the TRIG/TX Pin

void setup()
{
  Serial.begin(9600);
  pinMode(UltraS_echoPin, INPUT);
  pinMode(UltraS_trigPin, OUTPUT);
}
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
   delay(50);  
}
