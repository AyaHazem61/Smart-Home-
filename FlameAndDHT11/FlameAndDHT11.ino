#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define dhtpin 50
#define dhttype DHT11

DHT dht(dhtpin,dhttype);

#define flame 52
#define buzzer 12

#define fan 8

void setup(){
  
  pinMode(flame,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(fan,OUTPUT);
  dht.begin();
  Serial.begin(9600);
  
  }

void loop(){
  flameanddht();
  }
void flameanddht(){
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   int val = digitalRead(flame);
   Serial.println(h);
   Serial.println(t);
   Serial.println(val);
   if(val == LOW || t > 40){
      digitalWrite(buzzer,HIGH);
       }
   else if(h > 50){
      digitalWrite(fan,HIGH);
      }
   else{
      digitalWrite(buzzer,LOW);
      digitalWrite(fan,LOW);
     }
    }
