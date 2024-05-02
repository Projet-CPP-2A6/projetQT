#include <SimpleDHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


int pinDHT11 = 2;
int old_value = 0 ; 
boolean serialDataProcessed = false; 


SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  
  byte temperature = 0;
  byte humidity = 0; 
  int err = SimpleDHTErrSuccess;

  
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }

  
  Serial.print((int)temperature);  
   delay(1000);
    
    if ( Serial.available() ) {
        String str = Serial.readStringUntil('\n');
          if (str == "0") {
            lcd.print("ouvre 1") ;
            lcd.setCursor(0,1) ;
            lcd.print(" en risque !") ; 
            delay(2000);
            lcd.clear(); 
          }
          else if (str == "1") {
            lcd.print("Oeuvre 1 modifier !") ; 
            delay(2000);
            lcd.clear(); 
          }
          else if (str == "2") {
              lcd.print("ouvre 1") ; 
              lcd.setCursor(0,1) ; 
              lcd.print("non risque !") ; 
              delay(2000);
              lcd.clear(); 
            }
          else if (str == "3") { 
              lcd.print("Oeuvre 1 modifier !") ; 
               
              delay(2000);
              lcd.clear(); 
            }
    
          else {
            int spaceIndex = 0;
            while ((spaceIndex = str.indexOf(' ')) >= 0) {
                String word = str.substring(0, spaceIndex); 
                lcd.print("Risk detected! "); 
                lcd.setCursor(0, 1);
                lcd.print("ID: " + word); 
                delay(2000);
                lcd.clear(); 
                str = str.substring(spaceIndex + 1); 
            }
            serialDataProcessed = true ;
          }
     }

 }

  
  
