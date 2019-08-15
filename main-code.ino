#define LEFTOUT A0  //MARROM
#define LEFTIN A1   //AZUL
#define LEFTAN A4   //CINZA
#define RIGHTAN A5  //ROXO
#define RIGHTIN A2  //BRANCO
#define RIGHTOUT A3 //AMARELO

#define MLF 3  //MOTOR LEFT FORWARD
#define MLB 9  //MOTOR LEFT BACKWARD
#define MRF 10 //MOTOR RIGHT FORWARD
#define MRB 11 //MOTOR RIGHT BACKWARD

#define impulsoajuste 155 //VALOR PWM PARA AJUSTE SOBRE A LINHA
#define impulsofrente 155 //VALOR PWM PARA RETAS E REALIZAR SAIDA DA LINHA
#define PARAR 0           //VALOR PWM PARA PARAR O MOTOR

int PWMR = PARAR; //PWM MOTOR LADO DIREITO
int PWML = PARAR; //PWM MOTOR LADO ESQUERDO

byte LAN = 0;  //ADC da LEFTAN
byte RAN = 0;  //ADC da RIGHTAN
byte LIN = 0;  //ADC da LEFTAN
byte RIN = 0;  //ADC da RIGHTAN
byte LOUT = 0; //ADC da LEFTAN
byte ROUT = 0; //ADC da RIGHTAN

int GAP = 0;              //CONTADOR PARA A PSEUDOFUNÇAO GAP
int GRIP = 0;             //MARCADOR PARA REVERSAO DOS MOTORES
int SpeedLimit = 0;       //CONTADOR PARA LIMITAR VELOCIDADE NAS RESTAS
int SpeedLimit_Cicle = 5; //VALOR MAXIMO ANTES DA ATUAÇAO DO LIMITADOR DE VELOCIDADE

void setup()
{

  Serial.begin(9600); //ATIVAÇÃO DA COMUNICAÇÃO SERIAL COM O RESPECTIVO INTERVALO

} //END SETUP

void loop()
{
  // ADC do IR Analógico (início)  //Somar ao menos mais 100 no valor dado do fundo nunca mais que 800
  if (analogRead(LEFTOUT) <= 700)
  {
    LOUT = 0;
  }
  else
  {
    LOUT = 1;
  }
  if (analogRead(LEFTIN) <= 700)
  {
    LIN = 0;
  }
  else
  {
    LIN = 1;
  }
  if (analogRead(LEFTAN) <= 500)
  {
    LAN = 0;
  }
  else
  {
    LAN = 1;
  }
  if (analogRead(RIGHTAN) <= 500)
  {
    RAN = 0;
  }
  else
  {
    RAN = 1;
  }
  if (analogRead(RIGHTIN) <= 700)
  {
    RIN = 0;
  }
  else
  {
    RIN = 1;
  }
  if (analogRead(RIGHTOUT) <= 700)
  {
    ROUT = 0;
  }
  else
  {
    ROUT = 1;
  }
  // ADC do IR Analógico (fim)

  /*
Serial.print  (PWMR);    //MOSTRAR NA SERIAL A VELOCIDADE DOS MOTORES (1/3)
Serial.print  ("  ");    //MOSTRAR NA SERIAL A VELOCIDADE DOS MOTORES (2/3)
Serial.println(PWML);    //MOSTRAR NA SERIAL A VELOCIDADE DOS MOTORES (3/3)
*/
  /*
Serial.print  (analogRead(LEFTOUT));     //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (1/11)
Serial.print  ("  ");                    //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (2/11)
Serial.print  (analogRead(LEFTIN));      //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (3/11)
Serial.print  ("  ");                    //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (4/11)
Serial.print  (analogRead(LEFTAN));      //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (5/11)
Serial.print  ("  ");                    //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (6/11)
Serial.print  (analogRead(RIGHTAN));     //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (7/11)
Serial.print  ("  ");                    //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (8/11)
Serial.print  (analogRead(RIGHTIN));     //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (9/11)
Serial.print  ("  ");                    //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (10/11)
Serial.println(analogRead(RIGHTOUT));    //MOSTRAR NA SERIAL A LEITURA ANALOGICA DOS SENSORES (11/11)
*/
  Serial.print(LOUT);   //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (1/11)
  Serial.print("  ");   //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (2/11)
  Serial.print(LIN);    //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (3/11)
  Serial.print("  ");   //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (4/11)
  Serial.print(LAN);    //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (5/11)
  Serial.print("  ");   //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (6/11)
  Serial.print(RAN);    //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (7/11)
  Serial.print("  ");   //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (8/11)
  Serial.print(RIN);    //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (9/11)
  Serial.print("  ");   //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (10/11)
  Serial.print(ROUT);   //MOSTRAR NA SERIAL A LEITURA DOS SENSORES (11/11)
  Serial.print("  ");   //MOSTRAR NA SERIAL A VELOCIDADE DOS MOTORES (1/4)
  Serial.print(PWML);   //MOSTRAR NA SERIAL A VELOCIDADE DOS MOTORES (2/4)
  Serial.print("  ");   //MOSTRAR NA SERIAL A VELOCIDADE DOS MOTORES (3/4)
  Serial.println(PWMR); //MOSTRAR NA SERIAL A VELOCIDADE DOS MOTORES (4/4)

  scan(); //FUNÇÃO DE SCAN DOS IR's

  if ((PWML == impulsofrente) && (PWMR == impulsofrente))
  { //FUNÇAO EM TESTE PARA CONTROLE DE VELOCIDADE NAS RETAS !!!!! -INICIO
    SpeedLimit = SpeedLimit + 1;
    if (SpeedLimit == SpeedLimit_Cicle)
    {
      SpeedLimit = 0;
      PWML = PARAR;
      PWMR = PARAR;
    }
  }
  else
  {
    if (SpeedLimit > 0)
    {
      SpeedLimit = SpeedLimit - 1;
    }
  } //FUNÇAO EM TESTE PARA CONTROLE DE VELOCIDADE NAS RETAS !!!!!  -FIM

  analogWrite(MLB, PARAR); //AJUSTANDO PARA FUNCIONAMENTO O MOTOR ESQUERDO
  analogWrite(MRB, PARAR); //AJUSTANDO PARA FUNCIONAMENTO O MOTOR DIREITO
  analogWrite(MLF, PWML);  //AJUSTANDO VELOCIDADE DO MOTOR ESQUERDO
  analogWrite(MRF, PWMR);  //AJUSTANDO VELOCIDADE DO MOTOR DIREITO

  if ((PWML == PARAR) && (GRIP > 5))
  { //ROTINA DE CURVA AGUDA - INICIO
    analogWrite(MLB, impulsofrente);
  }
  if ((PWMR == PARAR) && (GRIP > 5))
  {
    analogWrite(MRB, impulsofrente);
  }
  if (GRIP > 0)
  {
    GRIP = GRIP - 1;
  } //DESATIVANDO GRIP           //ROTINA DE CURVA AGUDA - FIM

} //END LOOP

