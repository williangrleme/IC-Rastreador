#include <WiFi.h>
#include <PubSubClient.h>
#include <LoRa.h>
#include <SPI.h>
#include <cmath>

//MQTT
#define  MQTT_ID "Esp32" //Identificador do device dentro do Broker MQTT
#define  MQTT_TOPICO_LOC "home/localizacao" //Tópico MQTT
#define  MQTT_TOPICO_ALCANCE "Alerta_distancia" //Tópico MQTT
#define  MQTT_TOPICO_VELOCIDADE "Alerta_velocidade" //Tópico MQTT
#define  MQTT_TOPICO_VELOCIDADE_ATUAL "Velocidade" //Tópico MQTT
#define  MQTT_TOPICO_DISTANCIA "Distancia" //Tópico MQTT
#define  MQTT_BROKER "" //URL do Broker
#define  MQTT_SENHA ""  //Token 
#define  MQTT_USUARIO "Master"    //Usuario
#define  MQTT_PORTA 1883       //Porta do Broker

//LoRa
#define SCK     5    
#define MISO    19  
#define MOSI    27   
#define SS      18   
#define RST     14   
#define DI0     26  
#define FREQUENCIA  915E6 //  915MHz de frequencia
#define GANHO     20  //Ganho dBm que permite maior alcance
#define latCASA  //define latitude do local fixo
#define longCASA  //define longitude do local fixo
#define distanciaMax //distancia maxima permitida
#define velocidadeMax //velocidade maxima permitida

//WIFI
#define ssid ""   //rede wifi
#define password "" //senha rede wifi

//OBJETOS
WiFiClient wificlient; //objeto da classe wifi que o MQTT_BROKER usa pra se conectar
PubSubClient MQTT(MQTT_BROKER,MQTT_PORTA,wificlient); //objeto mqtt

//DADOS GPS
typedef struct __attribute__((__packed__)){   //esse atributo fala pro compilador utiizar o tamanho da soma dos dados dentro da struct
  double latitude;
  double longitude;
  double velocidade;
}Dado;

void setupWifi();   //Parametros pra conexao WiFi
bool setupLoRa();   //Parametros pra conexao LoRa
void conectaWifi(); //Efetua a conexao WiFi
void conectaMQTT(); //Efetua a conexao com o servidor MQTT
Dado recebePacote(); //Recebe o pacote LoRa e o retorna
String criaJsonLOC(Dado loc);  //Converte a informação no formato JSON
String criaJsonALCANCE(int x);  //Converte a informação no formato JSON
String criaJsonVELOCIDADE(int y); //Converte a informação no formato JSON
void publicaLOC(String payloadLOC); //publica localizacao em tempo real no server MQTT
void manterConexoes(); //Verifica conexoes, se perdidas, refaz elas
double paraRadiando(double degrees); //conversao para radiando
double calcularDistancia(double lat1, double lon1, double lat2, double lon2); //funcao de calcula de distancia entre localizacao atual e pré-estabelecida
void cercaVirtual(Dado dadoLora); //Funcoes da cerca virtual

void setup(){
  Serial.begin(115200);
  setupWifi();
  conectaWifi();   
  conectaMQTT();
  while (setupLoRa () == false);  // Tenta, até obter sucesso, comunicacao com o chip LoRa
  delay(1000);
}

void loop() {
  //manterConexoes();
  MQTT.loop(); //fica em constante comunicacao com o MQTT_BROKER
  String payloadLOC;
  Dado dadoLoRa;
  char recebido;
  int tamanhoPacote = 0;
  char * informacaoRecebida = NULL;
  tamanhoPacote = LoRa.parsePacket();     //recebe o pacote
     
  if (tamanhoPacote == sizeof(Dado))  //se o pacote recebido tem o tamanho do pacote esperado
  {
    Serial.println("[LoRa Receptor] Há dados a serem lidos");
    informacaoRecebida = (char *)&dadoLoRa;   //ponteiro pra variavel que vai receber os dados
    while (LoRa.available())  // recebe o pacote que esta quebrado em array de bytes, conforme o protocolo LoRaWAN
      {
        recebido = (char)LoRa.read();
        *informacaoRecebida = recebido;
        informacaoRecebida++;
      }
      payloadLOC = criaJsonLOC(dadoLoRa);
      publicaLOC(payloadLOC);
      cercaVirtual(dadoLoRa);
  }                     
}

void setupWifi(){
  WiFi.mode(WIFI_STA);  //Device operando como estacao
  WiFi.disconnect();    //Se desconectando de qualquer rede
  WiFi.setAutoConnect(true);
  delay(100);
}

