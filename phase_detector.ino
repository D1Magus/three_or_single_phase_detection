/* SENAI SC
 * Alunos: Eduardo Expedito Menezes, Fernando Henrique Vaz Mello e Gabriel Vinicius Tomasi
 * Professor: Carlos Carvalho
 * Data: 22/06/2021 
 * Projeto: Detecção de sistemas trifásicos ou monofásicos
 */


#include <LiquidCrystal.h>  
  
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);     


volatile float freq1, freq2;
float lastMillis, currentTime, lastReset;

void setup() {
  lcd.begin(16,2);
  lcd.clear(); 
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  attachInterrupt(digitalPinToInterrupt(18), phase1, RISING);
  attachInterrupt(digitalPinToInterrupt(19), phase2, RISING);
  freq1 = 0;
  freq2 = 0;
  lastMillis = 0;
  lastReset = 0;

}

void phase1(){
  freq1++;
}

void phase2(){
  freq2++;
  
}

void loop() {
  currentTime = millis();
  if(currentTime - lastMillis > 200){
      lastMillis = millis();
      if(freq1 > 0 && freq2 > 0){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("3-phase");
        lcd.setCursor(0, 1);
        lcd.print("P1/2 Connected");
      }
      else if(freq1 > 0){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Single-phase");
        lcd.setCursor(0, 1);
        lcd.print("P1 Connected");
      }
      else if(freq2 > 0){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Single-phase");
        lcd.setCursor(0, 1);
        lcd.print("P2 Connected");
      }
      else{
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Connection");
      }
  }
  if(currentTime - lastReset > 100){
    lastReset = millis();
    freq1 = 0;
    freq2 = 0;
  }


}
