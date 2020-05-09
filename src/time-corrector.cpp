using namespace std;

#ifndef TIME_CORRECTOR_INIT
#define TIME_CORRECTOR_INIT true

#include "time-corrector.h"

TIME_CORRECTOR::TIME_CORRECTOR(HardwareSerial *_stream) {
  this->__streamCorrector = _stream;
}
TIME_CORRECTOR::~TIME_CORRECTOR() {}

void TIME_CORRECTOR::begin() {
  Wire.begin();
  RTC_DS1307::begin();
}

void TIME_CORRECTOR::correct() {
  if (this->__streamCorrector->available()) {
    delay(5);
    String string = "";

    while (this->__streamCorrector->available()) {
      string += (char)this->__streamCorrector->read();
    }

    string.trim();

    string += this->_CORRECT_SEPARATOR;

    const byte countTime = 6;
    byte time[countTime];
    for (byte i = 0; i < countTime; i++) {
      int position = string.indexOf(this->_CORRECT_SEPARATOR);

      if (position == -1) {
        return;
      } else {
        time[i] = string.substring(0, position).toInt();
        string = string.substring(position + 1, string.length());
      }
    }

    DateTime t;
    t.setHour(time[0]);
    t.setMinute(time[1]);
    t.setSecond(time[2]);
    t.setYear(2000 + time[5]);
    t.setMonth(time[4]);
    t.setDay(time[3]);    

    this->adjust(t);
    

    DateTime now = this->now();
    String date = "Ok! ";

    date += now.hour();
    date += ':';
    date += now.minute();
    date += ':';
    date += now.second();
    date += ' ';
    date += now.day();
    date += '/';
    date += now.month();
    date += '/';
    date += now.year() - 2000;
    this->__streamCorrector->println(date);
  }
}


#endif;
