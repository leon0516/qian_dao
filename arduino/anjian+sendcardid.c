#include <SPI.h>
#include <Ethernet.h>
#include <RFID.h>
String a,b,c,d,e;
RFID rfid(53,46);
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAE, 0xFE, 0xDA, 0xFA, 0xAE };
byte ip[] = { 192, 168, 0, 166   }; 

// Enter the IP address of the server you're connecting to:
IPAddress server(112,124,39,140); 

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 23 is default for telnet;
// if you're using Processing's ChatServer, use  port 10002):
EthernetClient client;

void setup() {
  // start the Ethernet connection:
	pinMode(8,INPUT); 
	pinMode(12, OUTPUT); 
  Ethernet.begin(mac,ip);
  SPI.begin();
  rfid.init();
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 8480)) {
    Serial.println("connected");
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  e=" ";
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.println(c);
  }

  // as long as there are bytes in the serial queue,
  // read them and send them out the socket if it's open:

    if (client.connected()) {
            if(digitalRead(8)==LOW)
        {
          delay(10); 
          if(digitalRead(8)==LOW) 
          {
            digitalWrite(12, LOW);
          }
        }
		if (rfid.isCard()) {
		Serial.println("Find the card!");
		//读取卡序列号
			if (rfid.readCardSerial()) {
			 Serial.print("The card's number is  : ");
			  a=String(rfid.serNum[0],HEX);
				if (a.length() < 2)
				{
					a = "0" + a;
				}
			  b=String(rfid.serNum[1],HEX);
			  	if (b.length() < 2){
					b = "0" + b;
				}
			  c=String(rfid.serNum[2],HEX);
				if (c.length() < 2){
					c = "0" + c;
				}
			  d=String(rfid.serNum[3],HEX);
				if (d.length() < 2){
					d = "0" + d;
				}
			  e=a + b +c +d;
			  Serial.println(e);
			}
		//选卡，可返回卡容量（锁定卡片，防止多数读取），去掉本行将连续读卡
		rfid.selectTag(rfid.serNum);
		}
		rfid.halt();
		if(e!=" "){
		client.println(e);
		}
		delay(100);
    }
    if (client.available()) {
            char c = client.read();
		if(c=='1'){
		digitalWrite(12, HIGH);
                }
                else if (c == '3'){
                Serial.println("The wrong Card No. was enrolled!");}
                else {
                Serial.print("error");}
                Serial.print(c);
    }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    // do nothing:
    while(true);
  }
}