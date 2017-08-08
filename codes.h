//Actions to be perfomed when buttons are pressed

#define ACTION0 mixColour(0, 0, 0, 1, 0, 0, sel); if (bright < 240 ){bright = bright + 10;}
#define ACTION1 mixColour(0, 0, 0, 0, 1, 0, sel); if (bright > 50 ){bright = bright - 10;}
#define ACTION2 runSpeed = 0;
#define ACTION3 resetAuto(); changeColour(0, 0, 0, 5); sel = 5;
#define ACTION4 changeColour(255, 0, 0, sel);
#define ACTION5 changeColour(0, 255, 0, sel);
#define ACTION6 changeColour(0, 0, 255, sel);
#define ACTION7 changeColour(255, 255, 255, sel);
#define ACTION8 changeColour(233, 150, 122, sel);
#define ACTION9 changeColour(68, 255, 68, sel);
#define ACTION10 changeColour(30, 144, 255, sel);
#define ACTION11 changeColour(255, 240, 245, sel);
#define ACTION12 changeColour(233, 150, 122, sel);
#define ACTION13 changeColour(0, 191, 255, sel);
#define ACTION14 changeColour(0, 0, 205, sel);
#define ACTION15 changeColour(255, 240, 245, sel);
#define ACTION16 changeColour(255, 160, 122, sel);
#define ACTION17 changeColour(72, 209, 204, sel);
#define ACTION18 changeColour(153, 102, 204, sel);
#define ACTION19 changeColour(175, 238, 238, sel);
#define ACTION20 changeColour(255, 215, 0, sel);
#define ACTION21 changeColour(0, 128, 128, sel);
#define ACTION22 changeColour(255, 105, 180, sel);
#define ACTION23 changeColour(175, 238, 238, sel);
#define ACTION24 mixColour(1, 0, 0, 0, 0, 20, sel)
#define ACTION25 mixColour(0, 1, 0, 0, 0, 20, sel)
#define ACTION26 mixColour(0, 0, 1, 0, 0, 20, sel)
#define ACTION27 if (runSpeed > 1 ){runSpeed--;}
#define ACTION28 mixColour(1, 0, 0, 0, 0, -20, sel) 
#define ACTION29 mixColour(0, 1, 0, 0, 0, -20, sel)
#define ACTION30 mixColour(0, 0, 1, 0, 0, -20, sel)
#define ACTION31 if (runSpeed < 30 ){runSpeed++;}
#define ACTION32 sel = 0;
#define ACTION33 sel = 1;
#define ACTION34 sel = 2;
#define ACTION35 changeColour(68, 255, 68, 0); changeColour(255, 0, 0, 1); changeColour(0, 0, 255, 2); changeColour(255, 215, 0, 3); changeColour(175, 238, 238, 4);//auto mode
#define ACTION36 sel = 1;
#define ACTION37 sel = 2;
#define ACTION38 sel = 5;
#define ACTION39 int x = sel; for (int i = 0; i < NUM_LEDS; i++){leds[i].setRGB(255, 255, 255); FastLED.show(); delay(10); sel = 5; showChanges(); sel = x;}
#define ACTION40 doJump3(); jump3 = 1; 
#define ACTION41 doJump7(); jump7 = 1; 
#define ACTION42 doFade(); fade3 = 1; 
#define ACTION43 doFade(); fade7 = 1; 


//Remote for LED control. Order is in top left to bottom right, working rows then columns.
//The list below coresponds to the number above 0 -->43
 unsigned long int values[44] = {
                       0xFF3AC5, //Button 0 - Brightness up
                       0xFFBA45, //Button 1 - Brightness down
                       0xFF827D, //Button 2 - Pause on current settings
                       0xFF02FD, //Button 3 - Power on/off
                       0xFF1AE5, //Button 4 - Red
                       0xFF9A65, //Button 5 - Green
                       0xFFA25D, //Button 6 - Blue
                       0xFF22DD, //Button 7 - White
                       0xFF2AD5, //Button 8 - Orange
                       0xFFAA55, //Button 9 - Light green
                       0xFF926D, //Button 10 - Bright blue
                       0xFF12ED, //Button 11 - Light Pink
                       0xFF0AF5, //Button 12 - Light red
                       0xFF8A75, //Button 13 - Light blue
                       0xFFB24D, //Button 14 - Dark blue
                       0xFF32CD, //Button 15 - Light pink
                       0xFF38C7, //Button 16 - Light orange
                       0xFFB847, //Button 17 - Green blue
                       0xFF7887, //Button 18 - Purple
                       0xFFF807, //Button 19 - Baby blue
                       0xFF18E7, //Button 20 - Yellow
                       0xFF9867, //Button 21 - Turquoise
                       0xFF58A7, //Button 22 - Pink
                       0xFFD827, //Button 23 - Baby blue
                       0xFF28D7, //Button 24 - Increase red
                       0xFFA857, //Button 25 - Increase green
                       0xFF6897, //Button 26 - Increase blue
                       0xFFE817, //Button 27 - Increase speed
                       0xFF08F7, //Button 28 - Decrease red
                       0xFF8877, //Button 29 - Decrease green
                       0xFF48B7, //Button 30 - Decrease blue
                       0xFFC837, //Button 31 - Decrease speed
                       0xFF30CF, //Button 32 - DIY 1
                       0xFFB04F, //Button 33 - DIY 2  
                       0xFF708F, //Button 34 - DIY 3
                       0xFFF00F, //Button 35 - Auto
                       0xFF10EF, //Button 36 - DIY 4
                       0xFF906F, //Button 37 - DIY 5   
                       0xFF50AF, //Button 38 - DIY 6 
                       0xFFD02F, //Button 39 - Flash
                       0xFF20DF, //Button 40 - Jump 3
                       0xFFA05F, //Button 41 - Jump 7
                       0xFF609F, //Button 42 - Fade 3
                       0xFFE01F, //Button 43 - Fade 7                    
                      };
