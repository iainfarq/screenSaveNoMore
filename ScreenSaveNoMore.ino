//
// Stupendously simple code to pretend to be a keyboard, and press the SHift key every 5 minutes
// to stop the screen saver kicking in.
// We use the dotStar LED to warn the user that a keypress is coming - set by the LOOMING parameter.
//
// igf 22 mar 2020
//
#include <Keyboard.h>
#include <Adafruit_DotStar.h>

#define PERIOD   300               // seconds
#define LOOMING  2                 // time just before key press
#define KEY      KEY_LEFT_SHIFT    // actual key we're 'pressing'

Adafruit_DotStar loomingLED(1,7,8);

void setup() 
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);  // turn off status led
  loomingLED.begin();
  
  Keyboard.begin();  
}

void looming(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
  loomingLED.setPixelColor(0, r, g, b);
  loomingLED.setBrightness(brightness);
  loomingLED.show();
}

void loomingOff()
{
  loomingLED.clear();
  loomingLED.show();
}

void loop() 
{
  // looming LED = red!
  looming(0,255,0,255);
  
  Keyboard.press(KEY);
  Keyboard.releaseAll();

  delay(100);  
  
  loomingOff();
  delay((PERIOD-LOOMING) * 1000);
  
  // looming = amber
  looming(255,255,0,32);
  delay(LOOMING * 1000);
}
