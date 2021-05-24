#include <LiquidCrystal.h>//povikuvanje na LCD bibliotekata
#include "DHT.h"//povikuvanje na DHT sensor bibliotekata 
 
#define DHTPIN 8     //definiranje na DHT pinot     
 
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //definiranje na LCD pinovite
 
#define DHTTYPE DHT22       //odreduvanje na DHT tipot
DHT dht(DHTPIN, DHTTYPE);   
 
char temperature[] = "Temp = 00.0 C"; //Temperaturna promenliva
char humidity[]    = "Vlaz = 00.0 %"; //Promenliva za vlaznost
const int hummidityd = 9; //digitalen pin na senzorot za dozd
const int hummiditya = A0; //analogen pin na senzort za dozd
const int buzzer = 10; //Buzzer pinot
const int hygrometer = A1; //analogniot pin za senzorot za vlaznost na pocvata
int led1=13; //led1 pin
int led2=12; //led2 pin
int led3=11; //led3 pin
int value_analog; //analogna vrednost na senzorot za dozd 
int value; //vrednost na senzorot za vlaznost na pocvata

void setup() {
  Serial.begin(9600); //zapocnuvanje na Serial monitor
  lcd.begin(16, 2); //definiranje na LCD ekranot
  dht.begin(); //startuvanje na DHT senzorot
  pinMode(hummidityd, INPUT); 
  pinMode(hummidityd, INPUT);
  pinMode (buzzer, OUTPUT);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
}
 
void loop() {
  delay(1000);               
  int Vlaz = dht.readHumidity() * 10; //citanje na vlaznosta
  int Temp = dht.readTemperature() * 10; //citanje na temperaturata
  if (isnan(Vlaz) || isnan(Temp)) {  //ako temperaturata ili vlaznosta se nedostapni da ispecati Error
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Error"); //pecatenje na LCD ekranot
    return;
  }
  if(Temp < 0){ //ako e negativna temperaturata da se stavi '-'
    temperature[6] = '-';
    Temp = abs(Temp);
  }
  else
  temperature[6] = ' ';
  temperature[7]   = (Temp / 100)%10  + 48;
  temperature[8]   = (Temp / 10)  % 10  + 48;
  temperature[10]  =  Temp % 10 + 48;
  temperature[11]  = 223;        
  if(Vlaz >= 1000)
    humidity[6]    = '1';
  else
  humidity[6]    = ' ';
  humidity[7]      = (Vlaz / 100) % 10 + 48;
  humidity[8]      = (Vlaz / 10) % 10 + 48;
  humidity[10]     =  Vlaz % 10 + 48;
  lcd.setCursor(0, 0);//Postavuvanje na pocetokot na pecatenjeto
  lcd.print(temperature);//pecatanje na temparaturata na LCD-to
  lcd.setCursor(0, 1);//Postavuvanje na pocetokot na pecatenjeto
  lcd.print(humidity);//Pecatenje na vlaznosta na LCD-to
  if(digitalRead(hummidityd) == LOW) //Davanje na naredbi za senzorot za dozd
  {
    Serial.println("Digital value : wet"); 
    delay(10);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print ("Zavrna");//Predupreduvanje deka zavrnalo na LCD ekran.
  }
else
  {
    Serial.println("Digital value : dry");
    delay(10); 
  }
value_analog=analogRead(hummidityd);  
 Serial.print("Analog value : "); //pecatenje na analognata vrednost na senzorot za dozd
 Serial.println(value_analog); 
 Serial.println("");
  delay(1000);
   if(digitalRead(hummidityd) == LOW) //davanje na naredba na Buzzer
  {
    tone(buzzer, 1000); 
    delay(1000); 
  }
else
  {
    noTone(buzzer);
    delay(1000); 
  }
    value = analogRead(hygrometer);    //odreduvanje na vrednosta na podatocite na senzorot za vlaznost na pocvata,vklucitelno kod od internet
  value = constrain(value,400,1023);  //kod od internet
  value = map(value,400,1023,100,0);  //kod od internet
  Serial.print("Vlaznost na pocvata: "); //pecatenje na vlaznosta vo Serial monitor
  Serial.print(value);
  Serial.println("%");
  delay(2000); 
  if(value<=25) //davanje na naredbi za LED diodite
  {
    digitalWrite(led1, HIGH);
  }
  else
  {
    digitalWrite(led1, LOW);
  }
  if(value>25 && value<75)
  {
    digitalWrite(led2, HIGH);
  }
  
  else
  {
    digitalWrite(led2, LOW);
  }
  if(value>=75)
  {
    digitalWrite(led3, HIGH);
    lcd.clear();
    lcd.print("Vlaznosta na pocvata e nad 75%");//Predupreduvanje deka vlaznosta na pocvata e nad 75% na LCD ekran.
  } 
  
  else
  {
    digitalWrite(led3, LOW);
  }
  }
