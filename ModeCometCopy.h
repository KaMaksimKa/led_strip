#include "FastLED.h" // подключаем библиотеку фастлед
#include "Mode.h"


class ModeComet:public Mode {
  public:
    ModeComet(CRGB *leds,int led_num,int speed):Mode(leds,led_num)
    {
      matrix = new int [_led_num];
      for (int i = 0;i<_led_num;i++){
          matrix[i] = -1;
        }
      time_last_frame = millis();

      max_speed = speed;
      size_block_of_speed = led_num%speed == 0?led_num/speed:led_num/speed +1;

    }

    ~ModeComet()
    {
      delete[] matrix;
    }


    void next(){

      if (millis() - time_last_frame > period){
        
        // for (int i = _led_num-2;i>=0;i--){
        //   matrix[i+1] = matrix[i];
        //   matrix[i] = -1;
        // }
        
        for (int i = 0;i<_led_num;i++){
          if (matrix[i]!=-1){
            matrix[i] +=i/size_block_of_speed+1;
          }
        }

        for (int i = _led_num-1;i>=0;i--){
          if (matrix[i]>=max_speed){
            matrix[i] = -1;
            matrix[i+1] = 0;

            byte r = _leds[i].red;
            byte g = _leds[i].green;
            byte b = _leds[i].blue;
            _leds[i+1].setRGB(r,g,b);
            _leds[i].setRGB(0,0,0);
          }
        }


        int n = random(10);
        int m = random(10);
        // Serial.println(n);
        if (n==m){
          matrix[0] = 0;
          _leds[0].setRGB(random(256),random(256),random(256));
        }

        // for (int i = 0;i<_led_num;i++){
        //   if (matrix[i] != -1){
        //     _leds[i].setRGB(255,255,255);
        //   }
        //   else{
        //     _leds[i].setRGB(0,0,0);
        //   }
        // }

        time_last_frame = millis();
      }

      
      FastLED.setBrightness(_bright);
    }

  private:
    int *matrix;
    byte size_block_of_speed = 40;
    byte max_speed = 5;
    long time_last_frame;
    long period = 1;
    long count_frame = 0;
};
