#include "FastLED.h" // подключаем библиотеку фастлед
#include "Mode.h"


class ModeWork:public Mode {
  public:
    ModeWork(CRGB *leds,int led_num):Mode(leds,led_num)
    {
  
    }

    void next(){
    
      for (byte i =0;i<_led_num;i++){
          _leds[i].setRGB(210,140,70);
      }
      FastLED.setBrightness(_bright);
    }
};
