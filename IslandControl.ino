//Include IRRemote header file
#include <IRremote.h>

//Include header file contatining all the ir codes that the system should respond to
#include "codes.h"

//Timer functions
#include "TimerOne.h"

//LED stuff
//Include FastLED header
#include <FastLED.h>

//Constants
#define LED_PIN     3
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    3
#define TASK_TIME 500000 //0.5s

//Variables
// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

//Brightness of led strip for palete
int bright = 128;

//The currently selected led, if 5 then all are selected
int sel = 0;

//Values for rgb colours
int red[NUM_LEDS] = {0};
int green[NUM_LEDS] = {0};
int blue[NUM_LEDS] = {0};

//Used for timing for the auto modes
volatile unsigned int counter = 0;

//Used to enable, disable auto modes
volatile bool jump3 = 0;
volatile bool jump7 = 0;
volatile bool fade3 = 0;
volatile bool fade7 = 0;

//Speed control
volatile unsigned int runSpeed = 1;

//Pos
volatile int seqPosition = 0;

//Create a palette of colours used for fading
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

//IR stuff
//Define the pin which the reciever is connected to
#define IR_PIN 2 

//Setup a reciever object on this pin
IRrecv irrecv(IR_PIN);

//Define a place to hold the ir code recieved
decode_results results;

//Function prototypes

//Perform requested action
void doAction(int action);

//Event queue task handler
void processTasks();

//LED functions
void changeColour(int red, int green, int blue, int led);

void showChanges(int led);

void mixColour(bool r, bool g, bool b, bool maxBright, bool minBright, signed int val, int led);

//What code has been pressed
int findAction (decode_results *results);

//Setup
void setup()
{
  //Init the serial connection
  Serial.begin(9600);

  //Setup LEDs
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  //Set initial brightness to 128
  FastLED.setBrightness(128);
  
  // Start the receiver
  irrecv.enableIRIn(); 

  //Indicator LED
  pinMode(13, OUTPUT);

  //Init timer system
  Timer1.initialize();
  //Run function every 3s
  Timer1.attachInterrupt(processTasks, TASK_TIME);

  //Setup colour paletes for later use
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  //Display fade animation on startup
  doFade();
  fade7 = 1;
}

//Loop
void loop() {
  //If a code is recieved, do something about it, all signals recieved while processing will be ignored
  if (irrecv.decode(&results)) {
    
    //Print value recieved, in hex form
    Serial.print("Code recieved is ");
    Serial.println(results.value, HEX);
    
    Serial.print("Current counter value is ");
    Serial.println(counter);

    //Let action determine what needs to be done
    int res = findAction(&results);
    if (res != 44)
    {
      Serial.print("Performing action ");
      Serial.println(res);
      Serial.print("Current selected led is ");
      Serial.println(sel);
      ACTION39;
      doAction(res);
    }
    else
    {
      Serial.println("Unrecognised code!"); 
    }
    
    //Reset the value of results
    results.value = 0x00000000;
    
    //Resume listening for incoming signals
    irrecv.resume();
    
    //Show the results of the change
    showChanges();
  }
}

//LED functions
void resetAuto()
{
    jump3 = 0;
    jump7 = 0;
    fade3 = 0;
    fade7 = 0;
    seqPosition = 0;
    sel = 0;    
}

//Predefined routines

//Jump3
void doJump3()
{
    switch(seqPosition)
    {
        Serial.print("jump3 - Selected LED is ");
        Serial.println(sel);
        //Start by settting all to red
        case 0:
            changeColour(255, 0, 0, sel);
            //Increment position variable
            seqPosition++;
            break;
            
        //Then change to green
        case 1:
            changeColour(0, 255, 0, sel);
            //Increment position variable
            seqPosition++;
            break;

        //Then to blue
        case 2:
            changeColour(0, 0, 255, sel);
            seqPosition = 0;
            break;
            
        //If none of the above, reset position variable and set back to red
        default: 
            seqPosition = 0;
            changeColour(255, 0, 0, sel);
            break;      
    }
    //Update the LEDs
    showChanges();
}

