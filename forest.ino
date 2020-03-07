#include "dht.h"
#include <SoftwareSerial.h>

#include <TinyGPS.h> 
float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  

#define sen1 A0
#define sen2 A1
#define sen3 A2
#define sen4 A3

#define buzz 7

dht DHT1;
dht DHT2;
dht DHT3;
dht DHT4;

String latitude = String(lat,6);
String longitude = String(lon,6);

SoftwareSerial gpsmodule(3,4);//connection tx rx

SoftwareSerial BTmodule(8,9); //connection tx rx

SoftwareSerial GSMmodule(10 ,11); //connection tx rx

TinyGPS gps; // create gps object 

void initModule(String cmd, char *res, int t)
{
  while(1)
  {
    Serial.println(cmd);
    GSMmodule.println(cmd);
    delay(100);
    while(GSMmodule.available()>0)
    {
       if(GSMmodule.find(res))
       {
        Serial.println(res);
        delay(t);
        return;
       }

       else
       {
        Serial.println("Error");
       }
    }
    delay(t);
  }
}



void setup() {
  
  
  Serial.begin(9600);
  gpsmodule.begin(9600);
  BTmodule.begin(9600);
  GSMmodule.begin(9600);
  pinMode(buzz, OUTPUT);
  delay(500);
}

void loop() {

  while(gpsmodule.available()){ // check for gps data
    if(gps.encode(gpsmodule.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon);
    }
    }

  
  Serial.println(latitude+";"+longitude);
  
  DHT1.read11(sen1);
  
  Serial.print("Temperature in Celsius");
  Serial.print(DHT1.temperature);
  Serial.print("    Current humidity = ");
  Serial.print(DHT1.humidity);
  Serial.println();
  
  DHT2.read11(sen2);
  
  Serial.print("Temperature in Celsius");
  Serial.print(DHT2.temperature);
  Serial.print("    Current humidity = ");
  Serial.print(DHT2.humidity);
  Serial.println();
  
  DHT3.read11(sen3);
  
  Serial.print("Temperature in Celsius");
  Serial.print(DHT3.temperature);
  Serial.print("    Current humidity = ");
  Serial.print(DHT3.humidity);
  Serial.println();

  DHT4.read11(sen4);
  
  Serial.print("Temperature in Celsius");
  Serial.print(DHT4.temperature);
  Serial.print("    Current humidity = ");
  Serial.print(DHT4.humidity);
  Serial.println();

  delay(1000);
  
  GSMmodule.println("AT");
   delay(500);
  GSMmodule.println("AT+CMGF=1");
   delay(500);

   GSMmodule.print("AT+CMGS=");
   GSMmodule.print("xxxxxxxxxx");    //mobile no. for SMS alert
   GSMmodule.println('"');
   delay(1000);
    Serial.println();
    digitalWrite(buzz, LOW);
    if(DHT1.temperature > 70.0 || DHT1.humidity < 20.0 )
    {
       
        digitalWrite(buzz, HIGH);
        BTmodule.print("Temperature in Celsius");
        BTmodule.print(DHT1.temperature);
        BTmodule.print("    Current humidity = ");
        BTmodule.print(DHT1.humidity);
        BTmodule.println();

        Maps();
       
        Fire();
        BTmodule.println("Might be Fire in the grid One");
        GSMmodule.println("Might be Fire in the grid One");
        Serial.println("Might be Fire in the grid One");

        callMe();
    }
    Serial.println();
    if(DHT2.temperature > 70.0 || DHT2.humidity < 20.0 )
    {
        digitalWrite(buzz, HIGH);
        
        BTmodule.print("Temperature in Celsius");
        BTmodule.print(DHT2.temperature);
        BTmodule.print("    Current humidity = ");
        BTmodule.print(DHT2.humidity);
        BTmodule.println();

        Maps();
         
        Fire();
        BTmodule.println("Might be Fire in the grid two");
        GSMmodule.println("Might be Fire in the grid two");
        Serial.println("Might be Fire in the grid two");
        
        callMe();
    }
    Serial.println();
    if(DHT3.temperature > 70.0 || DHT3.humidity < 20.0 )
    {
        digitalWrite(buzz, HIGH);
        BTmodule.print("Temperature in Celsius");
        BTmodule.print(DHT3.temperature);
        BTmodule.print("    Current humidity = ");
        BTmodule.print(DHT3.humidity);
        BTmodule.println();
        
        Maps();
        
        Fire();
        
        BTmodule.println("Might be Fire in the grid three");
        GSMmodule.println("Might be Fire in the grid three");
        Serial.println("Might be Fire in the grid three");
        
        callMe();
    }
    Serial.println();
    if(DHT4.temperature > 70.0 || DHT4.humidity < 20.0 )
    {
        digitalWrite(buzz, HIGH);
        BTmodule.print("Temperature in Celsius");
        BTmodule.print(DHT4.temperature);
        BTmodule.print("    Current humidity = ");
        BTmodule.print(DHT4.humidity);
        BTmodule.println();

        
        Maps();
        
        Fire();
        BTmodule.println("Might be Fire in the grid four");
        GSMmodule.println("Might be Fire in the grid four");
        Serial.println("Might be Fire in the grid four");
        
        callMe();
        }
        Serial.println();
       digitalWrite(buzz, LOW);
}


void callMe()
{
        Serial.println("Calling  ");
        GSMmodule.println("ATD+XXxxxxxxxxxx;");// number and semicolon is compulsory at the end of number
        delay(1000);
        Serial.println("Call ended");
}

void Fire()
{
        
        Serial.println("FIRE ALERT !!!!!");
        BTmodule.println("FIRE ALERT !!!!!");
        GSMmodule.println("FIRE ALERT !!!!!");
}

void Maps()
{
        BTmodule.println(latitude+";"+longitude);
        GSMmodule.println(latitude+";"+longitude);
        Serial.println(latitude+";"+longitude);

        Serial.print("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=");
        GSMmodule.print("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=");
        BTmodule.print("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=");
        
}
