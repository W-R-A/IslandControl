//Include IRRemote header file
#include <IRremote.h>

//Include FastLED header
#include <FastLED.h>

//Include header file contatining all the ir codes that the system should respond to
#include "codes.h"
               
//Define the pin which the reciever is connected to
int RECV_PIN = 2; 

//Setup a reciever object on this pin
IRrecv irrecv(RECV_PIN);

//Define a place to hold the ir code recieved
decode_results results;

//Setup
void setup()
{
  //Init the serial connection
  Serial.begin(9600);
  
  // Start the receiver
  irrecv.enableIRIn(); 
}

//What code has been pressed
int findAction (decode_results *results){
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

int doAction(int action)
{
    if (action = 0)
    {
      ACTION0;
    }
  
}

//Loop
void loop() {
  //If a code is recieved, do something about it, all signals recieved while processing will be ignored
  if (irrecv.decode(&results)) {
    
    //Print value recieved, in hex form
    Serial.println(results.value, HEX);

    //Let action determine what needs to be done
    int res = findAction(&results);
    if (res != 44)
    {
      Serial.println(res);
    }
    else
    {
      Serial.println("Unrecognised code!"); 
    }
    
    //Reset the value of results
    results.value = 0x00000000;
    
    //Resume listening for incoming signals
    irrecv.resume();
  }
}
