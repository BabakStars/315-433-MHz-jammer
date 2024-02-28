#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27,16,2);
//*********************************************Setup Keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//*********************************************Config Pin_Keypad
const byte Pin_ROW1 = 6;
const byte Pin_ROW2 = 7;
const byte Pin_ROW3 = 8;
const byte Pin_ROW4 = 9;
const byte Pin_column1 = 10;
const byte Pin_column2 = 11;
const byte Pin_column3 = 12;
const byte Pin_column4 = 13;
byte rowPins[ROWS] = {Pin_ROW1, Pin_ROW2, Pin_ROW3, Pin_ROW4};
byte colPins[COLS] = {Pin_column1, Pin_column2, Pin_column3, Pin_column4};
//*********************************************Layout Keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
//*********************************************Start Program


char a;
String FP[5];
//String fr;
int ff4;
int ff3;

void setup() {
  Wire.begin();
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("Starting..");
  lcd.setCursor(0,1);
  lcd.print("Babak Stars");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("433MHz: A");
  lcd.setCursor(0,1);
  lcd.print("315MHz: B");
  lcd.setCursor(11,1);
  lcd.print("Off:C");
}

void loop() {
  L:
  // put your main code here, to run repeatedly:
  for(int T=0 ; T < 1 ; T++)
    { delay(60);
     do
     {
     a=scankey();
     }while(a!='&');
     do
     {
     a=scankey();
     }while(a=='&');
      Serial.println(a);
      if(a == 'A')
      {
        
        Serial.println("Type for 433:");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("433 MHz: A");
        for(int i=0 ; i < 6 ; i++)
       {
         do
         {
         a=scankey();
         }while(a!='&');
         do
         {
         a=scankey();
         }while(a=='&');
            FP[i] = a;
            Serial.print(a);
            lcd.setCursor(i,1);
            lcd.print(a);
            delay(100);
            if(FP[2] == "#" || FP[3] == "#" || FP[4] == "#" || FP[5] == "#")
            {
              Serial.println();
              ff4 = (FP[0] + FP[1] + FP[2]+ FP[3]+ FP[4]).toInt();
              if(ff4 >= 100 && ff4 <= 12000 )
              {
                Serial.println(ff4);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("433 MHz:");
                lcd.setCursor(0,1);
                lcd.print(ff4);                
                noTone(5);
                tone(3,ff4);
              }
              else
              {
                Serial.println("Invalid FRQ");
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Invalid FRQ");
                delay(4000);
                noTone(3);
                displayer();
              }
              i=0;
              FP[2]="";
              FP[3]="";
              FP[4]="";
              FP[5]="";
              goto L;
            }
       }
///////////////////
              Serial.println();
              Serial.println("Invalid FRQ");
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Invalid FRQ");
                delay(4000);
              noTone(3);
      }


      if(a == 'B')
      {
        
        Serial.println("Type for 315:");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("315 MHz: B");
        for(int i=0 ; i < 6 ; i++)
       {
         do
         {
         a=scankey();
         }while(a!='&');
         do
         {
         a=scankey();
         }while(a=='&');
            FP[i] = a;
            Serial.print(a);
            lcd.setCursor(i,1);
            lcd.print(a);
            delay(100);
            if(FP[2] == "#" || FP[3] == "#" || FP[4] == "#" || FP[5] == "#")
            {
              Serial.println();
              ff3 = (FP[0] + FP[1] + FP[2]+ FP[3]+ FP[4]).toInt();
              if(ff3 >= 100 && ff3 <= 12000 )
              {
                Serial.println(ff3);
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("315 MHz:");
                lcd.setCursor(0,1);
                lcd.print(ff3);   
                noTone(3);
                tone(5,ff3);
              }
              else
              {
                Serial.println("Invalid FRQ");
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Invalid FRQ");
                delay(4000);
                noTone(5);
                displayer();
              }
              i=0;
              FP[2]="";
              FP[3]="";
              FP[4]="";
              FP[5]="";
              goto L;
            }
       }
///////////////////
              Serial.println();
              Serial.println("Invalid FRQ");
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Invalid FRQ");
                delay(4000);
              noTone(5);
      }
}
      if(a == 'C')
      {
        noTone(5);
        noTone(3);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Standby");
        delay(4000);
      }
      displayer();
}
int scankey(){

char customKey = customKeypad.getKey();
 
 
  if (customKey)
  { //Serial.println(customKey);
    return customKey;
    
  }
  else
  {
    return '&';
  }

  
}
void displayer(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("433MHz: A");
  lcd.setCursor(0,1);
  lcd.print("315MHz: B");
  lcd.setCursor(11,1);
  lcd.print("Off:C");
}
