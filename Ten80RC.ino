#include <NewPing.h>
#include <Servo.h> 
 
Servo steerServo,throttleServo;
 
int pos = 0;    // variable to store the servo position 
int throttle = 1366;

#define RCTRIGGER_PIN 5 

unsigned long RCVal; 

#define ECHO_PIN 13
#define TRIGGER_PIN 12
#define MAX_DISTANCE 40
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() 
{ 
  steerServo.attach(9);  // attaches the servo on pin 9 to the servo object 
  throttleServo.attach(3);
  Serial.begin(9600);
  pinMode(RCTRIGGER_PIN, INPUT);
  throttleServo.write(1366);
  delay(1000);
  throttleServo.write(1500);
  //delay(1000);
  //throttleServo.write(1366);

} 
 
 
void loop() 
{ 
  delay(50);
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
  throttleServo.writeMicroseconds(throttle);
  delay(1000);
 
  if(Serial.available()) 
    throttle = Serial.parseInt(); 
    
  RCVal = pulseIn(RCTriggerPin, HIGH);
  delay(3000); // wait 3 seconds
  
  Serial.println(RCVal);
  
  delay(20);
  
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    steerServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    steerServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} 
