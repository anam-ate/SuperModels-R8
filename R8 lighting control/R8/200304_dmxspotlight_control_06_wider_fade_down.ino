#include <Conceptinetics.h>
#include "spotlights.h"


  
//#define DATA light  26

// The master will control 100 Channels (1-100)
//
// depending on the ammount of memory you have free you can choose
// to enlarge or schrink the ammount of channels (minimum is 1)
//
#define DMX_MASTER_CHANNELS   100

//
// Pin number to change read or write mode on the shield
//
#define RXEN_PIN                2


// Configure a DMX master controller, the master controller
// will use the RXEN_PIN to control its write operation
// on the bus
DMX_Master        dmx_master ( DMX_MASTER_CHANNELS, RXEN_PIN );

int state = 1;
long timer = 0;         // use this to store times for timers
bool timerDone = false;
int internalSequenceState = 0;

//Lights(int _numberofPixels, int _dataPinLight, int _pixelfadeSpeed)
Lights spotlight01(1, 13, 1);
Lights spotlight02(1, 14, 1);
Lights spotlight03(1, 15, 1);
Lights spotlight04(1, 16, 1);
Lights spotlight05(1, 17, 1);
Lights spotlight06(1, 18, 1);
Lights spotlight07(1, 19, 1);
Lights spotlight08(1, 20, 1);


// the setup routine runs once when you press reset:
void setup() {

  // Enable DMX master interface and start transmitting
  dmx_master.enable ();

  //Serial.begin(19200);
  spotlight01.setup();
  spotlight02.setup();
  spotlight03.setup();
  spotlight04.setup();
  spotlight05.setup();
  spotlight06.setup();
  spotlight07.setup();
  spotlight08.setup();

  //Serial.begin(9600);

}

// the loop routine runs over and over again forever:
void loop()
{

          
    dmx_master.setChannelValue (13, spotlight01.getValue(0));
    dmx_master.setChannelValue (14, spotlight02.getValue(0));
    dmx_master.setChannelValue (15, spotlight03.getValue(0));
    dmx_master.setChannelValue (16, spotlight04.getValue(0));
    dmx_master.setChannelValue (17, spotlight05.getValue(0));
    dmx_master.setChannelValue (18, spotlight06.getValue(0));
    dmx_master.setChannelValue (19, spotlight07.getValue(0));
    dmx_master.setChannelValue (20, spotlight08.getValue(0));

  // put your main code here, to run repeatedly:
  // FADE UP LIGHTS
  if (state == 1 && millis() >= timer + 1 * 1000)
  {
    if ( millis() >= timer + 1 * 1000)
    {
      spotlight01.fadeUpStart(0, 10);
      //Serial.println("start fade up spot 1");
    }
 
    if ( millis() >= timer + 3 * 1000)
    {
      //Serial.println("now start light 2");
      spotlight02.fadeUpStart(0, 10);
      spotlight01.fadeDownStart(0, 7);
    }

    if ( millis() >= timer + 5 * 1000)
    {
      //Serial.println("now start light 3");
      spotlight03.fadeUpStart(0, 10);
      spotlight02.fadeDownStart(0, 7);
    }
    if ( millis() >= timer + 7 * 1000)
    {
      //Serial.println("now start light 4");
      spotlight04.fadeUpStart(0, 10);
      spotlight03.fadeDownStart(0, 7);
    }
    if ( millis() >= timer + 9 * 1000)
    {
      //Serial.println("now start light 5");
      spotlight05.fadeUpStart(0, 10);
      spotlight04.fadeDownStart(0, 7);
    }
    if ( millis() >= timer + 11 * 1000)
    {
      //Serial.println("now start light 6");
      spotlight06.fadeUpStart(0, 10);
      spotlight05.fadeDownStart(0, 7);
    }
    if ( millis() >= timer + 13 * 1000)
    {
      //Serial.println("now start light 7");
      spotlight07.fadeUpStart(0, 10);
      spotlight06.fadeDownStart(0, 7);
    }
    if ( millis() >= timer + 15 * 1000)
    {
      //Serial.println("now start light 8");
      spotlight08.fadeUpStart(0, 10);
      spotlight07.fadeDownStart(0, 7);
    }
    if ( millis() >= timer + 17 * 1000)
    {
     
      spotlight08.fadeDownStart(0, 7);
    }

    bool spotlight01Done = spotlight01.lightSequence();
    bool spotlight02Done = spotlight02.lightSequence();
    bool spotlight03Done = spotlight03.lightSequence();
    bool spotlight04Done = spotlight04.lightSequence();
    bool spotlight05Done = spotlight05.lightSequence();
    bool spotlight06Done = spotlight06.lightSequence();
    bool spotlight07Done = spotlight07.lightSequence();
    bool spotlight08Done = spotlight08.lightSequence();

    

    if (spotlight01Done == true && spotlight02Done == true && spotlight03Done == true && spotlight04Done == true && spotlight05Done == true && spotlight06Done == true && spotlight07Done == true && spotlight08Done == true)
    {
      state = 1;
      timer = millis();
      //Serial.println("start fade up light sequence state = 2");
    }

  }
}
