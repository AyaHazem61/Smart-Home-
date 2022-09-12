#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include<Servo.h>

//keypad pins
const byte ROWS = 4 , COLS = 4;
byte pinRows[ROWS] = {18,19,20,21};

byte pinCols[COLS] =  {14,15,16,17}; 
//door buzzer
#define buzzer1 18

//servo pin
#define servoPin 2

//ultrasonic pins
#define echo 52
#define trig 50

LiquidCrystal_I2C lcd(0x27, 16, 2);
char keys[ROWS][COLS] = {{'1', '2', '3', 'A'},
                        {'4', '5', '6', 'B'},
                      {'7', '8', '9', 'C'},
  {'*', '0', '=', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys) , pinRows , pinCols, ROWS , COLS);
bool password = false; byte ct = 0;
const String pass = "1234" ;
Servo Myservo;
float distant, disC;

void setup() {
  lcd.init();
  lcd.backlight();
  Myservo.attach(servoPin);
  pinMode(buzzer1, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  Serial.begin(9600);
  noTone(buzzer1);

}
void loop() {
  if (true) {
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("Welcome.");
    delay(1000);
    password = checkPass();
    if (password) {
      servo_left();
      delay(2000);
      servo_right();
      lcd.clear();
    }
    else {
      lcd.clear(); lcd.setCursor(0, 0); lcd.print("Warning!");
      tone(buzzer1, 6000);
      long t = millis();
      while (millis() < t + 5500) {
        lcd.setCursor(0, 1); lcd.print((millis() - t) / 1000);
      }
      noTone(buzzer1);
      lcd.clear();
    }
  }

}
bool checkPass() {
  for (int i = 0 ; i < 3; i++) {
    lcd.setCursor(0, 0); lcd.print("Enter Password : "); lcd.setCursor(0, 1);
    String text = "";
    while (true) {
      char key = keypad.getKey();
      Serial.println(key);
      if (key == '=' && text == pass) {
        lcd.clear(); lcd.setCursor(0, 0); lcd.print("Correct Password" );
        lcd.setCursor(3, 1); lcd.print("Welcome." );
        return true;
      }
      else if (key == '=' && text != pass) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong Password");
        lcd.setCursor(0, 1);
        lcd.print("Try again.");
        delay(1000);
        lcd.clear();
        break;
      }
      else if (key) {
        text += String(key);
        lcd.print(key);
      }
    }
  }
  return false;
}


void servo_right()
{
  for (int pos = 50; pos <= 124; pos++) {
    Myservo.write(pos);
    delay(100);
  }
}

void servo_left()
{
  for (int pos = 123; pos >= 50; pos--) {
    Myservo.write(pos);
    delay(100);
  }
}


float ultrasonic()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  distant = pulseIn(echo, HIGH);
  disC = distant * 0.5 * 0.034;
  Serial.println(disC);
  return disC;
}
