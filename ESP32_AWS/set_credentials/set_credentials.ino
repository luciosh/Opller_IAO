#include "libraries.h"
String str;
String DEVICE_ID = "1";
String VERSAO = "1.1";
String SSID1 = "nome";
String PWD1 = "senha";
String SSID2 = "network2";
String PWD2 = "abcabcabc";
String ADM_COD = "998850";
String HOSTNAME_OTA = "device-iao-" + String(DEVICE_ID);
String PREFIX_TOPIC = "iao";
String str1, str2, str3, str4, str5, str6, str7, str8, str9;
int numID;
int eepromOffset = 100;

void setup(){
    Serial.begin(9600);
    EEPROM.begin(1024);

    int fimstr1 = set_EEPROM(eepromOffset, DEVICE_ID);
    int fimstr2 = set_EEPROM(fimstr1, SSID1);
    int fimstr3 = set_EEPROM(fimstr2, PWD1);
    int fimstr4 = set_EEPROM(fimstr3, SSID2);
    int fimstr5 = set_EEPROM(fimstr4, PWD2);
    int fimstr6 = set_EEPROM(fimstr5, ADM_COD);
    int fimstr7 = set_EEPROM(fimstr6, HOSTNAME_OTA);
    int fimstr8 = set_EEPROM(fimstr7, PREFIX_TOPIC);
    int fimstr9 = set_EEPROM(fimstr8, VERSAO);
    EEPROM.commit();

    // str1 = "sizeof DEVICE_ID: " + String(sizeof(DEVICE_ID));
    // str2 = "sizeof SSID1: " + String(sizeof(SSID1));
    // str3 = "sizeof PWD1: " + String(sizeof(PWD1));
    // str4 = "sizeof SSID2: " + String(sizeof(SSID2));
    // str5 = "sizeof PWD2: " + String(sizeof(PWD2));
    // str6 = "sizeof ADM_COD: " + String(sizeof(ADM_COD));
    // str7 = "sizeof HOSTNAME_OTA: " + String(sizeof(HOSTNAME_OTA));

}

void loop(){

		int newStr1AddrOffset = get_EEPROM(eepromOffset, &str1);
		int newStr2AddrOffset = get_EEPROM(newStr1AddrOffset, &str2);
		int newStr3AddrOffset = get_EEPROM(newStr2AddrOffset, &str3);
		int newStr4AddrOffset = get_EEPROM(newStr3AddrOffset, &str4);
		int newStr5AddrOffset = get_EEPROM(newStr4AddrOffset, &str5);
		int newStr6AddrOffset = get_EEPROM(newStr5AddrOffset, &str6);
		int newStr7AddrOffset = get_EEPROM(newStr6AddrOffset, &str7);
    int newStr8AddrOffset = get_EEPROM(newStr7AddrOffset, &str8);
    int newStr9AddrOffset = get_EEPROM(newStr8AddrOffset, &str9);

    Serial.println("Strings armazenadas: ");
    Serial.println(str1);
    Serial.println(str2);
    Serial.println(str3);
    Serial.println(str4);
    Serial.println(str5);
    Serial.println(str6);
    Serial.println(str7);
    Serial.println(str8);
    Serial.println(str9);

    delay(5000);
}

int set_EEPROM(int addrOffset, const String &strToWrite) {
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
  return addrOffset + 1 + len;
  EEPROM.commit();

}

int get_EEPROM(int addrOffset, String *strToRead){
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; // !!! NOTE !!! Remove the space between the slash "/" and "0" (I've added a space because otherwise there is a display bug)
  *strToRead = String(data);
  return addrOffset + 1 + newStrLen;
}
