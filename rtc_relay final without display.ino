#include <Wire.h>
#include <ds3231.h>
 
struct ts t; 
 
void setup() {
  Serial.begin(9600);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  pinMode(8, OUTPUT);
  /*----------------------------------------------------------------------------
  In order to synchronise your clock module, insert timetable values below !
  ----------------------------------------------------------------------------*/
  /*t.hour=17; 
  t.min=1;
  t.sec=0;
  t.mday=17;
  t.mon=11;
  t.year=2021;
 
  DS3231_set(t);*/
}
 
void loop() {
  DS3231_get(&t);
  Serial.print("Date : ");
  Serial.print(t.mday);
  Serial.print("/");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.year);
  Serial.print("\t Hour : ");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(".");
  Serial.println(t.sec);
  digitalWrite(8, LOW);

  digitalWrite(8, LOW);

  if(t.hour==12 && t.min==59){
    while(t.sec<7){
        //digital pin high
        digitalWrite(8, HIGH);
        DS3231_get(&t);
        delay(1000);
        
    }
    digitalWrite(8, LOW);
  }

  if(t.hour==13 && t.min==55){
    while(t.sec<10){
        //digital pin high
        digitalWrite(8, HIGH);
        DS3231_get(&t);
        delay(1000);
        
    }
    digitalWrite(8, LOW);
  }

  if(t.hour==14 && t.min==0){
    while(t.sec<4){
        //digital pin high
        digitalWrite(8, HIGH);
        DS3231_get(&t);
        delay(1000);
        
    }
    digitalWrite(8, LOW);
  }

  if(t.hour==18 && t.min==0){
    while(t.sec<7){
        //digital pin high
        digitalWrite(8, HIGH);
        DS3231_get(&t);
        delay(1000);
        
    }
    digitalWrite(8, LOW);
  }

  /*if(t.hour==13 && t.min==55){
    while(t.sec<10){
      //digital pin high
      }
      //digital pin low
    }

  if(t.hour==17 && t.min==59){
    while(t.sec<10){
      //digital pin high
      }
      //digital pin low
    }*/
 
  delay(1000);
}
