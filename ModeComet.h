#include "FastLED.h" // подключаем библиотеку фастлед
#include "Mode.h"


class ModeComet:public Mode {
  public:
    ModeComet(CRGB *leds,int led_num):Mode(leds,led_num)
    {
      matrix = new int [_led_num];
      for (int i = 0;i<_led_num;i++){
          matrix[i] = -1;
        }
      time_last_frame = millis();

      max_len_comet = 7;
      min_len_comet = 4;
      
      
      

      period = 6;
      max_speed = 4;
      size_block_of_speed = led_num%max_speed == 0?led_num/max_speed:led_num/max_speed +1;

    }

    ~ModeComet()
    {
      delete[] matrix;
    }


    void next(){

      if (millis() - time_last_frame > period){
      
        
        for (int i = 0;i<_led_num;i++){
          if (matrix[i]!=-1){
            matrix[i] +=i/size_block_of_speed+1;
          }
        }

        for (int i = _led_num-1;i>=0;i--){
          if (matrix[i]>=max_speed){
            while (matrix[i]!=-1){
              matrix[i] = -1;
              matrix[i+1] = 0;

              byte r = _leds[i].red;
              byte g = _leds[i].green;
              byte b = _leds[i].blue;
              _leds[i+1].setRGB(r,g,b);
              _leds[i].setRGB(0,0,0);
              if (i>0){
                i--;
              }
              
            }
            
          }
        }


        
        if (remains_current_comet == 0 && matrix[0] == -1 && matrix[1] == -1 && matrix[2] == -1){
          int n = random(5)+ random(5);
          int m = random(5)+ random(5);
          if (n==m){
            
            len_current_comet= random(min_len_comet,max_len_comet);
            
            
            baza +=5;
            color = baza + random8(64);
            saturation = 200;
            brightness = 150;

            matrix[0] = 0;
            _leds[0] += CHSV(color,saturation ,255 );
            
            remains_current_comet = len_current_comet-1;
          }
        }
        else if(remains_current_comet>0 && matrix[0] == -1){
          matrix[0] = 0;
          
          _leds[0] += CHSV(color,saturation ,brightness/len_current_comet*remains_current_comet);
          remains_current_comet--;
        }
        


        time_last_frame = millis();
      }

      
      FastLED.setBrightness(_bright);
    }

  private:
    int *matrix;
    int remains_current_comet = 0;
    byte len_current_comet = 0;
    byte max_len_comet;
    byte min_len_comet;
    byte baza = 0;
    byte size_block_of_speed;
    byte max_speed;
    long time_last_frame;
    long period;
    long count_frame = 0;

    byte color;
    byte saturation;
    byte brightness;
};
