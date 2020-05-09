using namespace std;

// 23:01:00:11:12:19

#include <TIME_CORRECTOR.h>

TIME_CORRECTOR *TIME = new TIME_CORRECTOR(&Serial);

// хранит данные при наличии основного питания или от батареи
const byte ramAddress = 10;
const byte ramValue   = 150;

void setup() {
  Serial.begin(9600);
  TIME->begin();

  //TIME->writenvram(ramAddress, ramValue);
}

void loop() {
  // Y-m-d H:i:s
  // 20-05-09 21:30:24
  TIME->correct();

  TIME->printCurrent();

  //Serial.println(TIME->readnvram(ramAddress));

  delay(1000);
}
