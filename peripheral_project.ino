#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
SoftwareSerial mySerial(9, 10);

int sensor=7;
int speaker=8;
int gas_value,Gas_alert_val, Gas_shut_val;
int Gas_Leak_Status;
int sms_count=0;

void setup()
{

pinMode(sensor,INPUT);
pinMode(speaker,OUTPUT);
mySerial.begin(9600);   
Serial.begin(9600);
lcd.begin(16,2);  
delay(500);
}
void loop()
{
CheckGas();
CheckShutDown();
}

void CheckGas()
{

lcd.setCursor(0,0);
lcd.print("Gas Scan - ON");
Gas_alert_val=ScanGasLevel();
if(Gas_alert_val==LOW)
{
 SetAlert(); 
}}

int ScanGasLevel()
{
gas_value=digitalRead(sensor); 
return gas_value; celsius
}

void SetAlert()
{
digitalWrite(speaker,HIGH);  
while(sms_count<3) 
{  
SendTextMessage(); 
}
Gas_Leak_Status=1; 
lcd.setCursor(0,1);
lcd.print("Gas Alert! SMS Sent!");
}

void CheckShutDown()
{
if(Gas_Leak_Status==1)
{

Gas_shut_val=ScanGasLevel();
if(Gas_shut_val==HIGH)
{

lcd.setCursor(0,1);
lcd.print("No Gas Leaking");
digitalWrite(speaker,LOW);
sms_count=0;
Gas_Leak_Status=0;
}}}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    
  delay(1000);
  mySerial.println("AT+CMGS=\"+880..........\"\r"); 
  delay(1000);
  mySerial.println("Gas Leaking
  delay(200);
  mySerial.println((char)26);
  delay(1000);
   mySerial.println("AT+CMGS=\"+880..........\"\r");
  delay(1000);
  mySerial.println("Gas Leaking!");
  delay(200);
  mySerial.println((char)26);
  delay(1000);
  sms_count++;
}
