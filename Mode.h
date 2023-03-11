#pragma once

//Base class for other mods
class Mode {
  public:
    Mode(CRGB *leds,int led_num){
      _leds = leds;
      _led_num = led_num;
    }

    virtual ~Mode()
    {
      
    }

    virtual void next(){
    }


  protected:
    CRGB *_leds;
    int _led_num;
    byte _bright = 0;
  public:
    void set_bright(byte bright){
      _bright = bright;
    }
};
