using namespace std;

// 23:01:00:11:12:19

#include "time-corrector.h"

TIME_CORRECTOR *TIME = new TIME_CORRECTOR(&Serial);

void setup() {
  Serial.begin(9600);
  TIME->begin();

// хранит данные при наличии основного питания или от батареи
    //TIME->writeByteInRam(10, 150);
}

void loop() {
  TIME->correct();

  DateTime now = TIME->now();

  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(' ');
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(now.dayOfWeek(), DEC);
  Serial.print(')');
  Serial.println();

  //Serial.println(TIME->readByteInRam(10));

  delay(1000);
}
