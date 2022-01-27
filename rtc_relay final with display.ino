#include <Wire.h>
#include <ds3231.h>

#define HOUR  12
#define MIN1  11
#define MIN2  10
#define DATA  8
#define CLOCK 9
#define POWER 13
#define RELAY 7

struct ts t; 

unsigned int seg(unsigned int num) {
  switch (num) {
    case 0 : return 0xA0;
    case 1 : return 0xBE;
    case 2 : return 0x62;
    case 3 : return 0x2A;
    case 4 : return 0x3C;
    case 5 : return 0x29;
    case 6 : return 0x21;
    case 7 : return 0xBA;
    case 8 : return 0x20;
    case 9 : return 0x28;
    }
  return 0;
}

unsigned int seg_hour(unsigned int num) {
  switch (num) {
    case 0 : return 0x80;
    case 1 : return 0x9E;
    case 2 : return 0x42;
    case 3 : return 0x0A;
    case 4 : return 0x1C;
    case 5 : return 0x09;
    case 6 : return 0x01;
    case 7 : return 0x8A;
    case 8 : return 0x00;
    case 9 : return 0x08;
    case 11 : return 0x9E;
    }
  return 0;
}

int displaySingleNum(int num, int place) {
    unsigned int code = seg(num);
    if(place==HOUR){
      code=seg_hour(num);
    }
    unsigned int j;
    for (j = 0x80; j > 0; j = j >> 1) {
        if (code & j){
          digitalWrite(DATA, HIGH);
        }
        else{
          digitalWrite(DATA, LOW);
        }
        digitalWrite(CLOCK, HIGH);
        digitalWrite(CLOCK, LOW);
        
    }
    
    digitalWrite(place, HIGH);
    delay(2);
    digitalWrite(place, LOW);
    
    return 0;
}


void setup() {
  Serial.begin(9600);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  pinMode(RELAY, OUTPUT);
  pinMode(HOUR, OUTPUT);
  pinMode(MIN1, OUTPUT);
  pinMode(MIN2, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(POWER, OUTPUT);
  
  digitalWrite(POWER, HIGH);
  digitalWrite(HOUR, LOW);
  digitalWrite(MIN1, LOW);
  digitalWrite(MIN2, LOW);

  
  /*----------------------------------------------------------------------------
  In order to synchronise your clock module, insert timetable values below !
  ----------------------------------------------------------------------------*/
  /*t.hour=11; 
  t.min=26;
  t.sec=7;
  t.mday=22;
  t.mon=1;
  t.year=2022;
 
  DS3231_set(t);*/
}
 
void loop() {
  int j=0;
  int hour=0;
  int min1=0;
  int min2=0;
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
  digitalWrite(RELAY, LOW);


  if(t.hour==9 && t.min==0){
    while(t.sec<5){
        //digital pin high
        digitalWrite(RELAY, HIGH);
        DS3231_get(&t);
        delay(1000);
        
    }
    digitalWrite(RELAY, LOW);
  }
  
  if(t.hour==13 && t.min==0){
    while(t.sec<5){
        //digital pin high
        digitalWrite(RELAY, HIGH);
        DS3231_get(&t);
        delay(1000);
        
    }
    digitalWrite(RELAY, LOW);
  }

  if(t.hour==13 && t.min==55){
    while(t.sec<6){
        //digital pin high
        digitalWrite(RELAY, HIGH);
        DS3231_get(&t);
        delay(1000);
        
    }
    digitalWrite(RELAY, LOW);
  }

  if(t.hour==14 && t.min==0){
    while(t.sec<4){
        //digital pin high
        digitalWrite(RELAY, HIGH);
        DS3231_get(&t);
        delay(1000);
        
    }
    digitalWrite(RELAY, LOW);
  }

  if(t.hour==18 && t.min==0){
    while(t.sec<5){
        //digital pin high
        digitalWrite(RELAY, HIGH);
        DS3231_get(&t);
        delay(1000);
        
    }
    digitalWrite(RELAY, LOW);
  }
  hour = t.hour % 12;
  if(hour==11){
    hour = 11;
  }else if(hour==10){
    hour = 0;
  }else if(hour==0){
    hour = 2;
  }
  
  min1 = t.min/10;
  min2 = t.min % 10;
  for (j = 0; j < 150; j++) {
      displaySingleNum(hour, HOUR);
      displaySingleNum(min1, MIN1);
      displaySingleNum(min2, MIN2);
      
  }
}
