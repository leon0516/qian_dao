#include <Wire.h> 
#include <aJSON.h>
#include <avr/pgmspace.h>
aJsonStream serial_stream(&Serial);
#define dht_dpin A0
byte bGlobalErr;
byte dht_dat[5];
// Specify data and clock connections and instantiate SHT1x object
 
void setup()
{  
 
 InitDHT();
Serial.begin(9600);
delay(300);
}
void loop()
{
  dt11();
}
void dt11 (){
ReadDHT();
  switch (bGlobalErr){
     case 0:
		 sendData();
 // Serial.print("Current humdity = ");
 // Serial.print(dht_dat[0], DEC);
 // Serial.print(".");
 // Serial.print(dht_dat[1], DEC);
 // Serial.print("%  ");
 // Serial.print("temperature = ");
 // Serial.print(dht_dat[2], DEC);
 // Serial.print(".");
 // Serial.print(dht_dat[3], DEC);
 // Serial.println("C  ");
        break;
     case 1:
        Serial.println("Error 1: DHT start condition 1 not met.");
        break;
     case 2:
        Serial.println("Error 2: DHT start condition 2 not met.");
        break;
     case 3:
        Serial.println("Error 3: DHT checksum error.");
        break;
     default:
        Serial.println("Error: Unrecognized code encountered.");
        break;
      }
  delay(800);

}
void sendData()
{
  aJsonObject *msg = createMessage();
  aJson.print(msg, &serial_stream);
  Serial.println(); /* Add newline. */
  aJson.deleteItem(msg);
//*******************************************        
  delay(100);
}
 
/* Generate message like: { "ID":1,"temperature":25.5,"humidity":31.1} */
aJsonObject *createMessage()
{
  char    *id = "tc504";
  int  temp = dht_dat[0];
  int  humidity = dht_dat[2];
 
  aJsonObject *msg = aJson.createObject();
  if (msg != NULL) {
     aJson.addStringToObject(msg, "ID", id);
     aJson.addNumberToObject(msg, "humidity", temp);
     aJson.addNumberToObject(msg, "temperature", humidity);
    return msg;
   }
}
 
void printProgStr(const prog_char* str) {
  char c;
  if (!str) {
    return;
  }
  while ((c = pgm_read_byte(str))) {
    Serial.write(c);
    str++;
  }
}


void InitDHT(){
   pinMode(dht_dpin,OUTPUT);
        digitalWrite(dht_dpin,HIGH);
}

void ReadDHT(){
bGlobalErr=0;
byte dht_in;
byte i;
digitalWrite(dht_dpin,LOW);
delay(20);

digitalWrite(dht_dpin,HIGH);
delayMicroseconds(40);
pinMode(dht_dpin,INPUT);
//delayMicroseconds(40);
dht_in=digitalRead(dht_dpin);

if(dht_in){
   bGlobalErr=1;
   return;
   }
delayMicroseconds(80);
dht_in=digitalRead(dht_dpin);

if(!dht_in){
   bGlobalErr=2;
   return;
   }
delayMicroseconds(80);
for (i=0; i<5; i++)
   dht_dat[i] = read_dht_dat();
pinMode(dht_dpin,OUTPUT);
digitalWrite(dht_dpin,HIGH);
byte dht_check_sum =
       dht_dat[0]+dht_dat[1]+dht_dat[2]+dht_dat[3];
if(dht_dat[4]!= dht_check_sum)
   {bGlobalErr=3;}
};

byte read_dht_dat(){
  byte i = 0;
  byte result=0;
  for(i=0; i< 8; i++){
      while(digitalRead(dht_dpin)==LOW);
      delayMicroseconds(30);
      if (digitalRead(dht_dpin)==HIGH)
     result |=(1<<(7-i));
    while (digitalRead(dht_dpin)==HIGH);
    }
  return result;
}

