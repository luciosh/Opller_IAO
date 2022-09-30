float FazLeituraUmidade(void)
{
  int ValorADC;
  float UmidadePercentual;

    ValorADC = analogRead(pinoSensor);   //978 -> 3,3V
    Serial.print("[Leitura ADC] ");
    Serial.println(ValorADC);
        
    UmidadePercentual = map(ValorADC, analogSoloSeco, analogSoloMolhado, 0, 100);
    Serial.print("[Umidade Percentual] ");
    Serial.print(UmidadePercentual);
    Serial.println("%");

    return UmidadePercentual;
}

void setup_opller(){
  //Inicializa hardware
  pinMode(pin_X1, INPUT_PULLUP);
  pinMode(pin_X2, INPUT_PULLUP);
  pinMode(pin_X3, INPUT_PULLUP);
  pinMode(pin_X4, INPUT_PULLUP);
  pinMode(pin_X5, INPUT_PULLUP);
  pinMode(pin_X6, INPUT_PULLUP);
  pinMode(pin_X7, INPUT_PULLUP);
  pinMode(pin_X8, INPUT_PULLUP);
  pinMode(pin_Y1, OUTPUT);
  pinMode(pin_Y2, OUTPUT);
  pinMode(pin_Y3, OUTPUT);
  pinMode(pin_Y4, OUTPUT);
  pinMode(pin_Y5, OUTPUT);
  pinMode(pin_Y6, OUTPUT);
  pinMode(pin_Y7, OUTPUT);
  pinMode(pin_Y8, OUTPUT);  
  pinMode(ENTX_pin, OUTPUT);

  digitalWrite(pin_Y1, LOW);
  digitalWrite(pin_Y2, LOW); 
  digitalWrite(pin_Y3, LOW); 
  digitalWrite(pin_Y4, LOW); 
  digitalWrite(pin_Y5, LOW);
  digitalWrite(pin_Y6, LOW);
  digitalWrite(pin_Y7, LOW);
  digitalWrite(pin_Y8, LOW);

  // Configuração da saída analógica
  //(Canal, Frequência, Resolução)
  ledcSetup(0, 10000, 10);
  //(Pino, Canal)
  ledcAttachPin(23, 0);
}

void loop_opller(){
  char FieldUmidade[11];
	UmidadePercentualLida = FazLeituraUmidade();
	UmidadePercentualTruncada = (int)UmidadePercentualLida; //trunca umidade como número inteiro
  Serial.print("Umidade do solo percentual: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(UmidadePercentualLida); //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO
  Serial.println("%"); //IMPRIME O CARACTERE NO MONITOR SERIAL
  Serial.print("Umidade do solo inteira: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(UmidadePercentualTruncada); //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO 
  Serial.print(pinoSensor); //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO 

  Serial.println(UmidadePercentualLida);
  if(UmidadePercentualLida < 60){
		ledcWrite(0, 650);
    Serial.println("Ativando motor");
	}else{
		ledcWrite(0, 0);
    Serial.println("Desativando motor");

	}

}