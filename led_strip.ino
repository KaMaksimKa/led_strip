#include "FastLED.h" // подключаем библиотеку фастлед
#include <Arduino.h>
#include <EncButton.h>


#include "ModeWork.h"
#include "ModeConfetti.h"
#include "ModeWarmForRelax.h"
#include "ModeTransfusion.h"
#include "ModeConfettiComet.h"
#include "ModeComet.h"
#include "ModeFill.h"
#include "ModeFire.h"

#define MAX_BRIGHT 255
#define MIN_BRIGHT 15

#define POTENT_PIN 2
#define LED_NUM 170
#define LED_PIN 2
#define BUTTON_BACK_PIN 6
#define BUTTON_FORWARD_PIN 7

byte bright =10;

const int minNumberMode = 1;
const int maxNumberMode = 7;
int numberMode = minNumberMode;

EncButton<EB_CALLBACK,BUTTON_FORWARD_PIN > btn_forward;   
EncButton<EB_CALLBACK,BUTTON_BACK_PIN > btn_back; 

Mode *mode;

CRGB leds[256];



void setup() {
  
  Serial.begin(9600);

  btn_forward.setButtonLevel(HIGH);
  btn_forward.attach(RELEASE_HANDLER, handle_forward_btn);  
  
  btn_back.setButtonLevel(HIGH);
  btn_back.attach(RELEASE_HANDLER, handle_back_btn);  

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(bright);
  Serial.println("setup");
  change_mode(numberMode);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
}



void loop() {
  setBrightByPotent();
  btn_back.tick(); 
  btn_forward.tick();
  
  mode -> next();

  FastLED.show();

}


void handle_forward_btn(){
  Serial.println("forward");
  numberMode++;
  if (numberMode > maxNumberMode){
    numberMode = minNumberMode;
  }
  change_mode(numberMode);
}

void handle_back_btn(){
  Serial.println("back");
  numberMode--;
  if (numberMode < minNumberMode){
    numberMode = maxNumberMode;
  }
  change_mode(numberMode);
}

void setBrightByPotent(){
  int bright_potent = analogRead(POTENT_PIN);
  bright_potent = map(bright_potent, 0, 1023, MIN_BRIGHT, MAX_BRIGHT);
  bright_potent = constrain(bright_potent, MIN_BRIGHT, MAX_BRIGHT);
  
  bright = bright_potent;
  mode->set_bright(bright);
  
}

void change_mode(byte number){
  Serial.println(number);
  delete mode; 
  FastLED.clear();
  switch (number) {
    case 1:
      mode = new ModeWork(leds,LED_NUM);
      break;
    case 2:
      mode = new ModeWarmForRelax(leds,LED_NUM);
      break;
    case 3:
      mode = new ModeConfetti(leds,LED_NUM);
      break;
    case 4:
      mode = new ModeTransfusion(leds,LED_NUM);
      break;
    case 5:
      mode = new ModeConfettiComet(leds,LED_NUM,5,4);
      break;
    case 6:
      mode = new ModeComet(leds,LED_NUM);
      break;
    case 7:
      mode = new ModeFill(leds,LED_NUM);
      break;
  }
}
