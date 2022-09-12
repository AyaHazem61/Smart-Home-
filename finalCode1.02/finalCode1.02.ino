#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include<Servo.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//keypad pins
const byte ROWS = 4 , COLS = 4;
byte pinRows[ROWS] = {11,10,9,8};

byte pinCols[COLS] =  {7,6,5,4};

//door buzzer
#define buzzer1 18

//bluetooth pins
#define RX 0
#define TX 1

//servo pin 
#define servoPin 2

//ultrasonic pins
#define echo 52
#define trig 50

//pir pin
#define pir 20

//pir leds pin
#define leds 15

//humidity sensor pin
#define dhtpin 48

//soil moisture sensor pin
#define soil_control 34
#define soil_adc A14

//flame sensor pin
#define flame 46

//fire alarm buzzer pin
#define buzzer2 3

//fan pin
#define fanA 10
#define fanB 11
#define fanE 12 //pwm

//fan pin
#define curtainA 10
#define curtainB 11
#define curtainE 12 //pwm

//ldr pin
#define ldr A1

//ldr led pin
#define led 21

LiquidCrystal_I2C lcd(0x27,16,2);
char keys[ROWS][COLS] = {{'1','2','3','A'},
                        {'4','5','6','B'},
                        {'7','8','9','C'},
                        {'*','0','=','D'}
                        };                 
Keypad keypad = Keypad(makeKeymap(keys) , pinRows , pinCols, ROWS , COLS);
bool password = false; byte ct = 0;
const String pass = "1234" ;
SoftwareSerial myserial(RX,TX);
Servo Myservo;
float distant,disC;
#define dhttype DHT11
DHT dht(dhtpin,dhttype);


void setup() {
  Serial.begin(9600);
  myserial.begin(9600);
  lcd.init();
  lcd.backlight();
  Myservo.attach(servoPin);
  dht.begin();   
  pinMode(buzzer1,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(pir,INPUT);
  pinMode(leds,OUTPUT);
  pinMode(soil_adc,INPUT);
  pinMode(soil_control,OUTPUT);
  digitalWrite(soil_control,LOW);
  pinMode(flame,INPUT);
  pinMode(buzzer2,OUTPUT);
  
  pinMode(fanA,OUTPUT);
  pinMode(fanB,OUTPUT);
  pinMode(fanE,OUTPUT);
  
  pinMode(curtainA,OUTPUT);
  pinMode(curtainB,OUTPUT);
  pinMode(curtainE,OUTPUT);
  
  pinMode(ldr,INPUT);
  pinMode(led,OUTPUT);

  noTone(buzzer1);
}

void loop() {
  bluetoothControl();
  doorControl();
//  openLeds();
//  curtain();
  flameanddht();
  soilsensor();
}

void doorControl(){
   if(ultrasonic() < 20.0){
    lcd.clear(); lcd.setCursor(0,0); lcd.print("Welcome.");
    delay(1000);
    password = checkPass();
    if(password){
      servo_right();
      delay(2000);
//      long t = millis(); //>>>>>>>>>>>>>>>>loop
//      while(millis() < t + 10000){
////        openLeds();
////        flameanddht();
////        curtain();
////        soilsensor();
//      }
      servo_left();
      lcd.clear();
      }
   else{
         lcd.clear(); lcd.setCursor(0,0); lcd.print("Warning!");
         //tone(buzzer1,6000);
         long t = millis(); //>>>>>>>>>>>>>>>>loop
          while(millis() < t + 5500){
          lcd.setCursor(0,1); lcd.print((millis() - t)/1000);
          }
         //noTone(buzzer1);
         lcd.clear();
      }
    }
  }

bool checkPass(){
  for(int i = 0 ; i < 3;i++){ //>>>>>>>>>>>>>>>>loop
     lcd.setCursor(0,0); lcd.print("Enter Password : "); lcd.setCursor(0,1);
     String text = "";
     while(true){            //>>>>>>>>>>>>>>>>infinte loop
     char key = keypad.getKey();
     if(key == '=' && text == pass){
      lcd.clear(); lcd.setCursor(0,0); lcd.print("Correct Password" );
      lcd.setCursor(3,1); lcd.print("Welcome." );
      return true;
      }
     else if(key == '=' && text != pass) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Wrong Password");
      lcd.setCursor(0,1);
      lcd.print("Try again.");
      delay(1000);
      }
      else if(key){
        text += String(key);
        lcd.print("*");
      }
     }
    }
    return false;
  }

void curtain(){
  if(analogRead(ldr) <= 512)
    openCurtain();
  else
    closeCurtain();
  }
 
void soilsensor(){
  digitalWrite(soil_control,HIGH);
  delay(25);
  int soil=analogRead(soil_adc);
  delay(25);
  digitalWrite(soil_control,LOW);
  if(soil < 50){
    lcd.clear(); lcd.setCursor(0,0); lcd.print("Plantes needs");
    lcd.setCursor(3,1); lcd.print(" water.");
      }
  }
  
void flameanddht(){
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   int val = digitalRead(flame);
   if(val == LOW || t > 40){
      tone(buzzer2,3000);
       }
   else if(h > 50){
      openFan();
      }
   else{
      noTone(buzzer2);
      closeFan();
     }
    }

void servo_right()
{
  for(int pos = 50; pos<= 124; pos++){   //>>>>>>>>>>>>>>>>loop
  Myservo.write(pos);
  delay(100);}
}

void servo_left()
{
  for(int pos = 123; pos >= 50; pos--){  //>>>>>>>>>>>>>>>>loop
  Myservo.write(pos);
  delay(100);
  }
}

float ultrasonic()
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  distant = pulseIn(echo,HIGH);
  disC = distant*0.5*0.034;
  Serial.println(disC);
  return disC;
}
void openLeds(){
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
        openFan();
        break;
        }
        case 'F' : {
        closeFan();
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

  void openFan(){
    digitalWrite(fanA,HIGH);
    digitalWrite(fanB,HIGH);
    analogWrite(fanE,255);
  }
  
  void closeFan(){
    digitalWrite(fanA,LOW);
    digitalWrite(fanB,LOW);
    analogWrite(fanE,0);
  }

  void openCurtain(){
    digitalWrite(curtainA,HIGH);
    digitalWrite(curtainB,HIGH);
    analogWrite(curtainE,255);
  }
  
  void closeCurtain(){
    digitalWrite(curtainA,LOW);
    digitalWrite(curtainB,LOW);
    analogWrite(curtainE,0);
  }
  
   
