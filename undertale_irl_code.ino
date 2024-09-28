#include <LiquidCrystal.h>        
#include <Servo.h>                     
LiquidCrystal  lcd(2,3,4,5,6,7);       
Servo          ObjServo;               
const uint8_t  PinKey      = 12;       
const uint8_t  PinBeep     = 9;        
const uint8_t  PinServo    = 8;        
const uint8_t  PwdAccess[] ={4,4,3,2}; 
      uint8_t  PwdInput[]  ={0,0,0,0}; 
      uint8_t  Mode        = 102;      
      bool     ChangeMode  = 1;        
      bool     PressKey    = 0;        
      uint32_t PressTime   = 0;        
void setup(){
    pinMode(PinKey,   INPUT );                                                                                   
    pinMode(PinBeep,  OUTPUT);                                                                                   
    pinMode(PinServo, OUTPUT);                                                                                   
    ObjServo.attach(PinServo);                                                                                   
    lcd.begin(16, 2);                                                                                            
    for(int i=0; i<7; i++){lcd.createChar(i+1, symbol[i]);}                                                      
    ObjServo.write(0);                                                                                           
}

void loop(){
    if(digitalRead(PinKey)){                                                                                     
      tone(PinBeep, 1000, 100);                                                                                  
      while(digitalRead(PinKey)){delay(100);}                                                                    
      PressTime=millis(); PressKey=1;                                                                            
    if(Mode<100){

        if(ChangeMode){ChangeMode=0;                                                                             
            lcd.clear();                                                                                         
            lcd.setCursor(0,0); lcd.print("don't you dare");                                                   
            lcd.setCursor(0,1); for(int i=0; i<sizeof(PwdAccess); i++){lcd.print("*");}                          
        }
        if(PressKey){                                                                                            
            PwdInput[Mode]++; if(PwdInput[Mode]>9){PwdInput[Mode]=0;}                                            
        }   lcd.setCursor(Mode,1); if(millis()%400<200){lcd.print(PwdInput[Mode]);}else{lcd.print(" ");}         
        if((PressTime+2000)<millis()){PressTime=millis();                                                        
            lcd.setCursor(Mode,1); lcd.print(PwdInput[Mode]);                                                    
            Mode++; if(Mode>=sizeof(PwdAccess)){Mode=100;}                                                       
        }
    }else if(Mode==100){

        Mode=101; for(int i=0; i<sizeof(PwdAccess); i++){if(PwdAccess[i]!=PwdInput[i]){Mode=102;}} ChangeMode=1; 
    }else if(Mode==101){

        if(ChangeMode){ChangeMode=0;                                                                             
            tone(PinBeep, 2000, 1000);                                                                           
            lcd.clear();                                                                                         
            lcd.setCursor(0,0); lcd.print("you're going to"); 
            delay(500);
            lcd.setCursor(0,1); lcd.print("have bad time");
            delay(2000);                                                          
            ObjServo.write(180);                                                                                 
        }
        if(PressKey){                                                                                            
            Mode=102; ChangeMode=1;                                                                              
        }
    }else if(Mode==102){

        if(ChangeMode){ChangeMode=0;                                                                             
            tone(PinBeep, 200, 1000);                                                                            
            lcd.clear();                                                                                        
            lcd.setCursor(0,0); lcd.print("sans room is");
            delay(500);
            lcd.setCursor(0,1); lcd.print("locked");                                                     
            delay(2000);
            lcd.clear();
            delay(2000);                                                                                         
            ObjServo.write(0);                                                                                   
            lcd.setCursor(0,0); lcd.print("enter password");                                                 
        }
        if(PressKey){                                                                                            
            for(int i=0; i<sizeof(PwdAccess); i++){PwdInput[i]=0;}                                               
            Mode=0; ChangeMode=1;                                                                                
        }
    }
    PressKey=0;                                                                                                  
}
