#include<EEPROM.h>

int eeprom_size = 4096;

void setup() {
  Serial.begin(115200);
  Serial.println("To READ EEPROM --> Write r \nTo CLEAR EEPROM --> Write c \n");
  Serial.printf("EEPROM size: %d\n", eeprom_size);  
}

void loop() {
  if(Serial.available() > 0){
    String c = Serial.readString();
    if(c.indexOf("r\r\n") == 0){
      Serial.println("EEPROM contains");
      EEPROM.begin(eeprom_size);
      // Reading EEPROM data
      for (int i = 0; i < eeprom_size; i++){
           byte c = EEPROM.read(i);
           Serial.printf("%c|", c);
        }
    
      Serial.println();
      EEPROM.end();
    }
    else if(c.indexOf("c\r\n") == 0){
      Serial.println("Going to clear EEPROM, Are you sure? \ny/n (write y to continue, n to abort)");
      do{
        Serial.print('.');
        delay(50);      
      }while(!Serial.available());
      Serial.println();
      String t = Serial.readString();
      if(t.indexOf("y\r\n") == 0){
        Serial.println("Clearing EEPROM");
        EEPROM.begin(eeprom_size);
        // Erasing EEPROM data
        for (int i = 0; i < eeprom_size; i++){  
           EEPROM.write(i, 0);
        }
        Serial.println("Done erasing");
        EEPROM.commit();
        EEPROM.end();
      }
      else if(t.indexOf("n\r\n") == 0){
        return;
      }
    }
    else Serial.println("Unknown command! r --> read, c --> clear");
  }
  
}
