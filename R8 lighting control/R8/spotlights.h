#include "Arduino.h"


/*
  DMX_Master.ino - Example code for using the Conceptinetics DMX library
  Copyright (c) 2013 W.A. van der Meeren <danny@illogic.nl>.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


//
// CTC-DRA-13-1 ISOLATED DMX-RDM SHIELD JUMPER INSTRUCTIONS
//
// If you are using the above mentioned shield you should
// place the RXEN jumper towards pin number 2, this allows the
// master controller to put to iso shield into transmit
// (DMX Master) mode
//
//
// The !EN Jumper should be either placed in the G (GROUND)
// position to enable the shield circuitry
//   OR
// if one of the pins is selected the selected pin should be
// set to OUTPUT mode and set to LOGIC LOW in order for the
// shield to work
//

//


#define MinBrightness 0    //value 0-255
#define MaxBrightness 255  //value 0-255
#define MAX_LEDS 1

class Lights
{
  public:
    int numberofPixels; // total pixels on strip
    int dataPinLight;  // which digi pin
    int pixelID; // pin id for turning on lights on certain strips
    int durationFade;;
    int currentValue[MAX_LEDS];  // stores the current brightness of the pixel
    int gotoValue[MAX_LEDS];  // stores the destination position of the pixel
    int durationFadeTime[MAX_LEDS];
    unsigned long LastFadeTime[MAX_LEDS];
    int pixelfadeSpeed; // the speed at which the fading occurs

    unsigned long LightstartTime;       // you set this to millis() when you want it to start, i.e. when the sensor triggers (just once though)

    //DECLARE THE STRIPS FOR THE HOUSE, FIREPLACE AND THE PARENTS BEDROOM
  

    //CONSTRUCTOR  list of variables you want to define outside the class in the main script
    Lights(int _numberofPixels, int _dataPinLight, int _pixelfadeSpeed) // call this function in the main script, this becomes an instance of the Lights constructor
    {
      numberofPixels = _numberofPixels;
      dataPinLight = _dataPinLight;
      pixelfadeSpeed = _pixelfadeSpeed;    
      for (uint16_t i = 0; i < numberofPixels; i++) // initialise the values of the pixels to 0
      {
        currentValue[i] = 0;
        gotoValue[i] = 0;
        durationFadeTime[i] = 0;
        LastFadeTime[i] = 0;
      }
    }

    void setup()
    {
      
    }

    void fadeUpStart(int pixelID, int durationFade)
    {
      //Serial.println("fade up begin");
      gotoValue[pixelID] = 255;  // the value the lights should go to when they fade up
      durationFadeTime[pixelID] = durationFade;
    }

    void fadeDownStart(int pixelID, int durationFade)
    {
      //Serial.println("fade down begin");
      gotoValue[pixelID] = 0;  // the value the lights should go to when they fade down
      durationFadeTime[pixelID] = durationFade;
    }

    // currentValue/fadeduration
    bool lightSequence()
    {
      /*for (uint16_t i = 0; i < numberofPixels; i++) {
        Serial.print(gotoValue[i]);
        Serial.print("/");
        Serial.print(currentValue[i]);
        Serial.print(" ");
      }
      Serial.println();*/
 
      for (uint16_t i = 0; i < numberofPixels; i++)
      {
        if (millis() - LastFadeTime[i] > durationFadeTime[i]) // durationofFadeTime is the interval at which I want each fadeup step to happen (in this case 1sec or whatever durationfadetime is set too)
        {

          if (currentValue[i] < gotoValue[i])
          {
            currentValue[i] += pixelfadeSpeed;
            if (currentValue[i] >= gotoValue[i] )
            {
              currentValue[i] = gotoValue[i];
            }
            //Serial.println("fade upper");
          }

          if (currentValue[i] > gotoValue[i])
          {
            currentValue[i] -= pixelfadeSpeed;

            if (currentValue[i] <= gotoValue[i])
            {
              currentValue[i] = gotoValue[i];
            }
            //Serial.println("fade downer");
          }

          //Serial.println(currentValue[i]);
         // analogWrite(dataPinLight,currentValue[i]);
          //dmx_master.setChannelValue ( dataPinLight, currentValue[i]);
          LastFadeTime[i] = millis();
        }
      }
      ///checker: check if the final gotovalue is reached then return true
      bool done = true;
      for (uint16_t i = 0; i < numberofPixels; i++)
      {
        if (currentValue[i] != gotoValue[i])
          done = false;
      }

      return done;
    }

    int getValue(int i) {
      return currentValue[i];
    }
};
