#include<EEPROM.h>

#define SER_MON_BAUD_RATE   115200  // 115.2 kBi/s
#define EEPROM_SIZE         4096    // Check your EEPROM's size
#define PROMPT_TIMEOUT      10000UL // Time to wait for a confirmation command when erasing (10s)

void setup() {
  Serial.begin(SER_MON_BAUD_RATE); // Start a serial port
  Serial.println("To READ EEPROM --> Write r \nTo CLEAR EEPROM --> Write c \n");
  Serial.printf("EEPROM size: %d\n", EEPROM_SIZE);  
}

void loop() {
  if(Serial.available() > 0){ // If there's something written to the serial monitor
    String c = Serial.readString(); // Read the available command
    if(c.indexOf("r\r\n") == 0){ // Compare the read data to 'r' (My serial monitor is set
                                 // to sent each command with a carri&age return & a new line
                                 // characters ("\r\n")
      Serial.println("EEPROM contains");
      EEPROM.begin(EEPROM_SIZE); // We must begin the EEPROM
      // Reading EEPROM data
      for (int i = 0; i < EEPROM_SIZE; i++){
           byte c = EEPROM.read(i); // Read the byte at the index i
           Serial.printf("%c|", c);
        }
    
      Serial.println();
      EEPROM.end(); // Close the EEPROM 
    }
    else if(c.indexOf("c\r\n") == 0){
      unsigned long start_count_ = millis(); //https://www.arduino.cc/reference/en/language/functions/time/millis/
      Serial.println("Going to clear EEPROM, Are you sure? \ny/n (write y to continue, n to abort)");
      do{
        Serial.print('.');
        delay(100);      
    // While no command was written, and we haven't been waiting for more than PROMPT_TIMEOUT (10 seconds)
      }while(!Serial.available() && millis() - start_count_ <= PROMPT_TIMEOUT);
      Serial.println();
      if(Serial.available()>0){
        String t = Serial.readString();
        if(t.indexOf("y\r\n") == 0){
          Serial.println("Clearing EEPROM");
          EEPROM.begin(EEPROM_SIZE);
          // Erasing EEPROM data
          for (int i = 0; i < EEPROM_SIZE; i++){  
             EEPROM.write(i, 0); // Clear EEPROM columns one by one by writing 0 to each one of them
          }
          Serial.println("Done erasing");
          EEPROM.commit(); // After making a change to the EEPROM, we have to commit it in order to make it permanent
          EEPROM.end();
        }
        else if(t.indexOf("n\r\n") == 0){
          return;
        }
      }
      else Serial.println("Aborted erasing, command timeout!");
    }
    // If we receive anything but r/c, it's an unknown command
    else Serial.println("Unknown command! r --> read, c --> clear");
  }
  
}
