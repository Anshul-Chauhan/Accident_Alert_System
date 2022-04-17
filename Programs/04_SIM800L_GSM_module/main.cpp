#include <Arduino.h>

int buttonPin = 5, bv = 0;     
int ledPin =  2;      
char sz[32] = "Date , Time";
float latitude = 30.00, longitude = 78.00;

void sms(void);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);    
}

void loop() {
  bv=digitalRead(buttonPin);
  if (bv == LOW) {
    digitalWrite(ledPin, HIGH);
    sms();
  } 
  else {
    digitalWrite(ledPin, LOW);
  }
}

void sms()
{
  Serial.println("AT");    
  delay(1000);
  Serial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  Serial.println("AT+CMGS=\"+919997662478\"\r");  
  delay(1000);
  Serial.print("Emergency Alert at ");
  Serial.print("http://www.google.com/maps/place/");
  delay(2000);
  Serial.print(latitude,6);
  Serial.print(",");
  Serial.println(longitude,6);      
  delay(2000);
  Serial.print(sz);
  Serial.print(",");
  Serial.println((char)26);      //the stopping character
  delay(2000);
}
