#include <TinyGPS++.h>
#include <LoRa.h>
#include <SPI.h>

//LoRa
#define SCK     5    
#define MISO    19  
#define MOSI    27   
#define SS      18   
#define RST     14   
#define DI0     26  
#define FREQUENCIA  915E6 //  915MHz de frequencia
#define GANHO     20  // ganho dBm que permite maior alcance

TinyGPSPlus gps; //objeto GPS
HardwareSerial SerialGPS(1);          

//DADOS GPS
typedef struct __attribute__((__packed__)){   //esse atributo fala pro compilador utiizar o tamanho da soma dos dados dentro da struct
  double latitude;
  double longitude;
  double velocidade;
}Dado;

bool setupLoRa();   //Parametros pra conexao LoRa
void enviaLoRa();
static void delayGPS(unsigned long ms);
Dado pegaDados();

void setup(){
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, 12, 15);  //Instancia as portas seriais
  while (setupLoRa () == false);  // Tenta, até obter sucesso, comunicacao com o chip LoRa
  delay(1000);
}

void loop() {
  enviaLoRa();
  delayGPS(1000);
}

bool setupLoRa(void)
{  
  bool status = false;
  Serial.println("[LoRa Transmissor] Tentando iniciar comunicacao com o radio LoRa...");
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
    Serial.println("[LoRa Transmissor] Comunicacao com o radio LoRa falhou. Nova tentativa em 1 segundo...");
    delay(1000);
    status = false;
  }
  else
  {
    LoRa.setTxPower(GANHO);
    Serial.println("[LoRa Transmissor] Comunicacao com o radio LoRa ok");
    status = true;
  }
  return status;
}

void enviaLoRa()
{
  Dado dadoLoRa;
  dadoLoRa = pegaDados();

  if((dadoLoRa.latitude != 0.0) && (dadoLoRa.longitude != 0.0)){
    LoRa.beginPacket();   //inicia transmissao
    LoRa.write((unsigned char *)&dadoLoRa, sizeof(Dado)); //envia os dados
    LoRa.endPacket(); //termina transmissao 
  }
}

static void delayGPS(unsigned long ms)       //delay melhor elaborado         
{
  unsigned long start = millis();
  do
  {
    while (SerialGPS.available())
      gps.encode(SerialGPS.read());
  } while (millis() - start < ms);


   if (millis() > 5000 && gps.charsProcessed() < 10)  //caso de ruim
    Serial.println(F("Erro: nenhum dado GPS recebido"));
}

Dado pegaDados(){
  Dado dados;
  dados.latitude = gps.location.lat();
  dados.longitude = gps.location.lng();
  dados.velocidade = gps.speed.kmph();
  return dados;
}


