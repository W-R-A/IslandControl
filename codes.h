//Actions to be perfomed when buttons are pressed

#define ACTION0 FastLED.setBrightness(253);













//Remote for LED control. Order is in top left to bottom right, working rows then columns.
//The list below coresponds to the number above 0 -->43
 unsigned long int values[44] = {
                       0xFF3AC5, //Brightness up
                       0xFFBA45, //Brightness down
                       0xFF827D, //Pause on current settings
                       0xFF02FD, //Power on/off
                       0xFF1AE5, //Red
                       0xFF9A65, //Green
                       0xFFA25D, //Blue
                       0xFF22DD, //White
                       0xFF2AD5, //Orange
                       0xFFAA55, //Light green
                       0xFF926D, //Bright blue
                       0xFF12ED, //Light Pink
                       0xFF0AF5, //Light red
                       0xFF8A75, //Light blue
                       0xFFB24D, //Dark blue
                       0xFF32CD, //Light pink
                       0xFF38C7, //Light orange
                       0xFFB847, //Green blue
                       0xFF7887, //Purple
                       0xFFF807, //Baby blue
                       0xFF18E7, //Yellow
                       0xFF9867, //Turquoise
                       0xFF58A7, //Pink
                       0xFFD827, //Baby blue
                       0xFF28D7, //Increase red
                       0xFFA857, //Increase green
                       0xFF6897, //Increase blue
                       0xFFE817, //Increase speed
                       0xFF08F7, //Decrease red
                       0xFF8877, //Decrease green
                       0xFF48B7, //Decrease blue
                       0xFFC837, //Decrease speed
                       0xFF30CF, //DIY 1
                       0xFFB04F, //DIY 2  
                       0xFF708F, //DIY 3
                       0xFFF00F, //Auto
                       0xFF10EF, //DIY 4
                       0xFF906F, //DIY 5   
                       0xFF50AF, //DIY 6 
                       0xFFD02F, //Flash
                       0xFF20DF, //Jump 3
                       0xFFA05F, //Jump 7
                       0xFF609F, //Fade 3
                       0xFFE01F, //Fade 7                    
                      };
