#include <SoftwareSerial.h>
#include <TinyGPS++.h>
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

SoftwareSerial ss(13, 12);

void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud);
  
  Serial.println("GPS example");
  Serial.println(TinyGPSPlus::libraryVersion());
}


static char sentence[80],c;  // NMEA sentence from external device
static int line= 0; // data available flag
static int i=0;
static long timer=0;

void loop() {
  readGPS();
//    if (ss.available()) {
//      while (ss.available() > 0) {
//      Serial.print(ss.read());
//      gps.encode(ss.read());
//      Serial.print("Sat: ");
//      Serial.print(gps.satellites.value());
//      Serial.print("\tLat: ");
//      Serial.print(gps.location.lat(), 6);
//      Serial.print("\tLon: ");
//      Serial.println(gps.location.lng(), 6);
//     delay(1000);
//    }
}

void readGPS(){
  int j;
  if (ss.available() > 0) {
    c=ss.read();
    sentence[i]=c; 
    ++i;
    if (c== 0x0d) line=1; 
  }
  if (i > 79) i=79;  // line too long
  if (line) {
//    for (j=0; j<i;++j) {
//      Serial.print(sentence[j]);
//    }
    Serial.println(sentence);
    gps.encode(*sentence);
//    Serial.print("Sat: ");
//    Serial.print(gps.satellites.value());
//    Serial.print("\tLat: ");
//    Serial.print(gps.location.lat(), 6);
//    Serial.print("\tLat: ");
//    Serial.println(gps.location.lat(), 6);
 
    displayInfo();

    line=i=0; // reset the sentence buffer
  }
}


void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
