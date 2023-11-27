<h1 align="center"> TECNOLOGIA ASSISTIVA E USO DE PLATAFORMA IOT PARA O MONITORAMENTO DE PACIENTES COM DOENÇAS COGNITIVAS </h1>

Este projeto propõe o desenvolvimento de um rastreador de pacientes com doenças cognitivas no ramo de tecnologia assistiva, incorporando o protocolo MQTT (Message Queuing Telemetry Transport), amplamente utilizado na Internet das Coisas (IoT), para comunicação eficaz. O sistema implementado utiliza a tecnologia LoRa para estabelecer comunicação entre dois dispositivos: um fixo na residência do paciente e outro móvel, acompanhando o paciente em deslocamento. A transmissão contínua de informações, utilizando o MQTT como um protocolo IoT, para uma plataforma web existente, permite a visualização em tempo real e a aplicação de lógica de cercas virtuais, que são alertas gerados pelo sistema quando certas condições de distância e velocidade são atingidas. 

Esse mecanismo aprimora a qualidade de vida dos pacientes e de seus familiares, proporcionando uma supervisão ativa e a capacidade de respostas rápidas em situações relevantes. Ao enfocar a eficiência do MQTT como um protocolo para IoT nesse sistema de tecnologia assistiva, busca-se contribuir de maneira significativa para a melhoria da assistência a pacientes com doenças cognitivas, fortalecendo a interação entre cuidadores e pacientes em um contexto de necessidade.


## Materiais e métodos
Para obter os resultados foi utilizado:

<p align="center">Placa Wemos® TTGO T-Beam ESP32 915Mhz WiFi Wireless Bluetooth Module ESP-32 GPS NEO-6M SMA LORA 32 18650 Battery Holder</p>
<p align="center">
  <img src="https://github.com/williangrleme/IC-Rastreador/blob/main/imgs/1.jpeg" alt="imagem">
</p>

<p align="center">Bateria 18650 Panasonic Ncr18650a 3000mah 3,6v</p>
<p align="center">
  <img src="https://github.com/williangrleme/IC-Rastreador/blob/main/imgs/2.jpeg" alt="imagem">
</p>

- __LoRa e LoRaWAN__: Tecnologia de rádio frequência para comunicação de longa distância com baixo consumo de energia e transmissão segura de dados.
- __ESP32__: Plataforma com microprocessador eficiente, WiFi, Bluetooth e suporte a bateria, GPS e LoRa 915MHz para rastreamento preciso e comunicação distante.
- __Protocolo MQTT__: Protocolo de comunicação eficiente entre dispositivos IoT, permitindo troca de mensagens e comandos via TCP/IP.
- __Plataforma PlatformIO__: Ambiente de desenvolvimento baseado no Visual Studio Code para codificação de sistemas embarcados em C/C++.
- __Plataforma TagoIO__: Plataforma em nuvem para monitoramento de ambientes por dispositivos IoT, oferecendo visualização de dados e criação de aplicações em diversos segmentos.


## Funcionalidades

- Rastreamento de localização em tempo real
- Rastreamento de velocidade em tempo real
- Cerca virtual de distância
- Cerca virtual de velocidade


## Resultados

Foram conduzidos testes de alcance de comunicação LoRa entre os dispositivos Slave (móvel) e Master (fixo), além do envio dos dados do Master para a plataforma de nuvem da TagoIO via MQTT. A maior distância alcançada foi cerca de 2 km, percorrendo uma rota não totalmente linear.

<p align="center">Rota urbana na cidade de Penápolis-SP visualizada no Widget de mapa da TagoIO</p>
<p align="center">
  <img src="https://github.com/williangrleme/IC-Rastreador/blob/main/imgs/3.png" alt="imagem">
</p>

Certificou-se uma expansão no alcance utilizando apenas recursos de software em um ambiente urbano densamente interferido. Para potencializar este resultado, sugere-se explorar melhorias de hardware, como uma antena mais avançada. Ademais, a análise da distância entre um ponto fixo pré-determinado e a posição atual demonstrou um máximo de cerca de 2 km.
Adicionalmente, foi conduzido um teste referente ao sistema de alerta de velocidade, no qual o limite máximo predefinido foi de 5 km/h. Dessa maneira, sempre que a velocidade registrada excedeu esse valor, o alerta correspondente foi ativado.

<p align="center">Widget da TagoIO para visualização de velocidade e alerta gerado</p>
<p align="center">
  <img src="https://github.com/williangrleme/IC-Rastreador/blob/main/imgs/4.png" alt="imagem">
</p>

Além disso, procedeu-se com um teste relativo ao alerta de raio de alcance, no qual a distância máxima permitida e predefinida foi estabelecida em 100 metros. Consequentemente, sempre que a distância registrada (expressa em quilômetros) ficou aquém desse limite, o alerta foi prontamente acionado.


<p align="center">Widget da TagoIO para visualização de distância e alerta gerado</p>
<p align="center">
  <img src="https://github.com/williangrleme/IC-Rastreador/blob/main/imgs/5.png" alt="imagem">
</p>

Em seguida, foi conduzido um teste para demonstrar a visualização completa no Painel de Controle, com o intuito de simular um cenário fiel ao contexto do projeto. Na ilustração abaixo, o dispositivo móvel permanecia parado, resultando em uma velocidade registrada de 0 km/h e a não ativação do alerta de velocidade. Entretanto, considerando que a distância máxima aceitável foi definida como 100 metros, o alerta de alcance máximo foi acionado. A representação também exibiu a distância entre a localização atual do dispositivo e o local fixo estabelecido.

<p align="center">Visualização do Dashboard completo na TagoIO</p>
<p align="center">
  <img src="https://github.com/williangrleme/IC-Rastreador/blob/main/imgs/6.png" alt="imagem">
</p>

## Documentação


Caso haja interesse em detalhes do projeto, é possivel visualizar dois artigos que escrevi [aqui](https://github.com/williangrleme/IC-Rastreador/blob/main/Documentacao/CONICT_2023.pdf) e [aqui](https://github.com/williangrleme/IC-Rastreador/blob/main/Documentacao/CONICT_2023.pdf).


Caso tenha interesse em visualizar outros relatórios e artigos desenvolvidos ao longo do desenvolvimento do projeto acesse [aqui](https://github.com/williangrleme/IC-Rastreador/tree/main/Documentacao).



## Referência

- LEME, Willian Gustavo Rocha; ALEXANDRE, Rogério Pinto. TECNOLOGIA ASSISTIVA E IOT PARA O MONITORAMENTO DE PESSOAS COM DOENÇAS COGNITIVAS.. In: Anais do Simpósio de Pesquisa e Iniciação Científica e Congresso de Pós-graduação da FUNEPE. Anais...Penápolis(SP) FUNEPE, 2022. Disponível em: https//www.even3.com.br/anais/simposiofunepe2022/562638-TECNOLOGIA-ASSISTIVA-E-IOT-PARA-O-MONITORAMENTO-DE-PESSOAS-COM-DOENCAS-COGNITIVAS. Acesso em: 30/08/2023
## Autor

- [Willian Gustavo](https://github.com/williangrleme)

