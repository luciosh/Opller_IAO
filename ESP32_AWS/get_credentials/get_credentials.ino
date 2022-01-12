#include "EEPROM.h"

void setup(){
    Serial.begin(9600);
    EEPROM.begin(1024);
    
	// Reading
    String newStr1;
    String newStr2;
    String newStr3;
    String newStr4;
    String newStr5;
    String newStr6;
    String newStr7;

    int newStr1AddrOffset = readStringFromEEPROM(0, &newStr1);
    int newStr2AddrOffset = readStringFromEEPROM(newStr1AddrOffset, &newStr2);
    int newStr3AddrOffset = readStringFromEEPROM(newStr2AddrOffset, &newStr3);
    int newStr4AddrOffset = readStringFromEEPROM(newStr3AddrOffset, &newStr4);
    int newStr5AddrOffset = readStringFromEEPROM(newStr4AddrOffset, &newStr5);
    int newStr6AddrOffset = readStringFromEEPROM(newStr5AddrOffset, &newStr6);
    readStringFromEEPROM(newStr6AddrOffset, &newStr7);

    Serial.println("Strings armazenadas: ");
    Serial.println(newStr1);
    Serial.println(newStr2);
    Serial.println(newStr3);
    Serial.println(newStr4);
    Serial.println(newStr5);
    Serial.println(newStr6);
    Serial.println(newStr7);

}

void loop(){
    Serial.println("...");
    delay(1000);
    
}

int readStringFromEEPROM(int addrOffset, String *strToRead)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; 
  *strToRead = String(data);
  return addrOffset + 1 + newStrLen;
}

