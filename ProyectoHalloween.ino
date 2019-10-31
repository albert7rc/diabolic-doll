
//ultrasonidos
#include <HCSR04.h>                                     //Include to arduino the ultrasonic sensor
UltraSonicDistanceSensor distanceSensor(13, 12);        // Initialize sensor that uses digital pins 13 and 12.
boolean movimiento;                                     
int d = 100;
int rep;

//motor
#include <Servo.h>                                    //Include to arduino the servo
Servo myservo;                                        //Create servo object to control a servo
Servo myservo2;                                       //Create servo object to control a servo

void setup() {
  //ultrasonidos
  Serial.begin(9600);                                 // Initialize serial connection so that we can print values from sensor.
  movimiento = false;

  //LED's
  pinMode(2, OUTPUT);                                 //The LED's outputs are 2 and 3
  pinMode(3, OUTPUT);

  //motor
  myservo.attach(9);                                 //The UltrasonicSensor's outputs are 8 and 9
  myservo2.attach(8);

}

void loop() {

  //ultrasonidos
  Serial.println(distanceSensor.measureDistanceCm());//Print the distance from the UltraSonic Sensor to the closer object
  delay(10);
  if (distanceSensor.measureDistanceCm() < d) {      //The boolean "movimiento" are true if the distance is lower than "d"
    movimiento = true;
  } else {
    movimiento = false;
  }

  if (movimiento == true) {                         //When something get close, active the servos and the LEDs
    myservo.write(0);
    myservo2.write(70);                             //The servos move 70º at first
    for(rep=0;rep<3;rep++){
    blinkEyes();                                    //During the servo movment, the LEDs blink 
    }
    rep=0;
    myservo.write(70);                              //The servos get back to the first position
    myservo2.write(0);
  for(rep=0;rep<3;rep++){                           //During the servo movment, the LEDs blink
    blinkEyes();
    }
    rep=0;
  } else {
    digitalWrite(3, LOW);                           //Turn off the LED

  }
}

void blinkEyes()                                    //This void do the LED's blink
{
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(100);
  digitalWrite(3, HIGH);
  digitalWrite(2, LOW);
  delay(100);
}
