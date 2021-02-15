# EEPROM_Shell
A light sketch to easily interact with the EEPROM in your uController.

--- 

## Description

Data stored to the EEPROM of any uController is permanent and could be retreived even after losing power, that what makes interacting with the EEPROM very powerful, but such power doesn't come with no consequences! Unfortunately, reading from the EEPROM isn't as easy as writing to it (from physiscs perspective), that's why each EEPROM has a limited number of Read/Write cycles that could be executed. This means that you shouldn't store variables that are frequently updates in EEPROM (like sensors' data in general), instead store config data, data that would require a read every stratup and rare updates (Wi-Fi data, number phones, passwords, ...).

This sketch provides a way to play with EEPROM and understand how it works.

## How to use?

- 1st, you have to figure out the size of your uController's EEPROM since it varies from model to model. The go to the sketch and update the *eeprom_size* variable.

- Upload the code, open your Serial monitor, and set its baud rate to *115200* (or change the one in the code to match your needs, since some Arduino borads might struggle with *115200 bips*).

- To interact with the EEPROM:
> Write 'c' to the serial monitor to CLEAR the EEPROM. You'll be asked for confirmation, write 'y' to proceed, 'n' to abort (The code will wait for 10 seconds before aborting automatically).

> Write 'r' to the serial monitor to READ the EEPROM content.

Have fun!
