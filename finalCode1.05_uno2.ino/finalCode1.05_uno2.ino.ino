#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//bluetooth pins
#define RX 0
#define TX 1
//pir pin
#define pir 11
//pir leds pin
#define leds 12 
//humidity sensor pin
#define dhtpin 8
//soil moisture sensor pin
#define soil_adc A0
//flame sensor pin
#define flame 10
//fire alarm buzzer pin
#define buzzer2 4
//fan pin
#define fan 9 
//ldr pin
#define ldr A1
#define led 6 
#define warningLed 13
#define bluetoothLed 7
#define soilLed 2

SoftwareSerial myserial(RX,TX);

#define dhttype DHT11
DHT dht(dhtpin,dhttype);

void setup() {
  Serial.begin(9600);
  myserial.begin(9600);
  dht.begin();   
  pinMode(pir,INPUT);
  pinMode(leds,OUTPUT);
  pinMode(soil_adc,INPUT);
  pinMode(flame,INPUT);
  pinMode(buzzer2,OUTPUT);
  pinMode(warningLed,OUTPUT);
  pinMode(bluetoothLed,OUTPUT);
  pinMode(ldr,INPUT);
  pinMode(led,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(soilLed,OUTPUT);
  noTone(buzzer2);
}

void loop() {
  bluetoothControl();
  openLeds();
  LDR();
  flameanddht();
  soilsensor();
}


void LDR(){
  Serial.println(analogRead(ldr));
  if(analogRead(ldr) <= 512)
    digitalWrite(led,HIGH);
  else
     digitalWrite(led,LOW);
  }
 
void soilsensor(){
  int soil=analogRead(soil_adc);
  Serial.println(soil);
  delay(25);
  if(soil > 500){
   digitalWrite(soilLed,HIGH);
  }
  else{
    digitalWrite(soilLed,LOW);
    }
  
  }
  
void flameanddht(){
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   int val = digitalRead(flame);
   Serial.println(h);
   Serial.println(t);
   //Serial.println(val);
   if(val == LOW || t > 40){
      tone(buzzer2,3000);
      digitalWrite(warningLed,HIGH);
      digitalWrite(fan,HIGH);
       }
   else if(h > 50){
      digitalWrite(fan,HIGH);
      }
   else{
    digitalWrite(warningLed,LOW);
      noTone(buzzer2);
     digitalWrite(fan,LOW);
     }
    }

void openLeds(){
  //Serial.println(digitalRead(pir));
  if(digitalRead(pir)){
    digitalWrite(leds,HIGH);
    }
  else{
    digitalWrite(leds,LOW);
    }
  }
 

void bluetoothControl(){
  if(myserial.available()){
    switch(myserial.read()){
        case 'F' : {
        digitalWrite(bluetoothLed,HIGH);
        break;
        }
        case 'B' : {
        digitalWrite(bluetoothLed,LOW);
        break;
        }
//        case 'c' : {
//        digitalWrite(fan,HIGH);
//        break;
//        }
//        case 'd' : {
//        digitalWrite(fan,LOW);
//        break;
//        }
//        case 'e' : {
//        servo_right();
//        break;
//        }
//        case 'f' : {
//        servo_left();
//        break;
// 
//     }
    }
  }
}