bool setupLoRa(void)
{  
  bool status = false;
  Serial.println("[LoRa Receptor] Tentando iniciar comunicacao com o radio LoRa...");
  SPI.begin(SCK, MISO, MOSI, SS); //Inicializacao da comunicaco serial
  LoRa.setPins(SS, RST, DI0); //Inicializacao dos  pinos LoRa
  //LoRa.setSpreadingFactor(12); //define o fator de espalhamento
  //LoRa.setSignalBandwidth(250E3); //define a largura de banda
  //LoRa.setCodingRate4(5); //define o Codding Rate
  //LoRa.setPreambleLength(6); //define o comprimento do preâmbulo
  //LoRa.setSyncWord(0x15); //define a palavra de sincronização
  //LoRa.disableCrc(); //desabilita o CRC
  //LoRa.crc();
  
  if (!LoRa.begin(FREQUENCIA))	//Comecando conexao LoRa
  {
    Serial.println("[LoRa Receptor] Comunicacao com o radio LoRa falhou. Nova tentativa em 1 segundo...");
    delay(1000);
    status = false;
  }
  else
  {
    LoRa.setTxPower(GANHO);
    Serial.println("[LoRa Receptor] Comunicacao com o radio LoRa ok");
    status = true;
  }
  return status;
}

void conectaWifi(){   
  if(WiFi.status() == WL_CONNECTED){
    return;
  }
  WiFi.begin(ssid, password); // Inicia a conexao WiFi
  Serial.printf("Conectando na rede Wifi");
  while ( WiFi.status() != WL_CONNECTED ) {
    delay (500);
    Serial.print ( "." );
  }
  Serial.printf( "\nConectado em: %s\n",ssid);
}

void conectaMQTT(){

  while(!MQTT.connected()){ //Enquanto nao se conectar ao servidor
    Serial.printf("Conectando ao Broker... ");
    Serial.println(MQTT_BROKER);
    if(MQTT.connect(MQTT_ID, MQTT_USUARIO, MQTT_SENHA)){    //Conexao do device no servidor
      Serial.println("Conectado ao Broker com sucesso");
    }
    else{
      Serial.println("Nao foi possivel conectar com o servidor");
      Serial.printf("Erro = ");
      Serial.println(MQTT.state());
    }
  }
}

Dado recebePacote(){
  char recebido;
  int tamanhoPacote = 0;
  Dado dadoLoRa;
  char * informacaoRecebida = NULL;
  tamanhoPacote = LoRa.parsePacket();     //recebe o pacote
     
  if (tamanhoPacote == sizeof(Dado))  //se o pacote recebido tem o tamanho do pacote esperado
  {
    Serial.println("[LoRa Receptor] Há dados a serem lidos");
    informacaoRecebida = (char *)&dadoLoRa;   //ponteiro pra variavel que vai receber os dados
    while (LoRa.available())  // recebe o pacote que esta quebrado em array de bytes, conforme o protocolo LoRaWAN
      {
        recebido = (char)LoRa.read();
        *informacaoRecebida = recebido;
        informacaoRecebida++;
        }
  }
return dadoLoRa;
}

String criaJsonLOC(Dado loc){
  String json;

  json = "[";
  json += "{";
  json += "\"variable\":\"localizacao\",\"value\":\"Rastreador\",\"location\":"; 
  json += "{";
  json += "\"lat\":";
  json += String(loc.latitude,15);
  json += ",";
  json +=  "\"lng\":";
  json += String(loc.longitude,14);
  json += "}";
  json += "}";
  json += "]";
  return json;
}

String criaJsonALCANCE(int x){
  String json;  
  json = "[";
  json += "{";
  json += "\"variable\":\"alcance\",\"value\":"; 
  json += String(x);
  json += "}";
  json += "]";

  return json;
}

String criaJsonVELOCIDADE(int y){
  String json;  
  json = "[";
  json += "{";
  json += "\"variable\":\"alcance\",\"value\":"; 
  json += String(y);
  json += "}";
  json += "]";

  return json;
}

void publicaLOC(String payloadLOC){
  MQTT.publish(MQTT_TOPICO_LOC,payloadLOC.c_str());
  delay(2000);
}

void manterConexoes(){

  if(!MQTT.connected()){
    conectaMQTT();
  }

  if(WiFi.status() != WL_CONNECTED){
    WiFi.reconnect();
  }
}

double paraRadiando(double degrees) {
    return degrees * M_PI / 180.0;
}

double calcularDistancia(double lat1, double lon1, double lat2, double lon2) {
    constexpr double radiandoKM = 6371.0; // Constante para conversao de radiando pra kM
    
    double dLat = paraRadiando(lat2 - lat1);
    double dLon = paraRadiando(lon2 - lon1);

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(paraRadiando(lat1)) * std::cos(paraRadiando(lat2)) *
               std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    double distancia = radiandoKM * c;
    return distancia;
}

void cercaVirtual(Dado dadoLora){

  //verificando distancia
  double dist;
  int x = 0;
  int y = 0;
  String payloadALCANCE, payloadVELOCIDADE;

  dist = calcularDistancia(dadoLora.latitude,dadoLora.longitude,latCASA,longCASA);
  if (dist > distanciaMax){ 
    x = 1;
  }
  else{
    x = 0;
  }

  payloadALCANCE = criaJsonALCANCE(x);
  MQTT.publish(MQTT_TOPICO_ALCANCE,payloadALCANCE.c_str()); //PUBLICA NO CAMPO ALERTA


  //verificando velocidade
  if(dadoLora.velocidade > velocidadeMax){
    y = 1;
  }
  else{
    y = 0;
  }

  payloadVELOCIDADE = criaJsonVELOCIDADE(y);
  MQTT.publish(MQTT_TOPICO_VELOCIDADE,payloadVELOCIDADE.c_str());
}