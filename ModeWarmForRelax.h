#include "FastLED.h" // подключаем библиотеку фастлед
#include "Mode.h"


class ModeWarmForRelax:public Mode {
  public:
    ModeWarmForRelax(CRGB *leds,int led_num):Mode(leds,led_num)
    {
  
    }

    void next(){
      for (byte i =0;i<_led_num;i++){
          _leds[i].setRGB(139,69,19);
      }
      FastLED.setBrightness(_bright);
    }
};
