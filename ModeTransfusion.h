#include "FastLED.h" // подключаем библиотеку фастлед
#include "Mode.h"


class ModeTransfusion:public Mode {
  public:
    ModeTransfusion(CRGB *leds,int led_num):Mode(leds,led_num)
    {
      for (byte i =0;i<_led_num;i++){
          _leds[i].setRGB(255,0,0); 
      }
      change_color(255,0,0);
    }

    void next(){
      count_frame++;
      int r = _leds[0].red;
      int g = _leds[0].green;
      int b = _leds[0].blue;
      change_color(r,g,b);
      switch (this_color) {
        case 0:
          if (g+step>255){
            g ++;
          }
          else{
           g+=step; 
          }
          break;
        case 1:
          if (r-step<0){
            r--;
          }
          else{
           r-=step; 
          }
          break;
        case 2:
          if (b+step>255){
            b ++;
          }
          else{
           b+=step; 
          }
          break;
        case 3:
          if (g-step<0){
            g--;
          }
          else{
           g-=step; 
          }
          break;
        case 4:
          if (r+step>255){
            r ++;
          }
          else{
           r+=step; 
          }
          break;
        case 5:
          if (b-step<0){
            b--;
          }
          else{
           b-=step; 
          }
          break;
      }

      // Serial.print(r);
      // Serial.print(" ");
      // Serial.print(g);
      // Serial.print(" ");
      // Serial.println(b);
      

      for (byte i =0;i<_led_num;i++){
          _leds[i].setRGB(r,g,b); 
      }
     
      FastLED.setBrightness(_bright*(abs(sin(count_frame/250.0))+0.0)/1.0);
    }
    
    void change_color(int r,int g,int b){
      if (r == 255 && g == 0 && b == 0){
        this_color = 0;
      }
      else if (r == 255 && g == 255 && b == 0){
        this_color = 1;
      }
      else if (r == 0 && g == 255 && b == 0){
        this_color = 2;
      }
      else if (r == 0 && g == 255 && b == 255){
        this_color = 3;
      }
      else if (r == 0 && g == 0 && b == 255){
        this_color = 4;
      }
      else if (r == 255 && g == 0 && b == 255){
        this_color = 5;
      }
    
    }

  private:
    int step =1;
    byte this_color;
    long count_frame = 0;
};