//Jump7
void doJump7()
{
    switch(seqPosition)
    {
        Serial.print("jump7 - Selected LED is ");
        Serial.println(sel);
        //Start by settting all to red
        case 0:
            changeColour(255, 0, 0, sel);
            //Increment position variable
            seqPosition++;
            break;
        
        //Then change to yellow
        case 1:
            changeColour(255, 215, 0, sel);
            //Increment position variable
            seqPosition++;
            break;
            
        //Then change to green
        case 2:
            changeColour(0, 255, 0, sel);
            //Increment position variable
            seqPosition++;
            break;

        //Then to cyan
        case 3:
            changeColour(0, 191, 255, sel);
            seqPosition++;
            break;
            
        //Then to blue
        case 4:
            changeColour(0, 0, 255, sel);
            seqPosition++;
            break;

        //Then to magenta
        case 5:
            changeColour(255, 105, 180, sel);
            seqPosition++;
            break;

        //Finally to white
        case 6:
            changeColour(255, 255, 255, sel);
            seqPosition = 0;
            break;
            
        //If none of the above, reset position variable and set back to red
        default: 
            seqPosition = 0;
            changeColour(255, 0, 0, sel);
            break;      
    }
    //Update the LEDs
    showChanges();
}

//Fade
void doFade()
{
  Serial.println("Fading");
    seqPosition = seqPosition + 5; /* motion speed */
    FillLEDsFromPaletteColors(seqPosition, bright);
    FastLED.show();
    
}

//Fade functions

void FillLEDsFromPaletteColors( uint8_t colorIndex, uint8_t brightness)
{    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


void changeColour(int r, int g, int b, int led)
{
    //Workaround to prevent sel getting reset
    int x = sel;
    if (led == 5)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            //Update global variables
            red[i] = r;
            green[i] = g;
            blue[i] = b;
        }
    }
    else
    {
        //Update global variables
        red[led] = r;
        green[led] = g;
        blue[led] = b;
    }
    sel = x;
}

void mixColour(bool r, bool g, bool b, bool maxBright, bool minBright, signed int val, int led)
{
    //Workaround to prevent sel getting reset
    int x = sel;
    if (led == 5)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            if (r)
            {
                red[i] = red[i] + val;
            }
            if (g)
            {
                green[i] = green[i] + val;
            }
            
            if (b)
            {
               blue[i] = blue[i] + val;
            }
            
            if (minBright)
            {
                leds[i].fadeLightBy( 64 );
                red[i] = leds[i].red;
                green[i] = leds[i].green;
                blue[i] = leds[i].blue; 
            }
            
            if (maxBright)
            {
                leds[i].maximizeBrightness();
                red[i] = leds[i].red;
                green[i] = leds[i].green;
                blue[i] = leds[i].blue;
            }  
        }
    }
    else
    {
        if (r)
        {
            red[led] = red[led] + val;
        }
        if (g)
        {
            green[led] = green[led] + val;
        }
        
        if (b)
        {
           blue[led] = blue[led] + val;
        }

        if (minBright)
        {
            leds[led].fadeLightBy( 64 );
            red[led] = leds[led].red;
            green[led] = leds[led].green;
            blue[led] = leds[led].blue; 
        }
        
        if (maxBright)
        {
            leds[led].maximizeBrightness();
            red[led] = leds[led].red;
            green[led] = leds[led].green;
            blue[led] = leds[led].blue;
        } 
    }
    sel = x;
}


void showChanges()
{
    //Workaround to prevent sel getting reset
    int x = sel;
    if (sel == 5)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i].setRGB(red[i], green[i], blue[i]);
        }
    }
    else
    {
        leds[sel].setRGB(red[sel], green[sel], blue[sel]);
    }
    sel = x;
    FastLED.show();     
}

//Event queue task handler
void processTasks()
{
    counter++; 
    if ((counter % runSpeed) == 0)
    {
        //Serial.println("Speed controlled tasks go here");  
        
        //Do jump3 routine
        if (jump3 == 1)
        {
            sel = 5;
            doJump3();  
        }
        
        //Do jump7 routine
        if (jump7)
        {
            sel = 5;
            doJump7();
        }
    
        //Do fade3 routine
        if (fade3)
        {
            sel = 5;
            doFade();
        }
    
        //Do fade7 routine
        if (fade7)
        {
            sel = 5;
            doFade();
        }   
    }
}

//What code has been pressed
int findAction (decode_results *results)
{
    int i = 0;
    //Check if code recognised
    for (i = 0 ; i < 44; i++)
    {
        if (results->value == values[i])
        {
            break;
        }  
    }
    return i;
}



