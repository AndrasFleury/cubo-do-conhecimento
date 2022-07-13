/********************************************
 * Cubo do Conhecimento    *
 * Versão Gilberto Gil v.3 *
 ******************************************** 
 * Criado em 24/04/2022
 * Autor: András Fleury
 * andras@netstern.com.br
 * Monitoria dos professores (em ordem alfabética)
 * Glauco Paiva
 * Nayara Prando
 * William Oliveira
 * 
 *********************************************
 * Agradecimentos:
 * A minha esposa Esterlita, que sempre me apoia nas minhas invenções.
 * Aos meus filhos Sandor e Ellen que matam minhas dúvidas, fazem as
 * soldas, além de muitas outras coisas.
 * Agradecimento especial
 * A Fábrica de Cultura 4.0 de São Barnardo do Campo
 * por toda estrutura incrivél, aos professores maravilhos,
 * a toda diretoria e cordenadores.
 *********************************************
 *   Fábrica de Cultura 4.0
 * São Bernardo do Campo - SP
 ******************************************** 
 */
 //Inclui as bibliotecas
 #include "SPI.h"
 #include "SoftwareSerial.h"
 #include "MFRC522.h"
 #include "LiquidCrystal_I2C.h"
 #include "DFRobotDFPlayerMini.h"

  /************** \/ RFID Configuração \/ **************/
  //Definição dos pinos de conexão do projeto 
  #define PINO_SS 10
  #define PINO_RST 9
  //Cria o item para configurar o módulo RC522 RFID
  MFRC522 mfrc522(PINO_SS, PINO_RST);
  /************** /\ RFID Configuração /\ **************/
  /************** \/ LCD configuração \/ **************/
  //Inicializa o display LCD no endereco 0x27
  LiquidCrystal_I2C lcd(0x27,16,2);
  /************** /\ LCD configuração /\ **************/
  /*************** \/ Mini Player MP3 \/ ***************/
  //Inicia a serial por software nos pinos 10 e 11
  SoftwareSerial mySoftwareSerial(6, 7); // RX, TX
  
  // Chama o objeto responsável pela comunicação com o módulo MP3
  DFRobotDFPlayerMini myDFPlayer;
  /*************** /\ Mini Player MP3 /\ ***************/
  /*************** \/ Criando a variável \/ ***************/
  //Cria a variável responsável em armazenar qual lado está sendo apresentado
    String lado = "vazio";
  /*************** /\ Criando a variável /\ ***************/
  /************ \/ Declarando as variáveis \/ ************/
      String linha01;
      String linha02;
      int trilha;

  /************ /\ Declarando as variáveis /\ ************/

void printDetail(uint8_t type, int value);

