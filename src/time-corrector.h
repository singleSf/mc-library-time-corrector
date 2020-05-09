using namespace std;

#ifndef TIME_CORRECTOR_INIT_H
#define TIME_CORRECTOR_INIT_H true

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>


class TIME_CORRECTOR : public RTC_DS1307 {
  private:
    HardwareSerial *__streamCorrector;
    
    static const char _CORRECT_SEPARATOR = ':';

  public:
    TIME_CORRECTOR(HardwareSerial *);
    TIME_CORRECTOR::~TIME_CORRECTOR();

    void correct();
    void begin();


};

#endif;