//Perform requested action
void doAction(int action)
{
    //Reset any auto modes in operation
    if ((jump3 || jump7 || fade3 || fade7) && !(action == 31 || action == 27 || action == 0 || action == 1))
    {
        resetAuto();   
    }
     
    //Trigger response to button 0 being presed
    if (action == 0)
    {
        ACTION0;
    } 
    
    //Trigger response to button 1 being presed
    if (action == 1)
    {
        ACTION1;
    } 
    
    //Trigger response to button 2 being presed
    if (action == 2)
    {
        ACTION2;
    } 
    
    //Trigger response to button 3 being presed
    if (action == 3)
    {
        ACTION3;
    } 
    
    //Trigger response to button 4 being presed
    if (action == 4)
    {
        ACTION4;
    } 
    
    //Trigger response to button 5 being presed
    if (action == 5)
    {
        ACTION5;
    } 
    
    //Trigger response to button 6 being presed
    if (action == 6)
    {
        ACTION6;
    } 
    
    //Trigger response to button 7 being presed
    if (action == 7)
    {
        ACTION7;
    } 
    
    //Trigger response to button 8 being presed
    if (action == 8)
    {
        ACTION8;
    } 
    
    //Trigger response to button 9 being presed
    if (action == 9)
    {
        ACTION9;
    } 
    
    //Trigger response to button 10 being presed
    if (action == 10)
    {
        ACTION10;
    } 
    
    //Trigger response to button 11 being presed
    if (action == 11)
    {
        ACTION11;
    } 
    
    //Trigger response to button 12 being presed
    if (action == 12)
    {
        ACTION12;
    } 
    
    //Trigger response to button 13 being presed
    if (action == 13)
    {
        ACTION13;
    } 
    
    //Trigger response to button 14 being presed
    if (action == 14)
    {
        ACTION14;
    } 
    
    //Trigger response to button 15 being presed
    if (action == 15)
    {
        ACTION15;
    } 
    
    //Trigger response to button 16 being presed
    if (action == 16)
    {
        ACTION16;
    } 
    
    //Trigger response to button 17 being presed
    if (action == 17)
    {
        ACTION17;
    } 
    
    //Trigger response to button 18 being presed
    if (action == 18)
    {
        ACTION18;
    } 
    
    //Trigger response to button 19 being presed
    if (action == 19)
    {
        ACTION19;
    } 
    
    //Trigger response to button 20 being presed
    if (action == 20)
    {
        ACTION20;
    } 
    
    //Trigger response to button 21 being presed
    if (action == 21)
    {
        ACTION21;
    } 
    
    //Trigger response to button 22 being presed
    if (action == 22)
    {
        ACTION22;
    } 
    
    //Trigger response to button 23 being presed
    if (action == 23)
    {
        ACTION23;
    } 
    
    //Trigger response to button 24 being presed
    if (action == 24)
    {
        ACTION24;
    } 
    
    //Trigger response to button 25 being presed
    if (action == 25)
    {
        ACTION25;
    } 
    
    //Trigger response to button 26 being presed
    if (action == 26)
    {
        ACTION26;
    } 
    
    //Trigger response to button 27 being presed
    if (action == 27)
    {
        ACTION27;
    } 
    
    //Trigger response to button 28 being presed
    if (action == 28)
    {
        ACTION28;
    } 
    
    //Trigger response to button 29 being presed
    if (action == 29)
    {
        ACTION29;
    } 
    
    //Trigger response to button 30 being presed
    if (action == 30)
    {
        ACTION30;
    } 
    
    //Trigger response to button 31 being presed
    if (action == 31)
    {
        ACTION31;
    } 
    
    //Trigger response to button 32 being presed
    if (action == 32)
    {
        ACTION32;
    } 
    
    //Trigger response to button 33 being presed
    if (action == 33)
    {
        ACTION33;
    } 
    
    //Trigger response to button 34 being presed
    if (action == 34)
    {
        ACTION34;
    } 
    
    //Trigger response to button 35 being presed
    if (action == 35)
    {
        ACTION35;
    } 
    
    //Trigger response to button 36 being presed
    if (action == 36)
    {
        ACTION36;
    } 
    
    //Trigger response to button 37 being presed
    if (action == 37)
    {
        ACTION37;
    } 
    
    //Trigger response to button 38 being presed
    if (action == 38)
    {
        ACTION38;
    } 
    
    //Trigger response to button 39 being presed
    if (action == 39)
    {
        ACTION39;
    } 
    
    //Trigger response to button 40 being presed
    if (action == 40)
    {
        ACTION40;
    } 
    
    //Trigger response to button 41 being presed
    if (action == 41)
    {
        ACTION41;
    } 
    
    //Trigger response to button 42 being presed
    if (action == 42)
    {
        ACTION42;
    } 
    
    //Trigger response to button 43 being presed
    if (action == 43)
    {
        ACTION43;
    } 
}
