// A funcao Format_publish prepara as strings chaves e valores concatenando as variáveis para enviá-las a funcao publishMessage()
void Format_pub(){
    String chaves_pub = "device_id,umidade";
    // chaves_pub += ",outra_chave"; 
    Serial.println("Device ID:"); Serial.println(DEVICE_ID);
    String valores_pub = DEVICE_ID + "," + String(UmidadePercentualLida);
    // valores_pub += ",outra_chave_val";
    publishMessage(TOPIC_PUB_CAD, chaves_pub, valores_pub);
}

