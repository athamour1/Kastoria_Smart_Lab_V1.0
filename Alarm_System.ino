#include <Keypad.h>
#include <Password.h>
#include <LiquidCrystal.h>
 
String newPasswordString; //hold the new password
char newPassword[6];      //charater string of newPasswordString

const int rs = 41, en = 40, d4 = 45, d5 = 44, d6 = 43, d7 = 42;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int RedPin = 48;
int GreenPin = 49;
int BPin = 46;
int DoorPin = 13;
int AlarmPinOut = 34;
int DoorPinOut = 36;
int Door;
int AlarmArmed = 0;

//int DoorPin = 30;
//int WindowPin = 31;
 
//initialize password to 1333
//you can use password.set(newPassword) to overwrite it
Password password = Password( "1333" );
 
byte maxPasswordLength = 6;
byte currentPasswordLength = 0;
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
 
//Define the keymap
char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
//// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {5,4,3,2}; //connect to row pinouts
 
// Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.
byte colPins[COLS] = {9,8,7,6}; //connect to column pinouts
 
// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 
void setup()
{  // put your setup code here, to run once:
   pinMode(RedPin, OUTPUT);
   pinMode(GreenPin, OUTPUT);
   pinMode(BPin, OUTPUT);
   pinMode(AlarmPinOut, OUTPUT);
   pinMode(DoorPinOut, OUTPUT);
   pinMode(DoorPin, INPUT);
   lcd.begin(16, 2);
   lcd.print("Alarm");
   Serial.begin(9600);
}
 
void loop()
{
  keypadprocess();
 
  Door = digitalRead(DoorPin);
  //Serial.println(Door);
  //delay(100000);
  if (Door == 0 && AlarmArmed == 1)
  {
    digitalWrite(DoorPinOut, HIGH);
    delay(500);
    digitalWrite(DoorPinOut, LOW);
    int i = 0;
    while(AlarmArmed == 1 && i<100)
    {
       keypadprocess();
       digitalWrite(BPin, HIGH);      
       delay(100);
       digitalWrite(BPin, LOW);
       delay(100);
       i++;
    }

    checkPassword();
    
    if(AlarmArmed == 1)
    {
      digitalWrite(AlarmPinOut, HIGH);
      delay(500);
      digitalWrite(AlarmPinOut, LOW);
    }
  }
}


void keypadprocess()
{
  lcd.setCursor(0, 1);
       char key = keypad.getKey();
       if (key != NO_KEY)
       {
        delay(60);
        switch (key)
        {
          case 'A': break;
          case 'B': break;
          case 'C': break;
          case 'D': break;
          case '#': checkPassword(); break;     
          default: processNumberKey(key);
        }
       }
}
 
void processNumberKey(char key)
{
   Serial.print(key);
   //lcd.print(key);
   currentPasswordLength++;
   password.append(key);
   if (currentPasswordLength == maxPasswordLength)
   {
      checkPassword();
   }

   if (currentPasswordLength == 1)
   {
    lcd.print("*");
   }
   else if (currentPasswordLength == 2)
   {
    lcd.print("**");
   }
   else if (currentPasswordLength == 3)
   {
    lcd.print("***");
   }
   else if (currentPasswordLength == 4)
   {
    lcd.print("****");
   }
   else if (currentPasswordLength == 5)
   {
    lcd.print("*****");
   }
   else if (currentPasswordLength == 6)
   {
    lcd.print("******");
   }
}

void checkPassword()
{
   if (password.evaluate())
   {  
      lcd.print("Password OK");
      
      Serial.println(" OK.");
      digitalWrite(BPin, HIGH);      
      digitalWrite(GreenPin, HIGH);
      delay(1500);
      digitalWrite(GreenPin, LOW);
      digitalWrite(BPin, LOW);
      
      if(AlarmArmed == 0)
      {
        AlarmArmed = 1;
        lcd.begin(16, 2);
        lcd.print("Alarm Armed");
      }
      else
      {
        AlarmArmed = 0;
        lcd.begin(16, 2);
        lcd.print("Alarm");
      }
      
    
   }
   else
   {
      lcd.print("Password Wrong");
      
      Serial.println(" Wrong passwowrd!");
      digitalWrite(BPin, HIGH);
      digitalWrite(RedPin, HIGH);
      delay(1500);
      digitalWrite(RedPin, LOW);
      digitalWrite(BPin, LOW);
       
      if(AlarmArmed == 1)
      {
        digitalWrite(AlarmPinOut, HIGH);
        delay(500);
        digitalWrite(AlarmPinOut, LOW);
      }
      
      lcd.begin(16, 2);
      lcd.print("Alarm");
   }
   resetPassword();
}

void resetPassword()
{
   password.reset();
   currentPasswordLength = 0;
}
 
