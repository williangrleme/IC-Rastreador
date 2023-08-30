<h1 align="center"> USO DE MQTT EM DISPOSITIVO PARA O MONITORAMENTO DE PESSOAS COM DOENÇAS COGNITIVAS </h1>

A complexidade dos desafios sociais decorrentes do envelhecimento da população e das doenças cognitivas, como Alzheimer, demanda cuidados específicos para idosos. A deficiência, definida pela interação entre impedimentos de longo prazo e barreiras sociais, motiva a Tecnologia Assistiva (TA) oferecer soluções para superar limitações, promovendo inclusão e qualidade de vida. 

Nesse contexto, o projeto propõe um dispositivo de baixo custo baseado em IoT e Open Hardware para rastrear pacientes com doenças cognitivas em tempo real, usando tecnologias como LoRa, MQTT, GPS e Wi-Fi. Isso permite monitoramento remoto, autonomia e dados precisos para cuidadores. O projeto visa oferecer aos pacientes independência controlada por meio de uma cerca virtual, além de alertas para situações específicas.
A combinação de IoT e tecnologia assistiva aborda as complexidades do cuidado de pacientes com doenças cognitivas, melhorando sua qualidade de vida. Esse projeto ilustra como a inovação tecnológica pode enfrentar desafios sociais prementes, contribuindo para um futuro mais inclusivo e eficaz no cuidado de pacientes vulneráveis.


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

Em seguida, foi conduzido um teste para demonstrar a visualização completa no Painel de Controle, com o intuito de simular um cenário fiel ao contexto do projeto. Na ilustração abaixo, o dispositivo móvel permanecia parado, resultando em uma velocidade registrada de 0 km/h e a não ativação do alerta de velocidade. Entretanto, considerando que a distância máxima aceitável foi definida como 100 metros, o alerta de alcance máximo foi acionado. A representação também exibiu a distância entre a localização atual do dispositivo e o local fixo estabelecido (Rua Francisco Freitas Franco, 52, Jardim Esplanada, Penápolis).

<p align="center">Visualização do Dashboard completo na TagoIO</p>
<p align="center">
  <img src="https://github.com/williangrleme/IC-Rastreador/blob/main/imgs/6.png" alt="imagem">
</p>

## Documentação

Caso haja interesse em detalhes do projeto, é possivel encontrar os relatórios e artigos desenvolvidos ao longo do desenvolvimento [aqui](https://github.com/williangrleme/IC-Rastreador/tree/main/Documentacao).


## Referência

- LEME, Willian Gustavo Rocha; ALEXANDRE, Rogério Pinto. TECNOLOGIA ASSISTIVA E IOT PARA O MONITORAMENTO DE PESSOAS COM DOENÇAS COGNITIVAS.. In: Anais do Simpósio de Pesquisa e Iniciação Científica e Congresso de Pós-graduação da FUNEPE. Anais...Penápolis(SP) FUNEPE, 2022. Disponível em: https//www.even3.com.br/anais/simposiofunepe2022/562638-TECNOLOGIA-ASSISTIVA-E-IOT-PARA-O-MONITORAMENTO-DE-PESSOAS-COM-DOENCAS-COGNITIVAS. Acesso em: 30/08/2023
## Autor

- [Willian Gustavo](https://github.com/williangrleme)

