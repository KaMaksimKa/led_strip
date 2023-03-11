#include "FastLED.h" // подключаем библиотеку фастлед
#include "Mode.h"


class ModeConfetti:public Mode {
  public:
    ModeConfetti(CRGB *leds,int led_num):Mode(leds,led_num)
    {
  
    }
    void next(){
      fadeToBlackBy(_leds, _led_num, 2);
      int pos = random16(_led_num);
      _leds[pos] += CHSV(baza++ + random8(64), 200, 255);
      FastLED.setBrightness(_bright);
    }
  private:
    byte baza = 0; 
};
