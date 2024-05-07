#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
 
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    
    for (byte i = 0; i < rfid.uid.size; i++) {
      
      if (rfid.uid.uidByte[i] < 0x10) {
        Serial.print("0");
      }
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();
  }

  // Check if data is available on the serial port
  if (Serial.available() > 0) {
    // Read data from serial port
    
   
    delay(1500);
  }
}
