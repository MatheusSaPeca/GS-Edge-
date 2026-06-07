#include <LiquidCrystal.h>

// ==================================================
// CONFIGURAÇÃO DO LCD
// ==================================================
// LCD paralelo 16x2: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 13, 2, 3, 4, 5);

// ==================================================
// DEFINIÇÃO DOS PINOS
// ==================================================
// Potenciômetro simulando o sensor de chuva
const int SENSOR_CHUVA = A0;

// LEDs indicadores dos níveis de chuva
const int LED_VERDE = 8;      // Risco OK
const int LED_AMARELO = 9;    // Chuva fraca
const int LED_LARANJA = 10;   // Chuva moderada
const int LED_VERMELHO = 7;   // Chuva intensa

// Buzzer para alerta sonoro
const int BUZZER = 11;

// ==================================================
// LIMITES DE CLASSIFICAÇÃO
// ==================================================
// No sensor simulado:
// 1023 = seco
// 0 = muito molhado
const int LIMITE_OK = 800;
const int LIMITE_FRACA = 550;
const int LIMITE_MODERADA = 300;

// ==================================================
// ESTADOS DO SISTEMA
// ==================================================
// Define os possíveis estados da chuva
enum EstadoChuva {
  RISCO_OK,
  CHUVA_FRACA,
  CHUVA_MODERADA,
  CHUVA_INTENSA
};

// Guarda o estado atual e o estado anterior
EstadoChuva estadoAtual = RISCO_OK;
EstadoChuva estadoAnterior = RISCO_OK;

// Controle de tempo para LCD e buzzer
unsigned long ultimoBip = 0;
unsigned long ultimaAtualizacao = 0;

// ==================================================
// SETUP
// ==================================================
void setup() {
  // Inicializa o monitor serial
  Serial.begin(9600);

  // Configura os LEDs como saída
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_LARANJA, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  // Configura o buzzer como saída
  pinMode(BUZZER, OUTPUT);

  // Inicializa o display LCD
  lcd.begin(16, 2);
  lcd.clear();

  // Mensagem inicial no LCD
  lcd.setCursor(0, 0);
  lcd.print("CLIMAVISION");

  lcd.setCursor(0, 1);
  lcd.print("RAIN MONITOR");

  delay(2000);
  lcd.clear();

  // Mensagem inicial no monitor serial
  Serial.println("ClimaVision Rain Monitor iniciado");
}

// ==================================================
// LOOP PRINCIPAL
// ==================================================
void loop() {
  // Lê o valor do sensor de chuva
  int leitura = analogRead(SENSOR_CHUVA);

  // Converte a leitura para porcentagem de chuva
  int chuvaPercentual = map(leitura, 1023, 0, 0, 100);
  chuvaPercentual = constrain(chuvaPercentual, 0, 100);

  // Classifica o nível de chuva
  estadoAtual = classificarChuva(leitura);

  // Atualiza LEDs e buzzer
  atualizarLEDs();
  atualizarBuzzer();

  // Atualiza LCD e serial em intervalos definidos
  if (millis() - ultimaAtualizacao >= 700 || estadoAtual != estadoAnterior) {
    atualizarLCD(chuvaPercentual);
    imprimirSerial(leitura, chuvaPercentual);

    ultimaAtualizacao = millis();
    estadoAnterior = estadoAtual;
  }
}

// ==================================================
// CLASSIFICAÇÃO DA CHUVA
// ==================================================
// Define o estado do sistema com base na leitura
EstadoChuva classificarChuva(int leitura) {
  if (leitura >= LIMITE_OK) {
    return RISCO_OK;
  } else if (leitura >= LIMITE_FRACA) {
    return CHUVA_FRACA;
  } else if (leitura >= LIMITE_MODERADA) {
    return CHUVA_MODERADA;
  } else {
    return CHUVA_INTENSA;
  }
}

// ==================================================
// ATUALIZAÇÃO DO LCD
// ==================================================
// Mostra o status da chuva e o percentual no display
void atualizarLCD(int chuvaPercentual) {
  lcd.clear();

  lcd.setCursor(0, 0);

  switch (estadoAtual) {
    case RISCO_OK:
      lcd.print("RISCO: OK");
      break;

    case CHUVA_FRACA:
      lcd.print("CHUVA FRACA");
      break;

    case CHUVA_MODERADA:
      lcd.print("CHUVA MODERADA");
      break;

    case CHUVA_INTENSA:
      lcd.print("CHUVA INTENSA");
      break;
  }

  lcd.setCursor(0, 1);
  lcd.print("Nivel: ");
  lcd.print(chuvaPercentual);
  lcd.print("%");
}

// ==================================================
// ATUALIZAÇÃO DOS LEDS
// ==================================================
// Acende o LED correspondente ao nível de chuva
void atualizarLEDs() {
  // Apaga todos os LEDs antes de acender o correto
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_LARANJA, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  switch (estadoAtual) {
    case RISCO_OK:
      digitalWrite(LED_VERDE, HIGH);
      break;

    case CHUVA_FRACA:
      digitalWrite(LED_AMARELO, HIGH);
      break;

    case CHUVA_MODERADA:
      digitalWrite(LED_LARANJA, HIGH);
      break;

    case CHUVA_INTENSA:
      digitalWrite(LED_VERMELHO, HIGH);
      break;
  }
}

// ==================================================
// CONTROLE DO BUZZER
// ==================================================
// O som aumenta conforme o nível de chuva
void atualizarBuzzer() {
  unsigned long agora = millis();

  int frequencia = 0;
  int duracao = 0;
  int intervalo = 0;

  switch (estadoAtual) {
    case RISCO_OK:
      frequencia = 300;    // som mais grave
      duracao = 40;        // bip curto
      intervalo = 4000;    // demora mais para tocar
      break;

    case CHUVA_FRACA:
      frequencia = 600;    // som leve
      duracao = 80;
      intervalo = 2500;
      break;

    case CHUVA_MODERADA:
      frequencia = 900;    // som médio
      duracao = 120;
      intervalo = 1200;
      break;

    case CHUVA_INTENSA:
      frequencia = 1400;   // som mais agudo
      duracao = 180;
      intervalo = 400;     // toca com mais frequência
      break;
  }

  // Emite bipes em intervalos controlados
  if (agora - ultimoBip >= intervalo) {
    ultimoBip = agora;
    tone(BUZZER, frequencia, duracao);
  }
}

// ==================================================
// MONITOR SERIAL
// ==================================================
// Exibe os dados da simulação no monitor serial
void imprimirSerial(int leitura, int chuvaPercentual) {
  Serial.print("Sensor: ");
  Serial.print(leitura);

  Serial.print(" | Chuva: ");
  Serial.print(chuvaPercentual);
  Serial.print("%");

  Serial.print(" | Status: ");

  switch (estadoAtual) {
    case RISCO_OK:
      Serial.println("Risco OK");
      break;

    case CHUVA_FRACA:
      Serial.println("Chuva fraca");
      break;

    case CHUVA_MODERADA:
      Serial.println("Chuva moderada");
      break;

    case CHUVA_INTENSA:
      Serial.println("Chuva intensa");
      break;
  }
}