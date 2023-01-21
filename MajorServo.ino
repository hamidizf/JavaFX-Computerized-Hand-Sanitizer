#include <Servo.h>
Servo myservo;
#define Sensor 7 // Sensor on Pin D7
int angle;
const unsigned long number = 800;
unsigned long previousTime = 0;
void setup() 
{
  Serial.begin(9600);// baud rate
  pinMode(Sensor, INPUT);
  myservo.attach(3);  // Servo motor on Pin D3
}
void loop() {
  
 unsigned long currentTime = millis(); 
 if (currentTime - previousTime >=number){  //sending sensor's data to Java
  const auto SensorValue= digitalRead(Sensor);
   const byte data[] = {0, 0, highByte(SensorValue), lowByte(SensorValue)};
 Serial.write(data, 4);
    Serial.println();
     previousTime = currentTime;
 }
   

   delay(5);

    const auto receivedData = Serial.read();
if ((receivedData== 200)||(receivedData== 255)) // rotating the servo at desired angle if the button is pressed on the hand is detected
    {
  for ( ;angle >= 5; angle -= 1) 
   { 
    myservo.write(angle);             
    delay(2);                        
   }
    }
else
    {
  for ( ;angle <= 80; angle += 1) 
  { 
    myservo.write(angle);             
    delay(4);                        
   }
    }
}
