// Funcoes referentes a interacao com AWS

void messageReceived(char *topic, byte *payload, unsigned int length){
  #ifdef DEBUG
    Serial.print("Received [");
    Serial.print(topic);
    Serial.print("]: ");
  #endif  

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received [");
  Serial.print(topic);
  Serial.println("]: "); 
  return_message = "";
   for (int i = 0; i < length; i++)
  {
    return_message += (char)payload[i];
  }
  retorno_mqtt();

}

void connectAWS(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID1.c_str(), PWD1.c_str());

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.setCallback(callback);


  Serial.print("Connecting to AWS IOT");
  
  while (!client.connect("iao1")) {
    Serial.print(".");
    delay(1000);
  }
  
  if(!client.connected()){
    Serial.println("\nAWS IoT Timeout!");
    return;
  }else{
    Serial.println("\nAWS IoT Connected!");
  }
  
  // Subscribe to a topic
  client.subscribe(TOPIC_SUB_CAD.c_str());
  
}

void connect_wifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID1.c_str(), PWD1.c_str());

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }  
}

void publishMessage(String AWS_IOT_PUBLISH_TOPIC,  String keys,  String values){

  yield();
  Serial.println("entrando em publish");
	StaticJsonDocument<200> doc;

  // ---- Explode das strings keys e values e atribuicao a objeto json doc -----
  int pos_key = 0;
  int pos_val = 0;
  int pos_ini = 0;
  String key_sub;
  String val_sub;
		while(keys.length() != 0)
	{
      pos_key = keys.indexOf(',');
      pos_val = values.indexOf(',');
      key_sub = keys.substring(pos_ini, pos_key);
      val_sub = values.substring(pos_ini, pos_val);
			doc[key_sub] = val_sub;
      keys.remove(0, key_sub.length()+1);
      values.remove(0, val_sub.length()+1);
      Serial.print("Estados das strings nessa rodada:");
      
      Serial.println(keys);
      Serial.println(values);
		
	}
  // ---------------------------------------
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
	#ifdef DEBUG
		Serial.println(String(jsonBuffer));
	#endif
  if (!client.connected()) {
    Serial.println("NAO CONECTADO.......................");
    reconecta_wifi();
    connectAWS();
  }
  if(!(client.publish(AWS_IOT_PUBLISH_TOPIC.c_str(), jsonBuffer))){
     //Publicacao falhou
  }
  else{
    //OK
   }
}

// FUNCOES RELACIONADAS A CONEXAO ---------------------------------------------

void reconecta_wifi(){
    if(WiFi.status() != WL_CONNECTED)
    {
      #ifdef DEBUG
        Serial.println("Wifi nao conectado!");
        Serial.println("Conectando wifi...");
      #endif  
      connect_wifi();
    }
}

void retorno_mqtt(){
  
  Serial.println(return_message);
  // Serial.println(return_message.indexOf("sucesso"));
  if(return_message.indexOf("liga") != -1){ // Entra caso sucesso
    ledcWrite(0, 650);
    Serial.println("Ativando motor");
  }
  if(return_message.indexOf("desliga") != -1){ // Entra caso sucesso
    ledcWrite(0, 0);
    Serial.println("Desativando motor");
  } 
}