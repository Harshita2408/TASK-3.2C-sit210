#include "arduino_secrets.h"
// hp_BH1750 - Version: Latest 
#include <hp_BH1750.h>

#include "thingProperties.h"
#include <Arduino.h>

float sensor;
hp_BH1750 BH1750;

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  
  //This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  
  //Set the LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);
  
  //set the address and intialise the sensor
  bool avail= BH1750.begin(BH1750_TO_GROUND);
  
  //Defined in thingProperties.h
  initProperties();
  
  //Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop()
{
  ArduinoCloud.update();
  BH1750.start();
  sensor = BH1750.getLux();
  light_sensor = sensor;
}

void onSunlightChange()
{
  if(sunlight = true)
  {
  //Turn led on
  digitalWrite(LED_BUILTIN,HIGH);
  //Give a delay for 2 second
  delay(2000);
  }
  else if(sunlight = false)
  {
  //Turn led off
  digitalWrite(LED_BUILTIN, LOW);
  //Give a delay for 2 second
  delay(2000);
  }
}

void onLightSensorChange()
{
    //If light intensity is greater than 400, blink led
    if(light_sensor > 400)
    {
      //Terrarium is exposed to sunlight
      sunlight = true;
      onSunlightChange();
      
      //Print light intensity and sunlight value
      Serial.print("Light intensity: ");
      Serial.print(light_sensor);
      Serial.print("Sunlight: ON ");
    }
    //Else, turn led off
    else
    {
      sunlight = false;
      onSunlightChange();
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print("Light intensity: ");
      Serial.print(light_sensor);
      Serial.print("Sunlight: OFF ");
    }
    
    //Give a delay for 5 seconds
    delay(5000);
}