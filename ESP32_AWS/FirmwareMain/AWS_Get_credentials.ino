
void get_credentials(){

	EEPROM.begin(1024);

	int newStr1AddrOffset = get_EEPROM(100, &DEVICE_ID);
	int newStr2AddrOffset = get_EEPROM(newStr1AddrOffset, &SSID1);
	int newStr3AddrOffset = get_EEPROM(newStr2AddrOffset, &PWD1);
	int newStr4AddrOffset = get_EEPROM(newStr3AddrOffset, &SSID2);
	int newStr5AddrOffset = get_EEPROM(newStr4AddrOffset, &PWD2);
	int newStr6AddrOffset = get_EEPROM(newStr5AddrOffset, &ADM_COD);
	int newStr7AddrOffset = get_EEPROM(newStr6AddrOffset, &HOSTNAME_OTA);
  int newStr8AddrOffset = get_EEPROM(newStr7AddrOffset, &PREFIX_TOPIC);
  // int newStr9AddrOffset = get_EEPROM(newStr8AddrOffset, &VERSAO);

	THINGNAME = "pbpm" + String(DEVICE_ID);

	#ifdef DEBUG
		Serial.println("\n\nStrings armazenadas: ");
		Serial.println(DEVICE_ID);
		Serial.println(SSID1);
		Serial.println(PWD1);
		Serial.println(SSID2);
		Serial.println(PWD2);
		Serial.println(ADM_COD);
		Serial.println(HOSTNAME_OTA);
		Serial.println(PREFIX_TOPIC);
		// Serial.println(VERSAO);
		Serial.println("\nFIM --- Strings armazenadas: ");
	#endif
	
	EEPROM.end();
	TOPIC_PUB_CAD = PREFIX_TOPIC + "/" + DEVICE_ID;
	TOPIC_SUB_CAD = PREFIX_TOPIC + "/return/" + DEVICE_ID;
}

int get_EEPROM(int addrOffset, String *strToRead)
{
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

int config_topics(){
	TOPIC_PUB_CAD = PREFIX_TOPIC + "/" + DEVICE_ID;
	TOPIC_SUB_CAD = PREFIX_TOPIC + "/return/" + DEVICE_ID;
	
}
