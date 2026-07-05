#include <ESP32Servo.h>

int servopin = 14;

//create a servo object
Servo myservo;

void setup()
{
  myservo.attach(servopin);//attach servo on Pin 14
}


void loop()
{
    // tell servo to go to position 180 degree
    myservo.write(180);
    delay(800); // Wait for 15 ms for servo to move

    // tell servo to go to position 0 degree
    myservo.write(0);
    delay(800); // Wait for 15ms for servo to move
}
