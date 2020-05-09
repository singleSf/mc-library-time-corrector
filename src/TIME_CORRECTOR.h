using namespace std;

#ifndef TIME_CORRECTOR_INIT_H
#define TIME_CORRECTOR_INIT_H true

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>


class TIME_CORRECTOR : public RTC_DS1307 {
  private:
    const String _SEPARATORS = "-/:_ ";

    HardwareSerial *__streamCorrector;

    String _addZero(byte);

  public:
    TIME_CORRECTOR(HardwareSerial *);
    TIME_CORRECTOR::~TIME_CORRECTOR();

    void correct();
    bool begin();
    void printCurrent();

};

#endif