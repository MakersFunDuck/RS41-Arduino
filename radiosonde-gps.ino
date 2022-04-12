#include <TinyGPSPlus.h>
HardwareSerial Serial1(USART1); // PB11 (RX)  PB10   (TX)
HardwareSerial Serial3(USART3); // PB11 (RX)  PB10   (TX)
/*
 * Maker's Fun Duck
   This sample sketch demonstrates the normal use of a RS41 radiosonde GPS.
   To upload it, connect the radiosonde frontend connections to a ST link as:
   
   gnd to gnd
   vcc to 3.3 V
   swclk to swclk
   swdio to swdio

   To read out the serial data from serial console connect it with a serial ttl module as:
   rx to tx
   tx to rx

   This code uses TinyGPSPlus arduino library. You can install this from the library manager
*/

static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;



void setup()
{
  Serial3.begin(9600);
  Serial1.begin(GPSBaud);

  Serial3.println(F("radiosonde-gps.ino"));
  Serial3.println(F("A simple demonstration of GPS with an  RS41 radiosonde"));
  Serial3.print(F("TinyGPSPlus library v. ")); Serial3.println(TinyGPSPlus::libraryVersion());
  Serial3.println(F("Maker's Fun Duck"));
  Serial3.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial1.available() > 0)
    if (gps.encode(Serial1.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial3.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial3.print(F("Location: ")); 
  if (gps.location.isValid())
  {
     Serial3.print(gps.location.lat(), 6);
     Serial3.print(F(","));
     Serial3.print(gps.location.lng(), 6);
  }
  else
  {
     Serial3.print(F("INVALID"));
  }

   Serial3.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
     Serial3.print(gps.date.month());
     Serial3.print(F("/"));
     Serial3.print(gps.date.day());
     Serial3.print(F("/"));
     Serial3.print(gps.date.year());
  }
  else
  {
     Serial3.print(F("INVALID"));
  }

   Serial3.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10)  Serial3.print(F("0"));
     Serial3.print(gps.time.hour());
     Serial3.print(F(":"));
    if (gps.time.minute() < 10)  Serial3.print(F("0"));
     Serial3.print(gps.time.minute());
     Serial3.print(F(":"));
    if (gps.time.second() < 10)  Serial3.print(F("0"));
     Serial3.print(gps.time.second());
     Serial3.print(F("."));
    if (gps.time.centisecond() < 10)  Serial3.print(F("0"));
     Serial3.print(gps.time.centisecond());
  }
  else
  {
     Serial3.print(F("INVALID"));
  }

  Serial3.println();
}
