 **ClimaVision Rain Monitor**
 Descrição do Projeto

O ClimaVision Rain Monitor é uma solução desenvolvida para a disciplina de Edge Computing, integrada ao projeto maior ClimaVision, que tem como objetivo monitorar e apresentar informações climáticas de forma simples e acessível.

Neste projeto, foi desenvolvido um sistema capaz de simular a detecção de chuva utilizando Arduino. A solução realiza a leitura de um sensor de chuva simulado, processa as informações e apresenta o nível de chuva em tempo real por meio de um display LCD, LEDs indicadores e alertas sonoros.

O projeto foi desenvolvido utilizando o simulador Wokwi, permitindo a demonstração completa do funcionamento sem a necessidade de montagem física.

 **Objetivo da Solução**

O objetivo do projeto é monitorar o nível de chuva em um ambiente e informar o usuário sobre as condições climáticas identificadas.

A solução busca:

Simular a detecção de chuva;
Exibir informações de forma visual e intuitiva;
Utilizar indicadores luminosos para representar diferentes níveis de chuva;
Emitir alerta sonoro em situações de chuva intensa;
Demonstrar a aplicação de conceitos de Edge Computing no monitoramento climático.

 **Componentes Utilizados**

Arduino Uno;
Display LCD 16x2;
Potenciômetro (simulando sensor de chuva);
LED Verde;
LED Amarelo;
LED Laranja;
LED Vermelho;
Buzzer;
Resistores de 220Ω;
Protoboard;
Jumpers;
 
**Explicação do Funcionamento**

O sistema realiza leituras contínuas do sensor de chuva simulado através de um potenciômetro conectado ao Arduino.
 Faixa    | Situação             
 
 Verde    | Risco OK (sem chuva) 
 Amarelo  | Chuva Fraca          
 Laranja  | Chuva Moderada       
 Vermelho | Chuva Intensa 

 As informações são exibidas no display LCD e também registradas no Monitor Serial.
 Quando o nível de chuva intensa é detectado, o buzzer é acionado para alertar o usuário.

 **Estrutura do Circuito**

-Entradas:
Potenciômetro (Sensor de Chuva Simulado);

-Processamento:
Arduino Uno;

-Saídas:
Display LCD 16x2;
LED Verde;
LED Amarelo;
LED Laranja;
LED Vermelho;
Buzzer;

**Fluxo do Sistema**

Sensor de Chuva
       ↓
   Arduino Uno
       ↓
 
  LCD 16x2     
  LEDs         
  Buzzer 

**Instruções de Execução**

Utilizando o Wokwi

1.Acesse o projeto no Wokwi.
2.Clique em Start Simulation.
3.Ajuste o potenciômetro para simular diferentes níveis de chuva.
4.Observe:
 As mensagens exibidas no LCD;
 O acionamento dos LEDs;
 O alerta sonoro em caso de chuva intensa.
5.Abra o Monitor Serial para acompanhar os dados em tempo real. 

**Tecnologias Utilizadas**

-Arduino C++;
-Wokwi Simulator;
-GitHub;

**Integrantes do Grupo**

-Matheus Sá Teles de Souza;
-Pedro Antônio Borges;
-Guilherme Cunha Romano;
-Guilherme Alvejan;
 
