#include "dht.h"
#define dht_apin A0

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif


// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

uint8_t errorCode = 0;

/*
Teensy3.x and Arduino's
You are using 4 wire SPI here, so:
 MOSI:  11//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 MISO:  12//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 SCK:   13//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 the rest of pin below:
 */
#define __CS 10
#define __DC 6
/*
Teensy 3.x can use: 2,6,9,10,15,20,21,22,23
Arduino's 8 bit: any
DUE: check arduino site
If you do not use reset, tie it to +3V3
*/

dht DHT;
TFT_ILI9163C display = TFT_ILI9163C(10, 8, 9);

void setup ()
{
  display.begin ();
  display.setBitrate (24000000);
  display.setRotation (2);
  display.clearScreen ();
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 
}//end "setup()"


void loop() {
  DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");

    display.fillScreen ();
    display.setCursor (0, 0);
    display.setTextColor (GREEN); 
    display.setTextSize (1);
    display.print ("Демонстрація датчика DHT");

 // Відображення температури в C
 display.setCursor (2, 22);
 display.print("Temperature-");
 display.print (DHT.temperature);
 display.setTextSize (2);
 display.print ("C");

 display.setCursor (2, 62);
 display.print("H-");
 display.print (DHT.humidity);
 display.setTextSize (1);
 display.print ("%");
 delay(5000);
 }
