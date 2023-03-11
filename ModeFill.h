#include "FastLED.h" // подключаем библиотеку фастлед
#include "Mode.h"


class ModeFill:public Mode {
  public:
    ModeFill(CRGB *leds,int led_num):Mode(leds,led_num)
    {
  
    }
 
    void next(){

      

      if (millis() - time1 > T){
        Serial.println(i);
        if ((i >=_led_num-1)||(i <=0))
        {
          k = (k+1)%2;   
        }
        if (k == 0){
          i--;
        }
        else if (k == 1){
          i++;
        }
        _leds[i] = CHSV(baza++, 255, 255);
        time1 = millis();
      }
      
     
      FastLED.setBrightness(_bright);
    }
 private:
    long time1 =0;  
    long T =20;  
    int i = 0; 
    int k = 0;
    byte baza;
};
