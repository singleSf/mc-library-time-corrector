using namespace std;

#ifndef TIME_CORRECTOR_INIT
#define TIME_CORRECTOR_INIT true

#include "TIME_CORRECTOR.h"

TIME_CORRECTOR::TIME_CORRECTOR(HardwareSerial *_stream) {
  this->__streamCorrector = _stream;
}
TIME_CORRECTOR::~TIME_CORRECTOR() {}

bool TIME_CORRECTOR::begin() {
  RTC_DS1307::begin();

  return this->isrunning();
}

void TIME_CORRECTOR::correct() {
  if (this->__streamCorrector->available()) {
    String string = "";
    while (this->__streamCorrector->available()) {
      string += (char)this->__streamCorrector->read();
      delay(5);
    }
    string.trim();

    byte countTime       = 6;
    byte time[countTime] = {};
    byte timeCursor      = 0;
    byte step            = 2;

    for(byte i = 0; i < countTime; i++){
      time[i] = (byte)-1; // overflow
    }

    for (byte i = 0; i < countTime * 2; i += step) {
      String separator = string.substring(step, step + 1);
      if (this->_SEPARATORS.indexOf(separator) == -1) {
        break;
      }
      time[timeCursor++] = string.substring(0, step).toInt();

      string = string.substring(step + 1);
      if(!string.length()){
        break;
      }
    }
    
    Serial.println(time[0]);
    Serial.println(time[1]);
    Serial.println(time[2]);
    Serial.println(time[3]);
    Serial.println(time[4]);
    Serial.println(time[5]);

    if (
         time[0] >= 0 && time[0] <= 50
      && time[1] >  0 && time[1] <= 12
      && time[2] >  0 && time[2] <= 31
      && time[3] >= 0 && time[3] <= 23
      && time[4] >= 0 && time[4] <= 59
      && time[5] >= 0 && time[5] <= 59
    ) {
      this->adjust(DateTime(time[0], time[1], time[2], time[3], time[4], time[5]));

      this->__streamCorrector->println("DateTime update!");
    }
  }
}


void TIME_CORRECTOR::printCurrent() {
  DateTime now  = this->now();
  String   date = "";

  date += now.year();
  date += '-';
  date += this->_addZero(now.month());
  date += '-';
  date += this->_addZero(now.day());
  date += ' ';
  date += this->_addZero(now.hour());
  date += ':';
  date += this->_addZero(now.minute());
  date += ':';
  date += this->_addZero(now.second());
  date += " (";
  date += now.dayOfTheWeek();
  date += ')';

  this->__streamCorrector->println(date);
}

String TIME_CORRECTOR::_addZero(byte _n) {
  String n = String(_n);
  if (_n < 10) {
    n = "0" + n;
  }

  return n;
}

#endif