void scan()
{

  if ((LOUT == 0) && (LIN == 0) && (LAN == 0) && (RAN == 0) && (RIN == 0) && (ROUT == 0))
  {                //TODOS OS SENSORES ESTAO FORA DA LINHA?
    PWML = PARAR;  //PARAR OS MOTORES (1/2)
    PWMR = PARAR;  //PARAR OS MOTORES (2/2)
    GAP = GAP + 1; //CONTADOR PARA ATIVAÇAO DA PSEUDOFUNÇAO "gap"
    if (GAP > 50)
    {              //CONTADOR GAP SUFICIENTE PARA "ativaçao"?
      PWML = 255;  //SIM, MOTORES RECEBEM IMPULSO MAXIMO (1/2)
      PWMR = PWML; //SIM, MOTORES RECEBEM IMPULSO MAXIMO (2/2)
      GAP = 47;    //REDUZIR CONTADOR DE GAP PARA NAO PERMITIR ALTA VELOCIDADE
    }
  } //END: FORA - FORA

  if ((LOUT == 0) && (LIN == 0) && (LAN == 0) && ((RAN == 1) || (RIN == 1) || (ROUT == 1)))
  { //ESQUERDA FORA E DIRETA NA LINHA?
    PWML = impulsoajuste;
    PWMR = PARAR;
    GAP = 0;
  } //END: FORA - LINHA
  if (((LOUT == 1) || (LIN == 1) || (LAN == 1)) && (RAN == 0) && (RIN == 0) && (ROUT == 0))
  { //ESQUERDA NA LINHA E DIRETA FORA?
    PWML = PARAR;
    PWMR = impulsoajuste;
    GAP = 0;
  } //END: LINHA - FORA
  if ((LOUT == 0) && (LIN == 0) && (LAN == 1) && (RAN == 1) && (RIN == 0) && (ROUT == 0))
  { //SENSORES CENTRALIZADOS NA LINHA?
    PWML = impulsofrente;
    PWMR = impulsofrente;
    GAP = 0;
  } //END: CENTRO LINHA

  if ((LIN == 1) && (LAN == 1) && (RAN == 1))
  { //CURVA PARA DIREITA
    PWML = PARAR;
    PWMR = impulsoajuste;
    GAP = 0;
  } //END: CENTRO E ESQUERDA NA LINHA

  if ((LAN == 1) && (RAN == 1) && (RIN == 1))
  { //CURVA PARA DIREITA
    PWML = impulsoajuste;
    PWMR = PARAR;
    GAP = 0;
  } //END: CENTRO E DIREITA NA LINHA

  if ((LAN == 1) && (RAN == 1) && ((LIN == 1) && (RIN == 1)))
  { //PROVAVEL CIRCULO? - CURVAR PARA DIREITA
    PWML = PARAR;
    PWMR = impulsofrente;
    GAP = 0;
  } //END: CENTRO MAIOR LINHA

  if (((LOUT == 1) && (LIN == 1)) || ((RIN == 1) && (ROUT == 1)))
  { //PROVAVEL CURVA AGUDA - ATIVAR GIRO REVERSO
    if (GRIP <= 5)
    {
      GRIP = GRIP + 2;
    }
  } //END: GRIP
}
