#include <LiquidCrystal.h>
#include <dht.h>

/*neste escopo deve ser declarados data e horas corretas*/
int hora=12;
int minuto=53;
int dia=12;
int mes=12;
int ano=2013;
/*neste escopo deve ser declarado data e horas corretas*/

unsigned long previousMilli;

LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
dht DHT;

void setup(){
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Relogio digital:");
  Serial.begin(9600);
}

void loop(){
  int teste;
  int currentMilli = millis();
  static int dayPass=0;
  static int milliSP=0;
  static int secSP=0;
  static int minutoSP=minuto;
  static int horaSP=hora;
  static int diaSP=dia;
  static int mesSP=mes;
  static int anoSP=ano;
  DHT.read11(A0);
  
  Serial.println((int)DHT.temperature);
  delay(30);
  
  lcd.setCursor(0, 1);
  lcd.print("Data: ");
  lcd.print(diaSP);
  lcd.print("/");
  lcd.print(mesSP);
  lcd.print("/");
  lcd.print(anoSP);

  //implementar uma biblioteca apenas para dar refresh - clear e print na tela
  lcd.setCursor(0, 2);
  lcd.print(horaSP);
  lcd.print("h");
  lcd.print(" ");
  lcd.print(minutoSP);
  lcd.print("min");
  lcd.print(" ");
  lcd.print(secSP);
  lcd.print("seg");
  lcd.print("   ");
  
  lcd.setCursor(0, 3);
  lcd.print("temp: ");
  lcd.print(DHT.temperature);
  lcd.print("C");

  lcd.print(" ");
  lcd.print((int)DHT.humidity);
  lcd.print("%");
  lcd.print(" ");
  
  
  if(currentMilli - previousMilli > 1000){
    previousMilli = currentMilli;
    if(secSP==60){
      secSP=0;  
      minutoSP++;
    }
    secSP++;
  }
  
  if(minutoSP==60){
    horaSP++;
    minutoSP=0;  
  }
  
  if(horaSP==24){
    dayPass=1;
    horaSP=0;  
  }
  
  //se um dia passar
  if(horaSP==0 && dayPass){
    diaSP++;
    
    if(mesSP==1 || mesSP==3 || mesSP==5 || mesSP==7 || mesSP==8 || mesSP==10 || mesSP==12){
      if(diaSP>31){
        diaSP=1;
        if(mesSP==12){
          mesSP=1;
          anoSP++;  
        }
      }
    }
    else if(mesSP!=2){
      if(diaSP>30)
        diaSP=1;
    }
    else{
      if(diaSP>28)
        diaSP=1;  
    } 
    dayPass=0;
  }
}
