#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include<Servo.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

LiquidCrystal_I2C lcd(0x27,16,2);
const byte ROWS = 4 , COLS = 4;
byte pinRows[ROWS] = {2,3,4,5};
byte pinCols[COLS] = {6,7,8,9};
char keys[ROWS][COLS] = {{'1','2','3','A'},
                        {'4','5','6','B'},
                        {'7','8','9','C'},
                        {'*','0','=','D'}
                        };                 
Keypad keypad = Keypad(makeKeymap(keys) , pinRows , pinCols, ROWS , COLS);
#define buzzer1 10
bool password = false; byte ct = 0;
const String pass = "1234" ;

#define RX 0
#define TX 1
SoftwareSerial myserial(RX,TX);
byte ct0 = 0 , ct1 =0 , ct2 = 0 , ct3 = 0 , ct4 = 0,ct5 = 0;

Servo Myservo;
#define servoPin 11
#define echo 12
#define trig 13
#define pir 14
#define leds 15
float distant,disC;


#define dhtpin 16
#define dhttype DHT11
DHT dht(dhtpin,dhttype);
#define soil_control 17
#define soil_adc A0
#define flame 18
#define buzzer2 19
#define fan 20

#define ldr A1
#define led 21

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(buzzer1,OUTPUT);
  password = false ;

  Serial.begin(9600);
  myserial.begin(9600);

  Myservo.attach(servoPin);    //connect to digital pin 
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(pir,INPUT);
  pinMode(leds,OUTPUT);

  pinMode(soil_adc,INPUT);
  pinMode(soil_control,OUTPUT);
  digitalWrite(soil_control,LOW);
  pinMode(flame,INPUT);
  pinMode(buzzer2,OUTPUT);
  pinMode(fan,OUTPUT);
  dht.begin();

  pinMode(ldr,INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
 //password
 while(!password){
    password = checkPass();
    if(password){
      break;
      }
    else{
      ct++;
      if(ct == 3){
         lcd.clear(); lcd.setCursor(0,0); lcd.print("Warning!");
         digitalWrite(buzzer1,HIGH);
         long t = millis();
         while(millis() < t + 5500){
          lcd.setCursor(0,1); lcd.print((millis() - t)/1000);
          }
         digitalWrite(buzzer1,LOW);
         ct = 0 ;
         lcd.clear();}
      }
    }
 //bluetooth setting
   bluetoothControl();
 //sensors
  //door&ultrasonic
  if(ultrasonic() < 50.0){
    servo_right();
    delay(10000);
    servo_left();
    }
  //pir&leds
  openLeds();
  //ldr&led
  openLed();
  //dht11&flame&buzzer&fan
  flameanddht();
  //soilsensors
  soilsensor();

}

bool checkPass(){
  lcd.setCursor(0,0); lcd.print("Enter Password : "); lcd.setCursor(0,1);
  String text = "";
  while(true){
    char key = keypad.getKey();
    if(key == '=' && text == pass){
      lcd.clear(); lcd.setCursor(0,0); lcd.print("Correct Password" );
      lcd.setCursor(0,1); lcd.print("Welcome." );
      return true;
      }
     else if(key == '=' && text != pass) {
      lcd.clear();
      return false;
      }
      else if(key){
        text += String(key);
        lcd.print("*");
      }
    }
  }

void openLed(){
  if(analogRead(ldr) <= 512)
    digitalWrite(led,HIGH);
  else
    digitalWrite(led,LOW);
  }
 
void soilsensor(){
  digitalWrite(soil_control,HIGH);
  delay(25);
  int soil=analogRead(soil_adc);
  delay(25);
  digitalWrite(soil_control,LOW);
  if(soil<50){
      Serial.print("warrning!!:plantes needs water");
      }
  }
  
void flameanddht(){
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   int val = digitalRead(flame);
   if(val == LOW || t > 40){
      digitalWrite(buzzer1,HIGH);
       }
   else if(h > 50){
      digitalWrite(fan,HIGH);
      }
   else{
      digitalWrite(buzzer1,LOW);
      digitalWrite(fan,LOW);
     }
    }

void servo_right()
{
  for(int pos=0;pos<=180;pos++){   
  Myservo.write(pos);
  delay(10);}
}

void servo_left()
{
  for(int pos=180;pos>=0;pos--){
  Myservo.write(pos);
  delay(10);}
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
  while(myserial.read()){
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
