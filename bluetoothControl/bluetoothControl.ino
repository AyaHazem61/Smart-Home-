#include <SoftwareSerial.h>
#define RX 0
#define TX 1
SoftwareSerial myserial(RX,TX);

#include <Servo.h>
Servo Myservo;
#define SERVO 2
#define led 8
#define leds 4
#define fan 5
#define buzzer1 6
#define buzzer2 7


void servo_right()
{
  for(int pos = 50; pos<= 180; pos++){   
  Myservo.write(pos);
  delay(50);}
}

void servo_left()
{
  for(int pos = 150; pos >= 50; pos--){
  Myservo.write(pos);
  delay(50);
  }
}

void setup() {
  Serial.begin(9600);
  myserial.begin(9600);
  Myservo.attach(SERVO);
  
  pinMode(buzzer1,OUTPUT);
  pinMode(buzzer2,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(leds,OUTPUT);
  pinMode(fan,OUTPUT);

}

void loop() {
   if(myserial.available()){
    switch(myserial.read()){
      case 'A' : {
        digitalWrite(led,HIGH);
        break;
        }
       case 'B' : {
        digitalWrite(led,LOW);
        break;
        }
        case 'C' : {
        digitalWrite(leds,HIGH);
        break;
        }
        case 'D' : {
        digitalWrite(leds,LOW);
        break;
        }
        case 'E' : {
        digitalWrite(fan,HIGH);
        break;
        }
        case 'F' : {
        digitalWrite(fan,LOW);
        break;
        }
        case 'G' : {
        servo_right();
        break;
        }
        case 'H' : {
        servo_left();
        break;
        }
        case 'I' : {
        digitalWrite(buzzer1,HIGH);
        break;
        }
        case 'J' : {
        digitalWrite(buzzer1 , LOW);
        break;
        }
        case 'K' : {
        digitalWrite(buzzer2,HIGH);
        break;
        }
        case 'L' : {
        digitalWrite(buzzer2 , LOW);
        break;
        }
      }
    }
    }
