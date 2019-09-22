/* @file    ematch.ino
 * @author  Anthony Duen for UBC Rocket Avionics 2018/2019
 * @description Sample code for using the ematch igniter, including
 *  the igniter driver.
 *
 * @section LICENSE
 * This program is free software; you can redistribute it and/or
 * modify it without restriction under the terms of the MIT License.
 *
 * Distributed as-is; no warranty is given.
 */

/*Includes------------------------------------------------------------*/
#include <Arduino.h>
#include "igniter.h"
#include "debugger.h"

/*Constants------------------------------------------------------------*/
#define SerialUSB   Serial

/*Functions------------------------------------------------------------*/

/**
  * @brief  The Arduino setup function
  * @param  None
  * @return None
  */
void setup() {

    SerialUSB.begin(115200);
    while (!SerialUSB) {}
    SerialUSB.println("Initializing...");

    initIgniter();

    bool mainCheck = MainContinuityCheck();
    bool drogueCheck = DrogueContinuityCheck();

    if (mainCheck)
        SerialUSB.println("Main Continuity Check Passed");
    else
        SerialUSB.println("Main Continuity Check FAILED");

    if (drogueCheck)
        SerialUSB.println("Drogue Continuity Check Passed");
    else
        SerialUSB.println("Drogue Continuity Check FAILED");

    // infinite loop to halt program with continuity error
    while (!mainCheck || !drogueCheck){
        delay(2500);
        SerialUSB.println("Check igniters!");
    }

}

/**
  * @brief  The Arduino loop function
  * @param  None
  * @return None
  */
void loop() {
    // checks for serial input
    if(SerialUSB.available())
        serviceDebug();
}
