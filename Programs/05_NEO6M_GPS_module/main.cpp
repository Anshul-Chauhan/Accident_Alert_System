#include <Arduino.h>

#include <TinyGPS.h>
#include<SoftwareSerial.h>
TinyGPS gps;
SoftwareSerial gps_port(16,17); // Rx2 Tx2
float latitude, longitude;
char data[32];
int ledPin = 2;

void encode_gps();
void getgps(TinyGPS &gps);
static void print_date(TinyGPS &gps);

void setup()
{
 pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, LOW);
 Serial.begin(9600);
 gps_port.begin(9600);
 delay(1000);
}

void loop()
{
  encode_gps();
  delay(1000);
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
