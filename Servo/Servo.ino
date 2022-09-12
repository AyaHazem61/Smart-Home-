#include <Servo.h>

Servo ser;

#define SERVO 12

void openDoor(){
  for(int i = 50 ; i <= 124 ; i++){
    ser.write(i);
    delay(100);
    }
  }

void closeDoor(){
  for(int i = 124 ; i > 50 ; i--){
    ser.write(i);
    delay(100);
    }
  }
  
void setup() {
  ser.attach(SERVO);
}

void loop() {
  openDoor();
  delay(1000);
  closeDoor();
}
