#include <Arduino.h>

#include <TinyGPS.h>
#include<SoftwareSerial.h>

int x=13, y=12, z=14;
int xv=0, yv=0, zv=0;
int alarmPin = 2, ledPin = 27;
int buttonPin = 5, bv = 0;
int fr = 15, fv = 0;
int pz = 4, pv = 0;
TinyGPS gps;
SoftwareSerial gps_port(16,17); // Rx2 Tx2
char data[32];
float latitude, longitude;

void encode_gps(void);
void adxl(void);
void fire(void);
void piezo(void);
void sms(void);
void sms_s(void);
void getgps(TinyGPS &gps);
static void print_date(TinyGPS &gps);

void setup()
{
 pinMode(alarmPin, OUTPUT); 
 digitalWrite(alarmPin, LOW);
 pinMode(ledPin, OUTPUT); 
 digitalWrite(ledPin, LOW);
 pinMode(fr, INPUT); 
 digitalWrite(fr, LOW);
 pinMode(buttonPin, INPUT);
 pinMode(pz, INPUT); 
 Serial.begin(9600);
 gps_port.begin(9600);
 delay(1000);
}

void loop()
{
  encode_gps();
  adxl();
  fire();
  piezo();
  bv=digitalRead(buttonPin);
  if (bv == LOW) {
    sms_s();
  } 
  else {
  }
}

void adxl()
{
  xv = analogRead(x);
  yv = analogRead(y);
  zv = analogRead(z);
  //Serial.println(xv);
  //Serial.println(yv);
  if((xv>2050) || (xv<1600) || (yv>2050) || (yv<1650))
  {
    Serial.println("ADXL tilt happen");
    digitalWrite(alarmPin, HIGH); 
    sms();            
  }
  else
  {
    digitalWrite(alarmPin, LOW);
  }
}

void fire()
{
  fv=digitalRead(fr);   
  if(fv==HIGH)
  {
    Serial.println("Fire detected");
    digitalWrite(alarmPin, HIGH);
    sms();
  }
  else
  {
    digitalWrite(alarmPin, LOW);    
  }
}

void piezo()
{
  pv=analogRead(pz);
  //Serial.println(pv);
  if(pv<100)
  {
    Serial.println("Pressure detected");
    digitalWrite(alarmPin, HIGH);
    sms();
  }
  else
  {
    digitalWrite(alarmPin, LOW);
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
  Serial.print("Accident Alert at ");
  Serial.print("http://www.google.com/maps/place/");
  delay(2000);
  Serial.print(latitude,6);
  Serial.print(",");
  Serial.println(longitude,6);      
  delay(2000);
  Serial.print(data);
  Serial.println((char)26);      //the stopping character
  delay(2000);
}
void sms_s()
{
  Serial.println("AT");    
  delay(1000);
  Serial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  Serial.println("AT+CMGS=\"+919997662478\"\r");  
  delay(1000);
  Serial.print("Accident is not Serious.");
  delay(2000);
  Serial.print(data);
  Serial.println((char)26);      //the stopping character
  delay(2000);
}

void encode_gps()
{
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (gps_port.available())
    {
      char a = gps_port.read();
//       Serial.write(a); // GPS encoded data
      if(gps.encode(a)) // if there is valid GPS data...
       {
         digitalWrite(ledPin, HIGH);
         getgps(gps); // grab the data 
       }
    }
  }
}

void getgps(TinyGPS &gps)
{
  gps.f_get_position(&latitude, &longitude);
  Serial.println(latitude);
  Serial.println(longitude);
  print_date(gps);
}

static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
  {
    
  }
  else
  {
    sprintf(data, "\nDate: %02d/%02d/%02d\nTime: %02d:%02d:%02d\n", day, month, year, hour, minute, second);
    Serial.print(data);
  }
}
