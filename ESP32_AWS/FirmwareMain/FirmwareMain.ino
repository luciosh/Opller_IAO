/* IAO - Irrigacao Automatica com Opller
  AUTOR: ABR - Sergio Lucio
  DATA: 03/01/2022
  VERSAO: 1.1 - Padronizacao do codigo

*/
#include "Init.h"


// VOID SETUP -----------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("INICIANDO...");
  Serial.println("OBTENDO CREDENCIAIS...");
  get_credentials();
  Serial.println("INICIALIZANDO AWS E TOPICOS...");
  // config_topics();
  connectAWS();
  Serial.println("Fim setup...");
  setup_opller();
  t.every(10000, envia_dados, 0);
}

// VOID LOOP ------------------------------------------------------------------
void loop() {
  loop_opller();
  if (!client.connected()) {
    Serial.println("NAO CONECTADO.......................");
    reconecta_wifi();
    connectAWS();
    
  }else{
    client.loop();
  }
  t.update();
  delay(2000);
}

void envia_dados(void* context){
  if (!client.connected()) {
    Serial.println("NAO CONECTADO.......................");
    reconecta_wifi();
    connectAWS();
    
  }else{
    client.loop();
    Format_pub();
  }
}