void setup()
{
  // inicia LCD
   lcd.init();
  // Inicializa a serial
  Serial.begin(9600);
    mySoftwareSerial.begin(9600);
  //Inicializa a serial do Arduino
  Serial.begin(115200);
  //Verifica se o modulo esta respondendo e se o
  //cartao SD foi encontrado
  /************** \/ Teste do Cartao de memoria e módulo MP3 \/ **************/
  Serial.println();
  Serial.println("DFRobot DFPlayer Mini");
  Serial.println("Inicializando modulo DFPlayer... (3~5 segundos)");
  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println("Nao inicializado:");
    Serial.println("1.Cheque as conexoes do DFPlayer Mini");
    Serial.println("2.Insira um cartao SD");
    Serial.println(lado);
    while (true);
  }
  Serial.println();
  Serial.println("Modulo DFPlayer Mini inicializado!");
  Serial.println(lado);
  /************** /\ Teste do Cartao de memoria e módulo MP3 /\ **************/
  /************** \/ Definições do MiniPlayer iniciais \/ **************/
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.volume(10); //Volume 10
  myDFPlayer.EQ(2); //Equalizacao normal
  /************** /\ Definições do MiniPlayer iniciais /\ **************/
  /************** \/ Inicializa a comunicação SPI Inicializa o módulo MFRC522 \/ **************/
  // Inicializa a comunicação SPI
  SPI.begin();
  // Inicializa o módulo MFRC522
  mfrc522.PCD_Init();
  /************** /\ Inicializa a comunicação SPI Inicializa o módulo MFRC522 /\ **************/

  // Printa mensagem na serial
  Serial.println("Cubo de Gil. Escolha um lado do cubo e coloque na base.");
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("  Cubo do Gil  ");
  lcd.setCursor(0,1);
  lcd.print("Coloque na base");
  delay(1000);  
}
void loop() {

  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Imprime a mensagem de detalhes do DFPlayer para lidar com diferentes erros e estados.
  }

  // Aguarda a aproximação do token
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  // Seleciona qual token vai ser utilizado 
  if (!mfrc522.PICC_ReadCardSerial()) return;

  //Cria uma variável vazia, do tipo string
  String conteudo= "";

  //Cria uma variável do tipo byte
  byte letra;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     if(mfrc522.uid.uidByte[i] < 0x10){
        Serial.print(" 0");
     }
     else{
        Serial.print(" ");
     }
     // Printa a mensagem convertida em hexadecimal
     // Serial.print(mfrc522.uid.uidByte[i], HEX);


     if(mfrc522.uid.uidByte[i] < 0x10){
        conteudo.concat(String(" 0"));
     }
     else{
        conteudo.concat(String(" "));
     }
     // Concatena a string convertida em hexadecimal
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
    
    Serial.println();
    //Serial.print(" Mensagem : ");
    
    //Coloca todas as letras da string em maiúscula
    conteudo.toUpperCase();

    // Verifica se o conteúdo do cartão coincide
      String lendo= "";
      lendo=conteudo.substring(1);
      Serial.println("aqui vamos ver lado");
      Serial.println(lado);
      Serial.println("aqui vamos ver lendo");
      Serial.println(lendo);
  // \/ ################## Dados ##################### \/ //
          if(lendo=="76 1C 30 25"){
       // Mensagem inicio ################ \/ //
            linha01 = "Povo Petroleiro";
            linha02 = "Inicio - 1962";
            trilha = 1;
            Serial.println(linha01);
       // Mensagem inicio ################ /\ //
          }else if(lendo=="57 D0 76 62"){
       // Mensagem tropicalismo ################ \/ //
            linha01 = "Tropicalia";
            linha02 = "1966";
            trilha = 2;
            Serial.println(linha01);
       // Mensagem tropicalismo ################ /\ //
          }
          else if(lendo=="66 8A 44 25"){
       // Mensagem AI5 ################ \/ //
            linha01 = "O Golpe e AI5";
            linha02 = "13/12/1968";
            trilha = 3;
            Serial.println(linha01);
       // Mensagem AI5 ################ /\ //
          }
          else if(lendo=="66 E8 C3 25"){
       // Mensagem Exílio ################ \/ //
            linha01 = "Exilio";
            linha02 = "1969";
            trilha = 4;
            Serial.println(linha01);
       // Mensagem Exílio ################ /\ //
          }
          else if(lendo=="76 7E 00 25"){
       // Mensagem Retorno ################ \/ //
            linha01 = "Retorno ao Brasil";
            linha02 = "1972";
            trilha = 5;
            Serial.println(linha01);
       // Mensagem Retorno ################ /\ //
          }
          else if(lendo=="66 1E A2 25"){
       // Mensagem Prêmio ################ \/ //
            linha01 = "Premio Grammy";
            linha02 = "1999";
            trilha = 6;
            Serial.println(linha01);
       // Mensagem Prêmio ################ /\ //
          }
  // /\ ################## Dados ##################### /\ //
     
      if(lado==lendo){
        // \/ ################## Lado iguail, apresenta apenas mensagem ##################### \/ //
        Serial.println("Iguais");       
              Serial.print("acessou o lado ---->");
              Serial.print(lendo);
              Serial.println("<--");
              Serial.print("Pegou a variavel-->");
              Serial.print(linha01);
              Serial.println("<--");    
            /* lcd.clear();
              lcd.setBacklight(HIGH);
              lcd.setCursor(0,0); 
              lcd.print(linha01);
              lcd.setCursor(0,1);
              lcd.print(linha02);
              Serial.println(myDFPlayer.readState());*/
      }else{
        Serial.println("diferentes");
        lado=conteudo.substring(1);
              Serial.print("acessou o lado ---->");
              Serial.print(lendo);
              Serial.println("<--");
              Serial.print("Pegou a variavel-->");
              Serial.print(linha01);
              Serial.println("<--");
              lcd.clear();
              lcd.setBacklight(HIGH);
              lcd.setCursor(0,0);        
              lcd.print(linha01);
              lcd.setCursor(0,1);
              lcd.print(linha02);
              myDFPlayer.play(trilha);
              }  
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Tempo esgotado!"));
      break;
    case WrongStack:
      Serial.println(F("Trilha errada"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Cartão inserido"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Cartão inserido"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Cartão On-line!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Numero:"));
      Serial.print(value);
      Serial.println(F(" Trilha finalizada"));
          lcd.clear();
          lcd.setBacklight(HIGH);
          lcd.setCursor(0,0);
          lcd.print("    Escolha    ");
          lcd.setCursor(0,1);
          lcd.print("  outro lado.");
            delay(6000);
            lcd.clear();
            lcd.setBacklight(HIGH);
            lcd.setCursor(0,0);
            lcd.print("  Cubo do Gil  ");
            lcd.setCursor(0,1);
            lcd.print("Coloque na base");
      break;
      
    default:
      break;
  }
  }
