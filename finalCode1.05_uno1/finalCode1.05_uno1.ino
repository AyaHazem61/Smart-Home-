#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include<Servo.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//keypad pins
const byte ROWS = 4 , COLS = 4;
byte pinRows[ROWS] = {13,12,11,10};

byte pinCols[COLS] =  {9,8,7,6};

//door buzzer
#define buzzer1 2

//servo pin 
#define servoPin 4

//ultrasonic pins
#define echo 5
#define trig 3


LiquidCrystal_I2C lcd(0x27,16,2);
char keys[ROWS][COLS] = {{'1','2','3','A'},
                        {'4','5','6','B'},
                        {'7','8','9','C'},
                        {'*','0','#','D'}
                        };                 
Keypad keypad = Keypad(makeKeymap(keys) , pinRows , pinCols, ROWS , COLS);
bool password = false; byte ct = 0;
const String pass = "1234" ;

Servo Myservo;
float distant,disC;


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Myservo.attach(servoPin);
  Myservo.write(124);  
  pinMode(buzzer1,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  noTone(buzzer1);
}

void loop() {
  doorControl();
}

void doorControl(){
   if(ultrasonic < 20){
    lcd.clear(); lcd.setCursor(0,0); lcd.print("Welcome!");
    delay(1000);
    password = checkPass();
    if(password){
      servo_left();
      long _t = millis();
      while(millis() < _t + 15000){
        lcd.clear(); lcd.setCursor(3,0);lcd.print("Welcome!" );
        lcd.setCursor(0,1); lcd.print("Closing In "+String((millis() - _t)/1000));
        }
      servo_right();
      lcd.clear();
      }
   else{
         lcd.clear(); lcd.setCursor(3,0); lcd.print("Warning!");
         tone(buzzer1,6000);
         long t = millis();
          while(millis() < t + 5500){
          lcd.setCursor(7,1); lcd.print((millis() - t)/1000);
          }
         noTone(buzzer1);
         lcd.clear();
      }
    }
  }

bool checkPass(){
  for(int i = 0 ; i < 3;i++){ 
     lcd.clear(); lcd.setCursor(0,0); lcd.print("Enter Password : "); lcd.setCursor(0,1);
     String text = "";
     while(true){           
     char key = keypad.getKey();
     if(key == '#' && text == pass){
      lcd.clear(); lcd.setCursor(0,0); lcd.print("Correct Password" );
      lcd.setCursor(3,1);
      return true;
      }
     else if(key == '#' && text != pass) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Wrong Password");
      lcd.setCursor(0,1);
      lcd.print("Try again.");
      delay(1000);
      break;
      }
      else if(key){
        text += String(key);
        lcd.print("*");
      }
     }
    }
    return false;
  }

void servo_right()
{
  for(int pos = 50; pos<= 124; pos++){   
  Myservo.write(pos);
  delay(100);}
}

void servo_left()
{
  for(int pos = 123; pos >= 50; pos--){  
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
