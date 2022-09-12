#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

//soil moisture sensor pin
#define soil_control 17
#define soil_adc A0

void setup() {
  
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(soil_adc,INPUT);
  pinMode(soil_control,OUTPUT);
  digitalWrite(soil_control,LOW);
  
}

void loop() {
  soilsensor();
}

void soilsensor(){
  digitalWrite(soil_control,HIGH);
  delay(25);
  int soil=analogRead(soil_adc);
  delay(25);
  digitalWrite(soil_control,LOW);
  Serial.println(soil);
  if(soil < 50){
    lcd.clear(); lcd.setCursor(0,0); lcd.print("Plantes needs");
    lcd.setCursor(3,1); lcd.print(" water.");
      }
  }
