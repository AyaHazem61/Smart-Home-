//pir pin
#define pir 20

//pir leds pin
#define leds 15

//ldr pin
#define ldr A1

//ldr led pin
#define led 21

void setup() {
  Serial.begin(9600);
  
  pinMode(pir,INPUT);
  pinMode(leds,OUTPUT);

  pinMode(ldr,INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  openLeds();

}
void openLed(){
  Serial.println(analogRead(ldr));
  if(analogRead(ldr) <= 512)
    digitalWrite(led,HIGH);
  else
    digitalWrite(led,LOW);
  }
void openLeds(){
  Serial.println(digitalRead(pir));
//  if(digitalRead(pir)){
//    digitalWrite(leds,HIGH);
//    }
//  else{
//    digitalWrite(leds,LOW);
//    }
  }
