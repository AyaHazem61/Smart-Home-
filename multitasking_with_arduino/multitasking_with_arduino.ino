/*  --------use this pseudocode to multitask with arduino-------
    intiate previous time to zero
    assign the wanted delay time 
    assign time now varialbe to millis func
    --------- in loop func ---------
    print line one
    if delayTime passed "aka : time now >= previous time + delayTime"
       update previous time to mills or += delayTime
       print line two
       action
    --------- each block of code has its own delay time and previous time variables -------
*/

void setup() {


}

void loop() {
/*  get character from keypad
 *  store it in string text
 *  repeat until the charcter is '=' then break
 */
/* bug 1 : text would either be erased every turn
           or if it was declared before loop func it would not be erased at all
*/

  String text = "";
  char key = Keypad.getKey();
  if(key){
    if(key == '=' && text == pass){
      lcd.clear(); lcd.setCursor(0,0); lcd.print("Correct Password" );
      lcd.setCursor(3,1); lcd.print("Welcome." );
      //openDoor
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








  
//  lcd.setCursor(0,0); lcd.print("Enter Password : "); lcd.setCursor(0,1);
//     String text = "";
//     while(true){            //>>>>>>>>>>>>>>>>infinte loop
//     char key = keypad.getKey();
//     if(key == '=' && text == pass){
//      lcd.clear(); lcd.setCursor(0,0); lcd.print("Correct Password" );
//      lcd.setCursor(3,1); lcd.print("Welcome." );
//      return true;
//      }
//     else if(key == '=' && text != pass) {
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("Wrong Password");
//      lcd.setCursor(0,1);
//      lcd.print("Try again.");
//      delay(1000);
//      }
//      else if(key){
//        text += String(key);
//        lcd.print("*");
//      }
//     }
//    }

}
