#include "ADS1118.h"

//dichiarazione varibili per il SPI-Setting
uint32_t clk = 1000000; //freq. default 1 MHZ
uint8_t  bOrder = 1; //Most sign. bit first
uint8_t  dMode = 1; //spi mode 1

//Istanza di SPISetting 
SPISettings spiset(clk,bOrder,dMode);

//Istanze di SPIClass
SPIClass hspi (HSPI);
SPIClass vspi (VSPI);

//Mappatura dei CS
int8_t hcs[4] = {15, 25, 26, 27};
int8_t vcs[4] = {4, 5, 21, 22};

//Istanze vettore di oggetti per rappresentare gli otto ADCs
ADS1118 adc[8] = {
  ADS1118(hcs[0],&hspi), ADS1118(hcs[1],&hspi), ADS1118(hcs[2],&hspi), ADS1118(hcs[3],&hspi), //primi quattro HSPI
  ADS1118(vcs[0],&vspi), ADS1118(vcs[1],&vspi), ADS1118(vcs[2],&vspi), ADS1118(vcs[3],&vspi), //ultimi quattro VSPI
};

void setup(){
  
  Serial.begin(256000);
  pinMode(2, OUTPUT); //Abilitazione IO2 per il controllo del Led
  
  //Settaggio di tutte le impostazioni di ogni ADC
  for(int i = 0; i < 8; i++){
    adc[i].begin();
    adc[i].setSamplingRate(adc->RATE_860SPS); //Viene impostato il rate massimo di 860 Samples per seconds
    adc[i].setFullScaleRange(adc->FSR_0256);  //Viene impostato un full range di 256mV
    adc[i].setContinuousMode();     //Abilitato il ContinousMode()
    adc[i].disablePullup();         //Vengono disabilitate le resistenze di pullup
  }

}

void loop(){
  for(int i = 0 ; i < 8 ; i++){
    adc[i].setInputSelected(adc->DIFF_0_1);   //Vengono considerati gli ingressi differenziali tra 0 e 1 
    Serial.print(String(adc[i].getMilliVolts(),10)+",");
    adc[i].setInputSelected(adc->DIFF_2_3);   //Vengono considerati gli ingressi differenziali tra 2 e 3
    Serial.print(String(adc[i].getMilliVolts(),10)); if(i!=7) Serial.print(",");
  }
  Serial.println("");
  digitalWrite(2, !digitalRead(2)); //led io2 toggle
  //delay(2000);
}