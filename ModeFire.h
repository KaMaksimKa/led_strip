#include "FastLED.h" // подключаем библиотеку фастлед
#include "Mode.h"


class ModeFire:public Mode {
  public:
    ModeFire(CRGB *leds,int led_num):Mode(leds,led_num)
    {
      f = random(0,_led_num);
    }
 
    void next(){
      if (millis()-last_time>t){
        n = random(0,_led_num);
        last_time = millis();
      }
      if (millis()-last_Time>T){
        last_Time = millis();
        f = round(f+(n -f)*k);
        Serial.println(f);
        Serial.println(n);
        for (int i =0; i<_led_num; i++){
          if (i<f){
            _leds[i].setRGB(255,0,0);
          }
          else{
            _leds[i].setRGB(0,255,0);
          }
        }
      }
    }

 private:
    float k = 0.01;
    int n;
    int f;
    int t = 500;
    int T = 100;
    long last_time; 
    long last_Time; 


};
