/*
  - RadioLib Non-Arduino Raspberry Pi Example

  This example shows how to use RadioLib without Arduino.
  In this case, a Raspberry Pi with WaveShare SX1302 LoRaWAN Hat
  using the lgpio library
  https://abyz.me.uk/lg/lgpio.html

  Can be used as a starting point to port RadioLib to any platform!
  See this API reference page for details on the RadioLib hardware abstraction
  https://jgromes.github.io/RadioLib/class_hal.html
   
  
  - RadioLib LoRaWAN Starter Example

  ! Please refer to the included notes to get started !

  This example joins a LoRaWAN network and will send
  uplink packets. Before you start, you will have to
  register your device at https://www.thethingsnetwork.org/
  After your device is registered, you can run this example.
  The device will join the network and start uploading data.

  Running this examples REQUIRES you to check "Resets DevNonces"
  on your LoRaWAN dashboard. Refer to the network's 
  documentation on how to do this.

  For default module settings, see the wiki page
  https://github.com/jgromes/RadioLib/wiki/Default-configuration

  For full API reference, see the GitHub Pages
  https://jgromes.github.io/RadioLib/

  For LoRaWAN details, see the wiki page
  https://github.com/jgromes/RadioLib/wiki/LoRaWAN

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Per sleep
#include "config.h"  // Configuration

void setup() {
  printf("Setup ...\n");

  // Serial.begin(115200);
  // while(!Serial);
  // delay(5000);  // Give time to switch to the serial monitor
  // Serial.println(F("\nSetup ... "));

  // Serial.println(F("Initialise the radio"));
  printf("Initialise the radio\n");

  int16_t state = radio.begin();
  // debug(state != RADIOLIB_ERR_NONE, F("Initialise radio failed"), state, true);
  debug(state != RADIOLIB_ERR_NONE, "Initialise radio failed", state, 1);

  // Setup the OTAA session information
  printf("Setup the OTAA session\n");
  state = node.beginOTAA(joinEUI, devEUI, nwkKey, appKey);
  // debug(state != RADIOLIB_ERR_NONE, F("Initialise node failed"), state, true);
  debug(state != RADIOLIB_ERR_NONE, "Initialise node failed", state, 1);

  // Serial.println(F("Join ('login') the LoRaWAN Network"));
  printf("Join ('login') the LoRaWAN Network\n");
  state = node.activateOTAA();
  // debug(state != RADIOLIB_LORAWAN_NEW_SESSION, F("Join failed"), state, true);
  debug(state != RADIOLIB_LORAWAN_NEW_SESSION, "Join failed", state, 1);

  // Serial.println(F("Ready!\n"));
  printf("Ready!\n");
}

void loop() {
  // Serial.println(F("Sending uplink"));
  printf("Sending uplink\n");

  // This is the place to gather the sensor inputs
  // Instead of reading any real sensor, we just generate some random numbers as example
  // uint8_t value1 = radio.random(100);
  // uint16_t value2 = radio.random(2000);
  uint8_t value1 = rand() % 100;
  uint16_t value2 = rand() % 2000;

  // Build payload byte array
  uint8_t uplinkPayload[3];
  uplinkPayload[0] = value1;
  // uplinkPayload[1] = highByte(value2);   // See notes for high/lowByte functions
  // uplinkPayload[2] = lowByte(value2);
  uplinkPayload[1] = (value2 >> 8) & 0xFF;  // byte alto
  uplinkPayload[2] = value2 & 0xFF;         // byte basso
  

  printf("uplink payload: %u\n", uplinkPayload);
  printf("value1 =  %u   value2 =  %u\n", value1, value2);


  // Perform an uplink
  int16_t state = node.sendReceive(uplinkPayload, sizeof(uplinkPayload));    
  // debug(state < RADIOLIB_ERR_NONE, F("Error in sendReceive"), state, false);
  debug(state < RADIOLIB_ERR_NONE, "Error in sendReceive", state, 0);

  // Check if a downlink was received 
  // (state 0 = no downlink, state 1/2 = downlink in window Rx1/Rx2)
  if(state > 0) {
    // Serial.println(F("Received a downlink"));
    printf("Received a downlink\n");
  } else {
    // Serial.println(F("No downlink received"));
    printf("No downlink received\n");
  }

  // Serial.print(F("Next uplink in "));
  // Serial.print(uplinkIntervalSeconds);
  // Serial.println(F(" seconds\n"));
  printf("Next uplink in %u seconds\n", uplinkIntervalSeconds);
  
  // Wait until next uplink - observing legal & TTN FUP constraints
  // delay(uplinkIntervalSeconds * 1000UL);  // delay needs milli-seconds
  sleep(uplinkIntervalSeconds);  // Waiting before next sending

}

int main() {
  // Runs the setup function only once
  setup();

  // Executes the loop function in a continuous loop
  while (1) {
      loop();
  }

  return 0;
}